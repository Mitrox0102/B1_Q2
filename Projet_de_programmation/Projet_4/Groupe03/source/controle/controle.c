#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>

#include "controle.h"

GtkWidget *label_score_global = NULL;
extern bool dialogue_fin_partie_affiche;

void maj_grille(GtkWidget *bouton_clique, gpointer donnees_plateau)
{
   if (!bouton_clique || !GTK_IS_BUTTON(bouton_clique))
   {
      fprintf(stderr, "Erreur: bouton cliqué invalide\n");
      return;
   }

   Plateau *plateau = (Plateau *)donnees_plateau;
   if (!plateau)
      return;

   static Case *case_selectionnee = NULL;
   int ligne = -1, colonne = -1;
   int largeur = plateau_get_largeur(plateau);
   int hauteur = plateau_get_hauteur(plateau);

   // Trouver la case cliquée
   for (int i = 0; i < largeur; i++)
   {
      for (int j = 0; j < hauteur; j++)
      {
         Case *case_courante = plateau_get_case(plateau, i, j);
         if (case_get_image(case_courante) == bouton_clique)
         {
            ligne = i;
            colonne = j;
            break;
         }
      }
      if (ligne != -1)
         break;
   }

   if (ligne == -1 || colonne == -1)
      return;

   Case *case_courante = plateau_get_case(plateau, ligne, colonne);
   if (!case_courante)
   {
      fprintf(stderr, "Erreur: case courante invalide\n");
      return;
   }

   // Si case occupée, on la sélectionne
   if (case_est_occupe(case_courante))
   {
      case_selectionnee = case_courante;
      return;
   }

   // Si case vide et une case est sélectionnée, on tente le déplacement
   if (case_selectionnee && !case_est_occupe(case_courante))
   {
      if (chemin_possible(plateau, case_selectionnee, case_courante))
      {
         // Copier l'image
         GtkWidget *image_source = gtk_button_get_image(GTK_BUTTON(case_get_image(case_selectionnee)));
         if (image_source)
         {
            GdkPixbuf *pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(image_source));
            GtkWidget *nouvelle_image = gtk_image_new_from_pixbuf(pixbuf);
            gtk_button_set_image(GTK_BUTTON(case_get_image(case_courante)), nouvelle_image);
         }

         // Mettre à jour les données
         case_set_couleur(case_courante, case_get_couleur(case_selectionnee));
         case_set_occupe(case_courante, true);
         case_set_occupe(case_selectionnee, false);
         gtk_button_set_image(GTK_BUTTON(case_get_image(case_selectionnee)), NULL);

         // Vérifier les alignements et mettre à jour le score
         if (verifier_lignes(plateau))
         {
            // Utiliser directement la référence globale
            if (label_score_global)
            {
               char buffer[32];
               int score = plateau_get_score_valeur(plateau);
               snprintf(buffer, sizeof(buffer), "%d", score);
               gtk_label_set_text(GTK_LABEL(label_score_global), buffer);
               //printf("Score mis à jour: %d\n", score);
            }
            else
            {
               fprintf(stderr, "Erreur: label_score_global est NULL\n");
            }
         }
         int total_cases = largeur * hauteur;
         int nb_cases_remplies = plateau_get_nb_cases_remplies(plateau);
         int cases_restantes = total_cases - nb_cases_remplies;
         int symboles_par_tour = plateau_get_symboles_par_tour(plateau);

         if (cases_restantes < symboles_par_tour)
         {
            int score = plateau_get_score_valeur(plateau);
            //printf("Plus assez de cases libres! Fin de partie.\n");
            afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), score);
            return;
         }

         generation_boules_depuis_liste(plateau, symboles_par_tour);

         nb_cases_remplies = plateau_get_nb_cases_remplies(plateau);
         cases_restantes = total_cases - nb_cases_remplies;
         if (cases_restantes < symboles_par_tour)
         {
            int score = plateau_get_score_valeur(plateau);
            //printf("Plus assez de cases libres! Fin de partie.\n");
            afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), score);
            return;
         }

         preparer_boules_suivantes(plateau);
         GtkWidget **boutons_suivants = plateau_get_boutons_suivants(plateau);
         if (!boutons_suivants)
         {
            fprintf(stderr, "Erreur: boutons_suivants est NULL\n");
            return;
         }
         maj_boutons_suivants(boutons_suivants, plateau);
      }
      case_selectionnee = NULL;
   }
}

void detruire_widget(GtkWidget *widget, gpointer data)
{
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
   if (!vbox || !GTK_IS_BOX(vbox))
   {
      fprintf(stderr, "Erreur: impossible de trouver le conteneur principal\n");
      return;
   }

   gtk_container_foreach(GTK_CONTAINER(vbox), detruire_widget, NULL);

   GtkWidget *barre_outils = creer_barre_outils();
   if (!barre_outils)
   {
      fprintf(stderr, "Erreur: impossible de créer la barre d'outils\n");
      return;
   }
   gtk_box_pack_start(GTK_BOX(vbox), barre_outils, FALSE, FALSE, 0);

   // Crée le score et les boules
   int nb_suivantes = plateau_get_nb_suivantes(nouveau_plateau);
   GtkWidget **boutons_suivants = g_new(GtkWidget *, nb_suivantes);
   if (!boutons_suivants)
   {
      fprintf(stderr, "Erreur: impossible d'allouer de la mémoire pour les boutons suivants\n");
      return;
   }

   for (int i = 0; i < nb_suivantes; i++)
   {
      boutons_suivants[i] = NULL;
   }

   plateau_set_boutons_suivants(nouveau_plateau, boutons_suivants);

   GtkWidget *label_score = NULL;
   GtkWidget *hbox_suivants_et_score = creer_suivants_et_score(boutons_suivants, &label_score, nouveau_plateau);
   if (!hbox_suivants_et_score)
   {
      fprintf(stderr, "Erreur: impossible de créer le conteneur pour les boules suivantes et le score\n");
      return;
   }
   gtk_box_pack_start(GTK_BOX(vbox), hbox_suivants_et_score, FALSE, FALSE, 5);

   // Crée la nouvelle grille
   GtkWidget *nouvelle_grille = creer_grille(nouveau_plateau);
   if (!nouvelle_grille)
   {
      fprintf(stderr, "Erreur: impossible de créer la grille\n");
      return;
   }
   gtk_box_pack_start(GTK_BOX(vbox), nouvelle_grille, TRUE, TRUE, 0);

   grille_actuelle = nouvelle_grille;

   if (!nouveau_plateau)
   {
      g_warning("Plateau NULL dans recreer_grille");
      return;
   }

   gtk_widget_show_all(fenetre_principale);
}

void changer_niveau(GtkMenuItem *item, gpointer user_data)
{
   if (!item)
   {
      fprintf(stderr, "Erreur: item invalide dans changer_niveau\n");
      return;
   }

   (void)item;

   int niveau = GPOINTER_TO_INT(user_data);

   if (plateau_actuel)
   {
      detruire_plateau(plateau_actuel);
      plateau_actuel = NULL;
   }

   if (grille_actuelle)
   {
      gtk_widget_destroy(grille_actuelle);
      grille_actuelle = NULL;
   }

   switch (niveau)
   {
   case 0:
      plateau_actuel = creer_plateau(fenetre_principale, 7, 7, 5, 3, 0);
      if (est_benoit_donnet(score_get_nom(plateau_actuel)))
         plateau_set_score_valeur(plateau_actuel, 99999);
      break;
   case 1:
      plateau_actuel = creer_plateau(fenetre_principale, 9, 9, 7, 3, 1);
      if (est_benoit_donnet(score_get_nom(plateau_actuel)))
         plateau_set_score_valeur(plateau_actuel, 99999);
      break;
   case 2:
      plateau_actuel = creer_plateau(fenetre_principale, 20, 15, 7, 7, 2);
      if (est_benoit_donnet(score_get_nom(plateau_actuel)))
         plateau_set_score_valeur(plateau_actuel, 99999);
      break;
   default:
      fprintf(stderr, "Niveau inconnu\n");
      return;
   }

   if (plateau_actuel == NULL)
   {
      fprintf(stderr, "Erreur lors de la création du plateau\n");
      return;
   }

   plateau_set_score_valeur(plateau_actuel, 0);

   recreer_grille(fenetre_principale, plateau_actuel);

   generation_boules(plateau_actuel);
   preparer_boules_suivantes(plateau_actuel);
   GtkWidget **boutons_suivants = plateau_get_boutons_suivants(plateau_actuel);
   maj_boutons_suivants(boutons_suivants, plateau_actuel);

   gtk_widget_show_all(fenetre_principale);
}

bool chemin_possible(Plateau *plateau, Case *depart, Case *arrivee)
{
   if (!plateau || !depart || !arrivee)
      return false;

   int largeur = plateau_get_largeur(plateau);
   int hauteur = plateau_get_hauteur(plateau);

   // Allocation de la matrice de visite
   bool **visite = malloc(hauteur * sizeof(bool *));
   if (!visite)
   {
      g_warning("Erreur d'allocation mémoire");
      return false;
   }

   for (int i = 0; i < hauteur; i++)
   {
      visite[i] = calloc(largeur, sizeof(bool));
      if (!visite[i])
      {
         // Libération de la mémoire en cas d'erreur
         for (int j = 0; j < i; j++)
            free(visite[j]);
         free(visite);
         return false;
      }
   }

   GQueue *file = g_queue_new();
   if (!file)
   {
      // Libération de la mémoire en cas d'erreur
      for (int i = 0; i < hauteur; i++)
         free(visite[i]);
      free(visite);
      return false;
   }
   g_queue_push_tail(file, depart);

   // Trouver les coordonnées de départ
   int x_depart = -1, y_depart = -1;
   for (int y = 0; y < hauteur && x_depart == -1; y++)
   {
      for (int x = 0; x < largeur; x++)
         if (plateau_get_case(plateau, x, y) == depart)
         {
            x_depart = x;
            y_depart = y;
            break;
         }
   }

   if (x_depart == -1 || y_depart == -1)
   {
      // Libération si case de départ non trouvée
      for (int i = 0; i < hauteur; i++)
         free(visite[i]);
      free(visite);
      g_queue_free(file);
      return false;
   }

   bool chemin_trouve = false;

   while (!g_queue_is_empty(file))
   {
      Case *courante = g_queue_pop_head(file);

      int x = -1, y = -1;

      // Trouver les coordonnées de la case courante
      for (int i = 0; i < hauteur && x == -1; i++)
      {
         for (int j = 0; j < largeur; j++)
         {
            if (plateau_get_case(plateau, j, i) == courante)
            {
               x = j;
               y = i;
               break;
            }
         }
      }

      if (x == -1 || y == -1)
         continue;

      // Vérifier si on est arrivé à destination
      if (courante == arrivee)
      {
         chemin_trouve = true;
         break;
      }

      // Marquer comme visité
      visite[y][x] = true;

      // Directions : haut, bas, gauche, droite
      int dx[4] = {0, 0, -1, 1};
      int dy[4] = {-1, 1, 0, 0};

      for (int d = 0; d < 4; d++)
      {
         int nx = x + dx[d];
         int ny = y + dy[d];

         if (nx >= 0 && ny >= 0 && nx < largeur && ny < hauteur && !visite[ny][nx])
         {
            Case *voisine = plateau_get_case(plateau, nx, ny);
            if (!voisine)
            {
               fprintf(stderr, "Erreur: case voisine invalide\n");
               return NULL;
            }
            if (!case_est_occupe(voisine) || voisine == arrivee)
            {
               visite[ny][nx] = true;
               g_queue_push_tail(file, voisine);
            }
         }
      }
   }

   // Libération de la mémoire
   for (int i = 0; i < hauteur; i++)
      free(visite[i]);
   free(visite);
   g_queue_free(file);

   return chemin_trouve;
}

void nouvelle_partie(GtkMenuItem *item, gpointer user_data)
{
   // Permettre l'appel avec un item NULL (pour le bouton Rejouer)
   if (item && !GTK_IS_MENU_ITEM(item))
   {
      fprintf(stderr, "Erreur: item invalide dans nouvelle_partie\n");
      return;
   }

   (void)item;
   (void)user_data;

   // Préserver la difficulté actuelle si le plateau existe
   int difficulte = 0;
   dialogue_fin_partie_affiche = false;
   if (plateau_actuel)
   {
      difficulte = plateau_get_difficulte(plateau_actuel);
   }

   // Nettoyer proprement l'ancien plateau
   if (plateau_actuel)
   {
      detruire_boules_suivantes(plateau_actuel);
      detruire_plateau(plateau_actuel);
      plateau_actuel = NULL;
   }

   // Nettoyer l'ancienne grille
   if (grille_actuelle)
   {
      gtk_widget_destroy(grille_actuelle);
      grille_actuelle = NULL;
   }

   // Créer un nouveau plateau selon la difficulté
   switch (difficulte)
   {
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
      plateau_actuel = creer_plateau(fenetre_principale, 7, 7, 5, 3, 0);
      break;
   }

   if (!plateau_actuel)
   {
      fprintf(stderr, "Erreur critique: Impossible de créer un nouveau plateau\n");
      return;
   }

   // Réinitialiser le score
   plateau_set_score_valeur(plateau_actuel, 0);

   recreer_grille(fenetre_principale, plateau_actuel);

   // Générer les boules initiales
   generation_boules(plateau_actuel);
   preparer_boules_suivantes(plateau_actuel);

   GtkWidget **boutons_suivants = plateau_get_boutons_suivants(plateau_actuel);
   if (boutons_suivants)
   {
      maj_boutons_suivants(boutons_suivants, plateau_actuel);
   }
   else
   {
      fprintf(stderr, "Erreur: boutons_suivants est NULL après recreer_grille\n");
   }

   gtk_widget_show_all(fenetre_principale);
}

void quitter_jeu(GtkMenuItem *item, gpointer user_data)
{
   if (!item)
   {
      fprintf(stderr, "Erreur: item invalide dans quitter_jeu\n");
      return;
   }
   (void)item;
   (void)user_data;
   gtk_main_quit();
}

void afficher_meilleurs_scores(GtkMenuItem *item, gpointer user_data)
{
   if (!item)
   {
      fprintf(stderr, "Erreur: item invalide dans afficher_meilleurs_scores\n");
      return;
   }
   (void)item;
   (void)user_data;
   afficher_dialogue_scores();
}

void afficher_a_propos(GtkMenuItem *item, gpointer user_data)
{
   if (!item)
   {
      fprintf(stderr, "Erreur: item invalide dans afficher_a_propos\n");
      return;
   }
   (void)item;
   (void)user_data;
   afficher_dialogue_a_propos();
}

void afficher_regles(GtkMenuItem *item, gpointer user_data)
{
   if (!item)
   {
      fprintf(stderr, "Erreur: item invalide dans afficher_regles\n");
      return;
   }
   (void)item;
   (void)user_data;
   afficher_dialogue_regles();
}
