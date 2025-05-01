#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>

#include "vue.h"
#include "../modele/modele.h"
#include "../controle/controle.h"
#include "../utilis.h"

extern Plateau *plateau_actuel;

GtkWidget *creer_fenetre(void)
{
   GtkWidget *F = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(F), "Five");
   gtk_window_set_default_size(GTK_WINDOW(F), 700, 800);

   g_signal_connect(G_OBJECT(F), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   return F;

} // fin creer_fenetre()

GtkWidget *creer_barre_outils(void)
{

   GtkWidget *menu_bar = gtk_menu_bar_new(); // lignes 26

   // --------------------- MENU PARTIE ---------------------
   GtkWidget *menu_partie = gtk_menu_new();
   GtkWidget *item_partie = gtk_menu_item_new_with_label("Partie");
   GtkWidget *item_nouvelle = gtk_menu_item_new_with_label("Nouvelle partie");
   GtkWidget *item_scores = gtk_menu_item_new_with_label("Meilleurs scores");
   GtkWidget *item_quitter = gtk_menu_item_new_with_label("Quitter");

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_nouvelle);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_scores);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_quitter);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_partie), menu_partie);

   // --------------------- MENU NIVEAU ---------------------
   GtkWidget *menu_niveau = gtk_menu_new();
   GtkWidget *item_niveau = gtk_menu_item_new_with_label("Niveau");
   GtkWidget *item_facile = gtk_menu_item_new_with_label("Facile");
   GtkWidget *item_moyen = gtk_menu_item_new_with_label("Moyen");
   GtkWidget *item_difficile = gtk_menu_item_new_with_label("Difficile");

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_facile);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_moyen);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_difficile);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_niveau), menu_niveau);

   g_signal_connect(G_OBJECT(item_facile), "activate", G_CALLBACK(changer_niveau), GINT_TO_POINTER(0));
   g_signal_connect(G_OBJECT(item_moyen), "activate", G_CALLBACK(changer_niveau), GINT_TO_POINTER(1));
   g_signal_connect(G_OBJECT(item_difficile), "activate", G_CALLBACK(changer_niveau), GINT_TO_POINTER(2));

   // --------------------- MENU AIDE ---------------------
   GtkWidget *menu_aide = gtk_menu_new();
   GtkWidget *item_aide = gtk_menu_item_new_with_label("Aide");
   GtkWidget *item_apropos = gtk_menu_item_new_with_label("À propos");

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_aide), item_apropos);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_aide), menu_aide);

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), item_partie);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), item_niveau);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), item_aide);

   g_signal_connect(G_OBJECT(item_quitter), "activate", G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(G_OBJECT(item_scores), "activate", G_CALLBACK(afficher_dialogue_scores), NULL);
   g_signal_connect(G_OBJECT(item_apropos), "activate", G_CALLBACK(afficher_dialogue_a_propos), NULL);

   // Autres actions que je dois encore implémenter : par exemple meilleurs scores

   return menu_bar;
}

char nom_joueur[MAX_NOM + 1] = "Joueur";

char *demander_nom_joueur()
{
   GtkWidget *dialog, *content;
   GtkWidget *table, *label, *entree;
   GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

   dialog = gtk_dialog_new_with_buttons("Bienvenue dans Five or More",
                                          NULL,
                                          flags,
                                          "Commencer", GTK_RESPONSE_ACCEPT,
                                          NULL);
   gtk_window_set_default_size(GTK_WINDOW(dialog), 350, 40);

   content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

   table = gtk_table_new(2, 1, FALSE);
   gtk_table_set_row_spacings(GTK_TABLE(table), 10);
   gtk_table_set_col_spacings(GTK_TABLE(table), 10);
   gtk_container_set_border_width(GTK_CONTAINER(table), 15);

   label = gtk_label_new("Entrez votre nom:");
   gtk_table_attach(GTK_TABLE(table), label, 
                     0, 1, 0, 1, 
                     GTK_EXPAND | GTK_FILL, GTK_FILL, 
                     0, 0);

   entree = gtk_entry_new();
   gtk_entry_set_text(GTK_ENTRY(entree), "Joueur");
   gtk_entry_set_max_length(GTK_ENTRY(entree), MAX_NOM);
   gtk_table_attach(GTK_TABLE(table), entree, 
                     0, 1, 1, 2, 
                     GTK_FILL, GTK_FILL, 
                     0, 0);

   gtk_container_add(GTK_CONTAINER(content), table);

   gtk_widget_show_all(dialog);

   char *nom_joueur = g_malloc(MAX_NOM + 1);
   if (nom_joueur == NULL)
   {
      fprintf(stderr, "Erreur d'allocation mémoire pour le nom du joueur\n");
      gtk_widget_destroy(dialog);
      return NULL;
   }

   gint resultat = gtk_dialog_run(GTK_DIALOG(dialog));

   if (resultat == GTK_RESPONSE_ACCEPT)
   {
      const char *texte = gtk_entry_get_text(GTK_ENTRY(entree));
      printf("Nom entré : %s\n", texte);
      snprintf(nom_joueur, MAX_NOM + 1, "%s", texte);
   }
   else {
      g_free(nom_joueur);
      nom_joueur = NULL;
   }

   gtk_widget_destroy(dialog);
   return nom_joueur;
}

GtkWidget *creer_grille(Plateau *plateau)
{
   if (!plateau) {
      g_warning("Plateau NULL dans creer_grille");
      return NULL;
   }

   GtkWidget *grille = gtk_table_new(plateau->largeur, plateau->hauteur, TRUE);
   for (unsigned i = 0; i < (unsigned)plateau->hauteur; i++)
   {
      for (unsigned j = 0; j < (unsigned)plateau->largeur; j++)
      {
         GtkWidget *bouton = gtk_button_new();
         gtk_widget_set_size_request(bouton, 45, 45);

         if (!bouton)
         {
            fprintf(stderr, "Erreur lors de la création du bouton\n");
            return NULL;
         }

         
         gtk_table_attach(GTK_TABLE(grille), bouton, i, i + 1, j, j + 1,
                           GTK_FILL, GTK_FILL, 1, 1);



         g_signal_connect(G_OBJECT(bouton), "clicked", G_CALLBACK(maj_grille), plateau);

         int index = i * plateau->largeur + j;
         plateau->cases[index].image = bouton;         

         gtk_widget_show(bouton);
      }
   }

   gtk_widget_show(grille);
   return grille;
}

GtkWidget *creer_suivants_et_score(GtkWidget **boutons_suivants, GtkWidget **label_score,
                                 Plateau *plateau)
{
   GtkWidget *hbox = gtk_hbox_new(FALSE, 10);

   GtkWidget *label_suivant = gtk_label_new("Suivants : ");
   gtk_box_pack_start(GTK_BOX(hbox), label_suivant, FALSE, FALSE, 2);

   if (!plateau) {
      g_warning("Plateau invalide dans creer_suivants_et_score");
      return NULL;
   }

   switch (plateau->difficulte)
   {
   case 0:
      for(int i = 0; i < 3; i++)
      {
         boutons_suivants[i] = gtk_button_new();
         gtk_widget_set_size_request(boutons_suivants[i], 35,35);
         gtk_box_pack_start(GTK_BOX(hbox), boutons_suivants[i], FALSE, FALSE, 3);
      }
      break;
   case 1:
      for(int i = 0; i < 3; i++)
      {
         boutons_suivants[i] = gtk_button_new();
         gtk_widget_set_size_request(boutons_suivants[i], 40,40);
         gtk_box_pack_start(GTK_BOX(hbox), boutons_suivants[i], FALSE, FALSE, 3);
      }
      break;
   case 2:
      for(int i = 0; i < 5; i++)
      {
         boutons_suivants[i] = gtk_button_new();
         gtk_widget_set_size_request(boutons_suivants[i], 35,35);
         gtk_box_pack_start(GTK_BOX(hbox), boutons_suivants[i], FALSE, FALSE, 25);
      }
      break;
   default:
      fprintf(stderr, "Erreur: difficulté invalide dans creer_suivants_et_score\n");
      return NULL;
   }

   GtkWidget *label_s = gtk_label_new("Score : ");
   gtk_box_pack_start(GTK_BOX(hbox), label_s, FALSE, FALSE, 5);

   char score[32];
   sprintf(score, "%d", plateau->score.valeur);
   *label_score = gtk_label_new(score);
   gtk_box_pack_start(GTK_BOX(hbox), *label_score, FALSE, FALSE, 5);

   return hbox;
}
   

// --------------- Fonctions Afficher les diff choses dans Menu ---------------
void afficher_dialogue_scores(void)
{
   if (!fichier_scores)
   {
      fprintf(stderr, "Erreur: aucun fichier de scores défini\n");
      return;
   }

   Score scores[MAX_SCORES];
   int nb = 0;

   charger_scores(fichier_scores, scores, &nb);

   char message[512];
   int position = 0;
   int espace_restant = sizeof(message) - 1;

   if (nb == 0)
   {
      // snprintf + secure que sprintf
      snprintf(message, sizeof(message), "Aucun score enregistré.");
   }
   else
   {
      position = snprintf(message, sizeof(message), "Meilleurs scores :\n");
      espace_restant = sizeof(message) - position - 1;

      // Ajouter chaque score
      for (int i = 0; i < nb && espace_restant > 0; i++)
      {
         int chars_written = snprintf(message + position, espace_restant,
            "%d. %s: %d points\n", i + 1, scores[i].nom, scores[i].valeur);

         if (chars_written > 0)
         {
            position += chars_written;
            espace_restant -= chars_written;
         }
      }
   }

   GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(fenetre_principale),
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,
                                             "%s", message);

   gtk_window_set_title(GTK_WINDOW(dialog), "Meilleurs scores");
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
}

void afficher_dialogue_a_propos(void)
{
   GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                             GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                             "Five or More -- Qayyum Muhammad & gazouz Sami\n"
                                             "Cours INFO0030 -- 04/05/2025\n"
                                             "Version 1.0\n");
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
}

void afficher_message_perdu(GtkWidget *parent)
{
   GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,
                                             "Vous avez perdu !\n");
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
}



// ---------------- Fonctions Callback pour recréer la grille -----------------
void callback_trouver_bouton(GtkWidget *bouton_case, gpointer donnees_ptr)
{
   MiseAJour *donnees = donnees_ptr;

   GValue position_gauche = G_VALUE_INIT;
   GValue position_haut = G_VALUE_INIT;
   g_value_init(&position_gauche, G_TYPE_UINT);
   g_value_init(&position_haut, G_TYPE_UINT);

   GtkWidget *grille = gtk_widget_get_parent(bouton_case);

   gtk_container_child_get_property(GTK_CONTAINER(grille),
                                    bouton_case,
                                    "left-attach", &position_gauche);
   gtk_container_child_get_property(GTK_CONTAINER(grille),
                                    bouton_case,
                                    "top-attach", &position_haut);

   if ((unsigned)donnees->colonne_actuelle == g_value_get_uint(&position_gauche) &&
   (unsigned)donnees->ligne_actuelle == g_value_get_uint(&position_haut))
   {
      donnees->est_bouton = bouton_case;
   }
}

void callback_trouver_vbox(GtkWidget *widget, gpointer data)
{
   Data *donnees = data;

   if (!donnees->est_trouve && GTK_IS_BOX(widget))
   {
      donnees->est_widget = widget;
      donnees->est_trouve = TRUE;
   }
}

void callback_trouver_table(GtkWidget *widget, gpointer data)
{
   Data *d = data;

   if (!d->est_trouve && GTK_IS_TABLE(widget))
   {
      d->est_widget = widget;
      d->est_trouve = TRUE;
      gtk_widget_destroy(widget);
   }
}

void callback_connecter_signal_bouton(GtkWidget *bouton, gpointer data_plateau)
{
   g_signal_connect(G_OBJECT(bouton), "clicked", G_CALLBACK(maj_grille), data_plateau);
}

void connecter_signaux_grille(GtkWidget *grille, Plateau *plateau)
{
   gtk_container_foreach(GTK_CONTAINER(grille), callback_connecter_signal_bouton, plateau);
}

void afficher_dialogue_fin_de_partie(GtkWindow *parent, int score)
{
   if (!parent)
   {
      fprintf(stderr, "Erreur: parent NULL dans afficher_dialogue_fin_de_partie\n");
      return;
   }
   
   char message[128];
   snprintf(message, sizeof(message), "Partie terminée !\nVotre score : %d points\n", score);

   printf("Partie terminée !\nVotre score : %d points\n", score);

   GtkWidget *dialog = gtk_dialog_new_with_buttons(
      "Fin de partie",
      parent,
      GTK_DIALOG_MODAL,
      "Rejouer", GTK_RESPONSE_YES,
      "Quitter", GTK_RESPONSE_NO,
      NULL
   );

   GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
   GtkWidget *label = gtk_label_new(message);
   gtk_container_add(GTK_CONTAINER(content), label);
   gtk_widget_show_all(dialog);

   gint response = gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);

   if (response == GTK_RESPONSE_YES) {
      int niveau = plateau_actuel->difficulte;

   // Détruit l'ancien plateau
   if (plateau_actuel) {
      detruire_plateau(plateau_actuel);
      plateau_actuel = NULL;
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

   // Vérification critique
   if (!plateau_actuel || !plateau_actuel->boutons_suivants) {
      fprintf(stderr, "Erreur: échec de l'initialisation du plateau\n");
      return;
   }

   // Réinitialise le score
   plateau_actuel->score.valeur = 0;

   // Recrée l'interface
   recreer_grille(fenetre_principale, plateau_actuel);

   // Génère les boules
   generation_boules(plateau_actuel);
   preparer_boules_suivantes(plateau_actuel);
   maj_boutons_suivants(plateau_actuel->boutons_suivants, plateau_actuel);

   gtk_widget_show_all(fenetre_principale);

   } else {
      gtk_main_quit();
   }
}
