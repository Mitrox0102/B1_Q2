#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>

#include "controle.h"

static Case *case_selectionnee = NULL;


void maj_grille(GtkWidget *bouton_clique, gpointer donnees_plateau) {
   Plateau *plateau = donnees_plateau;
   if (!plateau) return;

   int ligne = -1, colonne = -1;

   for (int i = 0; i < plateau->largeur; i++) {
      for (int j = 0; j < plateau->hauteur; j++) {
         if (plateau->cases[i * plateau->hauteur + j].image == bouton_clique) {
               ligne = i;
               colonne = j;
               break;
         }
      }
      if (ligne != -1) break;
   }

   if (ligne == -1 || colonne == -1) return;
   Case *clic = &plateau->cases[ligne * plateau->hauteur + colonne];

   if (clic->occupe) {
      case_selectionnee = clic;
      return;
   }

   if (case_selectionnee && !clic->occupe) {
      bool chemin = chemin_possible(plateau, case_selectionnee, clic);
      if (chemin) {
         clic->col = case_selectionnee->col;
         clic->occupe = true;

         GdkPixbuf *pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(gtk_button_get_image(GTK_BUTTON(case_selectionnee->image))));
         GtkWidget *nouvelle_image = gtk_image_new_from_pixbuf(pixbuf);
         gtk_button_set_image(GTK_BUTTON(clic->image), nouvelle_image);

         case_selectionnee->occupe = false;
         gtk_button_set_image(GTK_BUTTON(case_selectionnee->image), NULL);

         generation_boules_depuis_liste(plateau, plateau->symboles_par_tour);
         preparer_boules_suivantes(plateau);

         if (!plateau->boutons_suivants || plateau->nb_suivantes <= 0) {
            fprintf(stderr, "Erreur : boutons_suivants non initialisés correctement (%d)\n", plateau->nb_suivantes);
         } else {
            maj_boutons_suivants(plateau->boutons_suivants, plateau);
         }

         g_print("Déplacement effectué.\n");
      } else {
         g_print("Aucun chemin disponible.\n");
      }
      case_selectionnee = NULL;
   }
}


void detruire_widget(GtkWidget *widget, gpointer data) {
   (void)data;
   gtk_widget_destroy(widget);
}


void recreer_grille(GtkWidget *fenetre_principale, Plateau *nouveau_plateau)
{
   Data donnees_vbox;
   donnees_vbox.est_widget = NULL;
   donnees_vbox.est_trouve = FALSE;
   
   gtk_container_foreach(GTK_CONTAINER(fenetre_principale), callback_trouver_vbox, &donnees_vbox);

   GtkWidget *vbox = donnees_vbox.est_widget;


   // Vérifie si le conteneur principal est valide
   if (!vbox || !GTK_IS_BOX(vbox))
   {
      fprintf(stderr, "Erreur: impossible de trouver le conteneur principal\n");
      return;
   }

   //Detruire les widgets de la grille actuelle
   gtk_container_foreach(GTK_CONTAINER(vbox), detruire_widget, NULL);

   // Crée la nouvelle barre d'ooutils

   GtkWidget *barre_outils = creer_barre_outils();
   gtk_box_pack_start(GTK_BOX(vbox), barre_outils, FALSE, FALSE, 0);

   // Crée le score et les bouless

   GtkWidget **boutons_suivants = g_new(GtkWidget *, 5);
   for (int i = 0; i < 5; i++)
   {
      boutons_suivants[i] = NULL;
   }

   nouveau_plateau->boutons_suivants = boutons_suivants;
   
   GtkWidget *label_score;
   GtkWidget *hbox_suivants_et_score = creer_suivants_et_score(nouveau_plateau->boutons_suivants, &label_score, nouveau_plateau);
   gtk_box_pack_start(GTK_BOX(vbox), hbox_suivants_et_score, FALSE, FALSE, 5);

   // Crée la nouvelle grille
   GtkWidget *nouvelle_grille = creer_grille(nouveau_plateau);
   gtk_box_pack_start(GTK_BOX(vbox), nouvelle_grille, TRUE, TRUE, 0);

   grille_actuelle = nouvelle_grille;
   
   if (!nouveau_plateau) {
      g_warning("Plateau NULL dans recreer_grille");
      return;
   }

   
   gtk_widget_show_all(fenetre_principale);
}


void changer_niveau(GtkMenuItem *item, gpointer user_data) {
   (void)item;

   int niveau = GPOINTER_TO_INT(user_data);

   if (plateau_actuel) {
      detruire_plateau(plateau_actuel);
      plateau_actuel = NULL;
   }

   if (grille_actuelle) {
      gtk_widget_destroy(grille_actuelle);
      grille_actuelle = NULL;
   }

   switch (niveau) {
      case 0:
         plateau_actuel = creer_plateau(fenetre_principale, 7, 7, 5, 3, 0);
         break;
      case 1:
         plateau_actuel = creer_plateau(fenetre_principale, 9, 9, 7, 3, 1);
         break;
      case 2:
         plateau_actuel = creer_plateau(fenetre_principale, 20, 15, 7, 5, 2);
         break;
      default:
         fprintf(stderr, "Niveau inconnu\n");
         return;
   }

   if(plateau_actuel == NULL) {
      fprintf(stderr, "Erreur lors de la création du plateau\n");
      return;
   }

   plateau_actuel->score.valeur = 0;

   recreer_grille(fenetre_principale, plateau_actuel);

   generation_boules(plateau_actuel);
   preparer_boules_suivantes(plateau_actuel);
   maj_boutons_suivants(plateau_actuel->boutons_suivants, plateau_actuel);

   gtk_widget_show_all(fenetre_principale);
}


bool chemin_possible(Plateau *plateau, Case *depart, Case *arrivee) {
   int largeur = plateau->largeur;
   int hauteur = plateau->hauteur;
   bool **visite = malloc(sizeof(bool *) * hauteur);

   if (!visite) {
      fprintf(stderr, "Erreur d'allocation de mémoire pour la matrice de visite.\n");
      return false;
   }

   for (int i = 0; i < hauteur; i++) {
      visite[i] = calloc(largeur, sizeof(bool));
   }


   GQueue *file = g_queue_new();
   g_queue_push_tail(file, depart);


   while (!g_queue_is_empty(file)) {
      Case *courante = g_queue_pop_head(file);
      int x = -1, y = -1;


      for (int i = 0; i < hauteur; i++) {
         for (int j = 0; j < largeur; j++) {
               if (&plateau->cases[i * largeur + j] == courante) {
                  x = i;
                  y = j;
                  break;
               }
         }
         if (x != -1) break;
      }


      if (&plateau->cases[x * largeur + y] == arrivee) {
         for (int i = 0; i < hauteur; i++) free(visite[i]);
         free(visite);
         g_queue_free(file);
         return true;
      }


      visite[x][y] = true;


      int dx[4] = { -1, 1, 0, 0 };
      int dy[4] = { 0, 0, -1, 1 };

      for (int d = 0; d < 4; d++) {
         int nx = x + dx[d];
         int ny = y + dy[d];


         if (nx >= 0 && ny >= 0 && nx < hauteur && ny < largeur) {
               if (!visite[nx][ny]) {
                  Case *voisine = &plateau->cases[nx * largeur + ny];
                  if (!voisine->occupe) {
                     visite[nx][ny] = true;
                     g_queue_push_tail(file, voisine);
                  }
               }
         }
      }
   }

   for (int i = 0; i < hauteur; i++) free(visite[i]);
   free(visite);
   g_queue_free(file);
   return false;
}
