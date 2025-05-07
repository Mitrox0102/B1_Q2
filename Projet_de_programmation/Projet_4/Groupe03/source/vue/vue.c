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
extern GtkWidget *fenetre_principale;
extern GtkWidget *grille_actuelle;
extern char *fichier_scores;
char nom_joueur[MAX_NOM + 1] = "Joueur";
extern bool dialogue_fin_partie_affiche;
static bool redemarrage_en_cours = false;
static GtkWidget *dialogue_fin_partie = NULL;

GtkWidget *creer_fenetre(void)
{
   GtkWidget *F = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   if (!F)
   {
      fprintf(stderr, "Erreur lors de la création de la fenêtre principale\n");
      return NULL;
   }

   gtk_window_set_title(GTK_WINDOW(F), "Five");
   gtk_window_set_default_size(GTK_WINDOW(F), 700, 800);

   g_signal_connect(G_OBJECT(F), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   return F;
}

GtkWidget *creer_barre_outils(void)
{
   GtkWidget *menu_bar = gtk_menu_bar_new();
   if (!menu_bar)
   {
      fprintf(stderr, "Erreur lors de la création de la barre de menu\n");
      return NULL;
   }

   // --------------------- MENU PARTIE ---------------------
   GtkWidget *menu_partie = gtk_menu_new();
   if (!menu_partie)
   {
      fprintf(stderr, "Erreur lors de la création du menu Partie\n");
      return NULL;
   }

   GtkWidget *item_partie = gtk_menu_item_new_with_label("Partie");
   if (!item_partie)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Partie\n");
      return NULL;
   }

   GtkAccelGroup *accel_group = gtk_accel_group_new();
   gtk_window_add_accel_group(GTK_WINDOW(fenetre_principale), accel_group);


   GdkPixbuf *pixbuf_nouvelle =
      gdk_pixbuf_new_from_file_at_size("source/assets/images/new.png", 20, 20, NULL);
   if (!pixbuf_nouvelle)
   {
      fprintf(stderr, "Erreur lors du chargement de l'image nouvelle partie\n");
      return NULL;
   }

   GtkWidget *image_nouvelle = gtk_image_new_from_pixbuf(pixbuf_nouvelle);
   if (!image_nouvelle)
   {
      fprintf(stderr, "Erreur lors de la création de l'image nouvelle partie\n");
      g_object_unref(pixbuf_nouvelle);
      return NULL;
   }

   GtkWidget *item_nouvelle = gtk_image_menu_item_new_with_label("Nouvelle partie");
   if (!item_nouvelle)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Nouvelle partie\n");
      g_object_unref(pixbuf_nouvelle);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_nouvelle), image_nouvelle);

   gtk_widget_add_accelerator(item_nouvelle, "activate", accel_group,
      gdk_keyval_from_name("n"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);   


   GdkPixbuf *pixbuf_scores =
      gdk_pixbuf_new_from_file_at_size("source/assets/images/score.png", 20, 20, NULL);
   if (!pixbuf_scores)
   {
      fprintf(stderr, "Erreur lors du chargement de l'image meilleurs scores\n");
      g_object_unref(pixbuf_nouvelle);
      return NULL;
   }

   GtkWidget *image_scores = gtk_image_new_from_pixbuf(pixbuf_scores);
   if (!image_scores)
   {
      fprintf(stderr, "Erreur lors de la création de l'image meilleurs scores\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      return NULL;
   }

   GtkWidget *item_scores = gtk_image_menu_item_new_with_label("Meilleurs scores");
   if (!item_scores)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Meilleurs scores\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_scores), image_scores);

   gtk_widget_add_accelerator(item_scores,  "activate", accel_group, 
      gdk_keyval_from_name("s"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   GtkWidget *item_quitter = gtk_image_menu_item_new_with_label("Quitter");
   if (!item_quitter)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Quitter\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      return NULL;
   }

   GtkWidget *icon_quitter =
      gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_MENU);
   if (!icon_quitter)
   {
      fprintf(stderr, "Erreur lors de la création de l'icône Quitter\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_quitter), icon_quitter);

   gtk_widget_add_accelerator(item_quitter, "activate", accel_group, 
      gdk_keyval_from_name("q"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_nouvelle);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_scores);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_partie), item_quitter);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_partie), menu_partie);

   // --------------------- MENU NIVEAU ---------------------
   GtkWidget *menu_niveau = gtk_menu_new();
   if (!menu_niveau)
   {
      fprintf(stderr, "Erreur lors de la création du menu Niveau\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      return NULL;
   }

   GtkWidget *item_niveau = gtk_menu_item_new_with_label("Niveau");
   if (!item_niveau)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Niveau\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      return NULL;
   }

   GdkPixbuf *pixbuf_facile =
      gdk_pixbuf_new_from_file_at_size("source/assets/images/easy.png", 20, 20, NULL);
   if (!pixbuf_facile)
   {
      fprintf(stderr, "Erreur lors du chargement de l'image facile\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      return NULL;
   }

   GtkWidget *image_facile = gtk_image_new_from_pixbuf(pixbuf_facile);
   if (!image_facile)
   {
      fprintf(stderr, "Erreur lors de la création de l'image facile\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      return NULL;
   }

   GtkWidget *item_facile = gtk_image_menu_item_new_with_label("Facile");
   if (!item_facile)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Facile\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_facile), image_facile);

   gtk_widget_add_accelerator(item_facile,  "activate", accel_group, 
      gdk_keyval_from_name("0"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   GdkPixbuf *pixbuf_moyen =
      gdk_pixbuf_new_from_file_at_size("source/assets/images/mid.png", 20, 20, NULL);
   if (!pixbuf_moyen)
   {
      fprintf(stderr, "Erreur lors du chargement de l'image moyen\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      return NULL;
   }

   GtkWidget *image_moyen = gtk_image_new_from_pixbuf(pixbuf_moyen);
   if (!image_moyen)
   {
      fprintf(stderr, "Erreur lors de la création de l'image moyen\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      return NULL;
   }

   GtkWidget *item_moyen = gtk_image_menu_item_new_with_label("Moyen");
   if (!item_moyen)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Moyen\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_moyen), image_moyen);

   gtk_widget_add_accelerator(item_moyen,   "activate", accel_group, 
      gdk_keyval_from_name("1"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   GdkPixbuf *pixbuf_difficile =
      gdk_pixbuf_new_from_file_at_size("source/assets/images/hard.png", 20, 20, NULL);
   if (!pixbuf_difficile)
   {
      fprintf(stderr, "Erreur lors du chargement de l'image difficile\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      return NULL;
   }

   GtkWidget *image_difficile = gtk_image_new_from_pixbuf(pixbuf_difficile);
   if (!image_difficile)
   {
      fprintf(stderr, "Erreur lors de la création de l'image difficile\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      return NULL;
   }

   GtkWidget *item_difficile = gtk_image_menu_item_new_with_label("Difficile");
   if (!item_difficile)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Difficile\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_difficile), image_difficile);

   gtk_widget_add_accelerator(item_difficile, "activate", accel_group, 
      gdk_keyval_from_name("2"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_facile);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_moyen);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_niveau), item_difficile);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_niveau), menu_niveau);

   g_signal_connect(G_OBJECT(item_facile), "activate",
                     G_CALLBACK(changer_niveau), GINT_TO_POINTER(0));
   g_signal_connect(G_OBJECT(item_moyen), "activate",
                     G_CALLBACK(changer_niveau), GINT_TO_POINTER(1));
   g_signal_connect(G_OBJECT(item_difficile), "activate",
                     G_CALLBACK(changer_niveau), GINT_TO_POINTER(2));

   // --------------------- MENU AIDE ---------------------
   GtkWidget *menu_aide = gtk_menu_new();
   if (!menu_aide)
   {
      fprintf(stderr, "Erreur lors de la création du menu Aide\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      return NULL;
   }

   GtkWidget *item_aide = gtk_menu_item_new_with_label("Aide");
   if (!item_aide)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Aide\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      return NULL;
   }

   GdkPixbuf *pixbuf_apropos =
      gdk_pixbuf_new_from_file_at_size("source/assets/images/about.png", 20, 20, NULL);
   if (!pixbuf_apropos)
   {
      fprintf(stderr, "Erreur lors du chargement de l'image à propos\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      return NULL;
   }

   GtkWidget *image_apropos = gtk_image_new_from_pixbuf(pixbuf_apropos);
   if (!image_apropos)
   {
      fprintf(stderr, "Erreur lors de la création de l'image à propos\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      g_object_unref(pixbuf_apropos);
      return NULL;
   }

   GtkWidget *item_apropos = gtk_image_menu_item_new_with_label("À propos");
   if (!item_apropos)
   {
      fprintf(stderr, "Erreur lors de la création de l'item À propos\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      g_object_unref(pixbuf_apropos);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_apropos), image_apropos);

   gtk_widget_add_accelerator(item_apropos, "activate", accel_group, 
      gdk_keyval_from_name("a"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   GdkPixbuf *pixbuf_regles =
      gdk_pixbuf_new_from_file_at_size("source/assets/images/rules.png", 20, 20, NULL);
   if (!pixbuf_regles)
   {
      fprintf(stderr, "Erreur lors du chargement de l'image règles\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      g_object_unref(pixbuf_apropos);
      return NULL;
   }

   GtkWidget *image_regles = gtk_image_new_from_pixbuf(pixbuf_regles);
   if (!image_regles)
   {
      fprintf(stderr, "Erreur lors de la création de l'image règles\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      g_object_unref(pixbuf_apropos);
      g_object_unref(pixbuf_regles);
      return NULL;
   }

   GtkWidget *item_regles = gtk_image_menu_item_new_with_label("Règles");
   if (!item_regles)
   {
      fprintf(stderr, "Erreur lors de la création de l'item Règles\n");
      g_object_unref(pixbuf_nouvelle);
      g_object_unref(pixbuf_scores);
      g_object_unref(pixbuf_facile);
      g_object_unref(pixbuf_moyen);
      g_object_unref(pixbuf_difficile);
      g_object_unref(pixbuf_apropos);
      g_object_unref(pixbuf_regles);
      return NULL;
   }

   gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item_regles), image_regles);

   gtk_widget_add_accelerator(item_regles,  "activate", accel_group, 
      gdk_keyval_from_name("r"), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_aide), item_apropos);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_aide), item_regles);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_aide), menu_aide);

   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), item_partie);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), item_niveau);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), item_aide);

   g_signal_connect(G_OBJECT(item_nouvelle), "activate",
                     G_CALLBACK(nouvelle_partie), NULL);
   g_signal_connect(G_OBJECT(item_quitter), "activate",
                     G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(G_OBJECT(item_scores), "activate",
                     G_CALLBACK(afficher_meilleurs_scores), NULL);
   g_signal_connect(G_OBJECT(item_apropos), "activate",
                     G_CALLBACK(afficher_a_propos), NULL);
   g_signal_connect(G_OBJECT(item_regles), "activate",
                     G_CALLBACK(afficher_regles), NULL);

   return menu_bar;
}

char *demander_nom_joueur(void)
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
   if (!content)
   {
      fprintf(stderr, "Erreur lors de la récupération de la zone de "
                     "contenu du dialogue\n");
      gtk_widget_destroy(dialog);
      return NULL;
   }

   table = gtk_table_new(2, 1, FALSE);
   if (!table)
   {
      fprintf(stderr, "Erreur lors de la création de la table\n");
      gtk_widget_destroy(dialog);
      return NULL;
   }

   gtk_table_set_row_spacings(GTK_TABLE(table), 10);
   gtk_table_set_col_spacings(GTK_TABLE(table), 10);
   gtk_container_set_border_width(GTK_CONTAINER(table), 15);

   label = gtk_label_new("Entrez votre nom:");
   if (!label)
   {
      fprintf(stderr, "Erreur lors de la création du label\n");
      gtk_widget_destroy(dialog);
      return NULL;
   }

   gtk_table_attach(GTK_TABLE(table), label,
                  0, 1, 0, 1,
                  GTK_EXPAND | GTK_FILL, GTK_FILL, 0, 0);

   entree = gtk_entry_new();
   if (!entree)
   {
      fprintf(stderr, "Erreur lors de la création de l'entrée\n");
      gtk_widget_destroy(dialog);
      return NULL;
   }

   gtk_entry_set_text(GTK_ENTRY(entree), "Joueur");
   gtk_entry_set_max_length(GTK_ENTRY(entree), MAX_NOM);
   gtk_table_attach(GTK_TABLE(table), entree,
                     0, 1, 1, 2,
                     GTK_FILL, GTK_FILL,
                     0, 0);

   gtk_container_add(GTK_CONTAINER(content), table);

   gtk_widget_show_all(dialog);

   char *nom = g_malloc(MAX_NOM + 1);
   if (!nom)
   {
      fprintf(stderr, "Erreur d'allocation mémoire pour le nom du joueur\n");
      gtk_widget_destroy(dialog);
      return NULL;
   }

   gint resultat = gtk_dialog_run(GTK_DIALOG(dialog));

   if (resultat == GTK_RESPONSE_ACCEPT)
   {
      const char *texte = gtk_entry_get_text(GTK_ENTRY(entree));
      if (!texte)
      {
         fprintf(stderr, "Erreur lors de la récupération du texte de l'entrée\n");
         g_free(nom);
         gtk_widget_destroy(dialog);
         return NULL;
      }

      //printf("Nom entré : %s\n", texte);
      strncpy(nom, texte, MAX_NOM);
      nom[MAX_NOM] = '\0';
   }
   else
   {
      g_free(nom);
      nom = NULL;
   }

   gtk_widget_destroy(dialog);
   return nom;
}

GtkWidget *creer_grille(Plateau *plateau)
{
   if (!plateau)
   {
      g_warning("Plateau NULL dans creer_grille");
      return NULL;
   }

   int largeur = plateau_get_largeur(plateau);
   int hauteur = plateau_get_hauteur(plateau);

   GtkWidget *grille = gtk_table_new(largeur, hauteur, TRUE);
   if (!grille)
   {
      fprintf(stderr, "Erreur lors de la création de la grille\n");
      return NULL;
   }

   for (unsigned i = 0; i < (unsigned)hauteur; i++)
   {
      for (unsigned j = 0; j < (unsigned)largeur; j++)
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

         g_signal_connect(G_OBJECT(bouton), "clicked",
                           G_CALLBACK(maj_grille), plateau);

         Case *c = plateau_get_case(plateau, j, i);
         if (!c)
         {
            fprintf(stderr, "Erreur lors de la récupération de la case\n");
            gtk_widget_destroy(bouton);
            gtk_widget_destroy(grille);
            return NULL;
         }

         case_set_image(c, bouton);

         gtk_widget_show(bouton);
      }
   }

   gtk_widget_show(grille);
   return grille;
}

GtkWidget *creer_suivants_et_score(GtkWidget **boutons_suivants,
                                   GtkWidget **label_score, Plateau *plateau)
{
   if (!boutons_suivants || !label_score || !plateau)
   {
      fprintf(stderr, "Erreur: pointeur NULL dans creer_suivants_et_score\n");
      return NULL;
   }

   GtkWidget *hbox = gtk_hbox_new(FALSE, 10);
   if (!hbox)
   {
      fprintf(stderr, "Erreur lors de la création de la boîte horizontale\n");
      return NULL;
   }

   GtkWidget *label_suivant = gtk_label_new("Suivants : ");
   if (!label_suivant)
   {
      fprintf(stderr, "Erreur lors de la création du label Suivants\n");
      gtk_widget_destroy(hbox);
      return NULL;
   }

   gtk_box_pack_start(GTK_BOX(hbox), label_suivant, FALSE, FALSE, 2);

   if (!plateau)
   {
      g_warning("Plateau invalide dans creer_suivants_et_score");
      return NULL;
   }

   int difficulte = plateau_get_difficulte(plateau);
   int nb_suivantes = plateau_get_nb_suivantes(plateau);

   switch (difficulte)
   {
   case 0:
      for (int i = 0; i < nb_suivantes; i++)
      {
         boutons_suivants[i] = gtk_button_new();
         gtk_widget_set_size_request(boutons_suivants[i], 35, 35);
         gtk_box_pack_start(GTK_BOX(hbox), boutons_suivants[i], FALSE, FALSE, 3);
      }
      break;
   case 1:
      for (int i = 0; i < nb_suivantes; i++)
      {
         boutons_suivants[i] = gtk_button_new();
         gtk_widget_set_size_request(boutons_suivants[i], 40, 40);
         gtk_box_pack_start(GTK_BOX(hbox), boutons_suivants[i], FALSE, FALSE, 3);
      }
      break;
   case 2:
      for (int i = 0; i < nb_suivantes; i++)
      {
         boutons_suivants[i] = gtk_button_new();
         gtk_widget_set_size_request(boutons_suivants[i], 35, 35);
         gtk_box_pack_start(GTK_BOX(hbox), boutons_suivants[i], FALSE, FALSE, 25);
      }
      break;
   default:
      fprintf(stderr, "Erreur: difficulté invalide dans creer_suivants_et_score\n");
      return NULL;
   }

   GtkWidget *label_s = gtk_label_new("Score :");
   gtk_box_pack_start(GTK_BOX(hbox), label_s, FALSE, FALSE, 5);

   char score[32];
   int score_val = plateau_get_score_valeur(plateau);
   sprintf(score, "%d", score_val);
   *label_score = gtk_label_new(score);
   if (!*label_score)
   {
      fprintf(stderr, "Erreur lors de la création du label Score\n");
      gtk_widget_destroy(hbox);
      return NULL;
   }

   gtk_box_pack_start(GTK_BOX(hbox), *label_score, FALSE, FALSE, 5);

   // Stocker la référence globale au label du score
   label_score_global = *label_score;
   if (!label_score_global)
   {
      fprintf(stderr, "Erreur lors de la création du label du score global\n");
      gtk_widget_destroy(hbox);
      return NULL;
   }

   //printf("Label du score initialisé: %p\n", (void *)label_score_global);

   return hbox;
}

// Fonctions pour les dialogues
void afficher_dialogue_scores(void)
{
   if (!fichier_scores)
   {
      fprintf(stderr, "Erreur: aucun fichier de scores défini\n");
      return;
   }

   // Utiliser le type Score* (type opaque) directement
   Score *scores[MAX_SCORES];
   int nb = 0;

   // Appeler charger_scores avec le bon type
   FILE *fp = fopen(fichier_scores, "r");
   if (fp)
   {
      char nom_temp[MAX_NOM + 1];
      int valeur_temp;

      while (nb < MAX_SCORES && fscanf(fp, "%s %d", nom_temp, &valeur_temp) == 2)
      {
         // Créer un nouvel objet Score pour chaque entrée
         scores[nb] = score_create(nom_temp, valeur_temp);
         if (!scores[nb])
         {
            fprintf(stderr, "Erreur lors de la création d'un score\n");
            break;
         }
         nb++;
      }
      fclose(fp);
   }

   char message[512] = {0};
   int position = 0;
   int espace_restant = sizeof(message) - 1;

   if (nb == 0)
   {
      strncpy(message, "Aucun score enregistré.", sizeof(message) - 1);
   }
   else
   {
      position = snprintf(message, sizeof(message), "Meilleurs scores :\n");
      espace_restant = sizeof(message) - position - 1;

      // Utiliser les fonctions accesseurs
      for (int i = 0; i < nb && espace_restant > 0; i++)
      {
         const char *nom = score_get_nom(scores[i]);
         int valeur = score_get_valeur(scores[i]);

         int chars_written = snprintf(message + position, espace_restant,
                                    "%d. %s: %d points\n", i + 1, nom, valeur);

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
   if (!dialog)
   {
      fprintf(stderr, "Erreur lors de la création du dialogue des scores\n");
      return;
   }

   gtk_window_set_title(GTK_WINDOW(dialog), "Meilleurs scores");
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);

   // Libérer la mémoire des scores
   for (int i = 0; i < nb; i++)
   {
      score_destroy(scores[i]);
   }
}

void afficher_dialogue_a_propos(void)
{
   GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                             GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                             "Five or More -- Qayyum Muhammad & Ouazouz Sami\n"
                                             "Cours INFO0030 -- 04/05/2025\n"
                                             "Version 1.0\n");
   if (!dialog)
   {
      fprintf(stderr, "Erreur lors de la création du dialogue À propos\n");
      return;
   }

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
   if (!dialog)
   {
      fprintf(stderr, "Erreur lors de la création du dialogue de perte\n");
      return;
   }

   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
}

// Fonctions callback pour recréer la grille
void callback_trouver_bouton(GtkWidget *bouton_case, gpointer donnees_ptr)
{
   if (!bouton_case || !donnees_ptr)
   {
      fprintf(stderr, "Erreur: bouton_case ou donnees_ptr NULL.\n");
      return;
   }

   MiseAJour *donnees = donnees_ptr;
   if (!donnees)
   {
      fprintf(stderr, "Erreur: données NULL dans callback_trouver_bouton\n");
      return;
   }

   GValue position_gauche = G_VALUE_INIT;
   GValue position_haut = G_VALUE_INIT;
   g_value_init(&position_gauche, G_TYPE_UINT);
   g_value_init(&position_haut, G_TYPE_UINT);

   GtkWidget *grille = gtk_widget_get_parent(bouton_case);
   if (!grille)
   {
      fprintf(stderr, "Erreur: grille NULL dans callback_trouver_bouton\n");
      return;
   }

   gtk_container_child_get_property(GTK_CONTAINER(grille),
                                    bouton_case,
                                    "left-attach", &position_gauche);
   gtk_container_child_get_property(GTK_CONTAINER(grille),
                                    bouton_case,
                                    "top-attach", &position_haut);

   if ((unsigned)donnees->colonne_actuelle == g_value_get_uint(&position_gauche) && (unsigned)donnees->ligne_actuelle == g_value_get_uint(&position_haut))
   {
      donnees->est_bouton = bouton_case;
   }
}

void callback_trouver_vbox(GtkWidget *widget, gpointer data)
{
   if (!widget || !data)
   {
      fprintf(stderr, "Erreur: widget ou data NULL dans callback_trouver_vbox\n");
      return;
   }

   Data *donnees = data;
   if (!donnees)
   {
      fprintf(stderr, "Erreur: données NULL dans callback_trouver_vbox\n");
      return;
   }

   if (!donnees->est_trouve && GTK_IS_BOX(widget))
   {
      donnees->est_widget = widget;
      donnees->est_trouve = TRUE;
   }
}

void callback_trouver_table(GtkWidget *widget, gpointer data)
{
   if (!widget || !data)
   {
      fprintf(stderr, "Erreur: widget ou data NULL dans callback_trouver_table\n");
      return;
   }

   Data *d = data;
   if (!d)
   {
      fprintf(stderr, "Erreur: données NULL dans callback_trouver_table\n");
      return;
   }

   if (!d->est_trouve && GTK_IS_TABLE(widget))
   {
      d->est_widget = widget;
      d->est_trouve = TRUE;
      gtk_widget_destroy(widget);
   }
}

void callback_connecter_signal_bouton(GtkWidget *bouton, gpointer data_plateau)
{
   g_signal_connect(G_OBJECT(bouton), "clicked",
                     G_CALLBACK(maj_grille), data_plateau);
}

void connecter_signaux_grille(GtkWidget *grille, Plateau *plateau)
{
   if (!grille || !plateau)
   {
      fprintf(stderr, "Erreur: grille ou plateau NULL dans connecter_signaux_grille\n");
      return;
   }

   gtk_container_foreach(GTK_CONTAINER(grille),
                        callback_connecter_signal_bouton, plateau);
}

void callback_nouvelle_partie(GtkWidget *button, gpointer dialog)
{
   (void)button;

   if (dialog && GTK_IS_WIDGET(dialog))
   {
      gtk_widget_destroy(GTK_WIDGET(dialog));
   }

   redemarrer_jeu(NULL, NULL);

   if (fenetre_principale)
      gtk_widget_show_all(fenetre_principale);
}

static void dialogue_detruit(GtkWidget *widget, gpointer data)
{
   (void)widget;
   (void)data;
   dialogue_fin_partie = NULL;
}

void afficher_dialogue_fin_de_partie(GtkWindow *parent, int score)
{
   if (!parent)
   {
      fprintf(stderr, "Erreur: parent NULL dans afficher_dialogue_fin_de_partie\n");
      return;
   }

   // Si un dialogue est déjà visible, ne rien faire
   if (dialogue_fin_partie != NULL)
   {
      return;
   }

   dialogue_fin_partie = gtk_dialog_new_with_buttons("Partie terminée !",
                                                   parent,
                                                   GTK_DIALOG_MODAL,
                                                   NULL);

   GtkWidget *zone_contenu = gtk_dialog_get_content_area(GTK_DIALOG(dialogue_fin_partie));

   char texte_score[100];
   snprintf(texte_score, sizeof(texte_score), "Votre score : %d points", score);

   GtkWidget *label = gtk_label_new(texte_score);
   gtk_container_add(GTK_CONTAINER(zone_contenu), label);

   GtkWidget *bouton_rejouer = gtk_button_new_with_label("Rejouer");
   GtkWidget *bouton_quitter = gtk_button_new_with_label("Quitter");

   gtk_dialog_add_action_widget(GTK_DIALOG(dialogue_fin_partie),
                                 bouton_rejouer, GTK_RESPONSE_ACCEPT);
   gtk_dialog_add_action_widget(GTK_DIALOG(dialogue_fin_partie),
                                 bouton_quitter, GTK_RESPONSE_CANCEL);

   g_signal_connect(bouton_rejouer, "clicked",
                     G_CALLBACK(callback_nouvelle_partie), dialogue_fin_partie);
   g_signal_connect(bouton_quitter, "clicked",
                     G_CALLBACK(gtk_main_quit), NULL);

   // Connecter un signal pour réinitialiser le pointeur quand le dialogue est détruit
   g_signal_connect(dialogue_fin_partie, "destroy",
                     G_CALLBACK(dialogue_detruit), NULL);

   // Afficher le dialogue
   gtk_widget_show_all(dialogue_fin_partie);
}

void afficher_dialogue_regles(void)
{
   GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(fenetre_principale),
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,
                                             "Règles du jeu:\n\n"
                                             "- Le but est d'aligner au moins 5 boules de même couleur\n"
                                             "- À chaque tour, de nouvelles boules apparaissent\n"
                                             "- Déplacez les boules en cliquant d'abord sur une boule, puis sur sa destination\n"
                                             "- Un déplacement n'est possible que s'il existe un chemin libre\n"
                                             "- La partie se termine quand le plateau est plein");
   if (!dialog)
   {
      fprintf(stderr, "Erreur lors de la création du dialogue des règles\n");
      return;
   }

   gtk_window_set_title(GTK_WINDOW(dialog), "Règles du jeu");
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
}
static void deconnecter_signaux_enfant(GtkWidget *enfant, gpointer data)
{
   if (GTK_IS_WIDGET(enfant))
   {
      g_signal_handlers_disconnect_matched(
         enfant, G_SIGNAL_MATCH_DATA, 0, 0, NULL, NULL, data);
   }
}

void redemarrer_jeu(GtkWidget *widget, gpointer data)
{
   (void)widget;
   (void)data;

   if (!plateau_actuel)
   {
      fprintf(stderr, "Erreur: plateau_actuel est NULL dans redemarrer_jeu\n");
      return;
   }

   if (redemarrage_en_cours)
      return;

   redemarrage_en_cours = true;

   // Sauvegarder paramètres importants de façon sécurisée
   int difficulte = plateau_get_difficulte(plateau_actuel);
   char nom_joueur[MAX_NOM + 1] = {0};
   dialogue_fin_partie_affiche = false;

   const char *nom_source = plateau_get_score_nom(plateau_actuel);
   if (nom_source)
   {
      strncpy(nom_joueur, nom_source, MAX_NOM);
      nom_joueur[MAX_NOM] = '\0';
   }
   else
   {
      strcpy(nom_joueur, "Joueur");
   }

   if (grille_actuelle)
   {
      if (GTK_IS_WIDGET(grille_actuelle))
      {
         if (GTK_IS_CONTAINER(grille_actuelle))
         {
            // Utiliser gtk_container_foreach au lieu de GList
            gtk_container_foreach(GTK_CONTAINER(grille_actuelle),
                                 deconnecter_signaux_enfant,
                                 plateau_actuel);
         }

         gtk_widget_destroy(grille_actuelle);
      }
      grille_actuelle = NULL;
   }

   // Détruire proprement le plateau en préservant les paramètres importants
   if (plateau_actuel)
   {
      if (plateau_get_boutons_suivants(plateau_actuel))
      {
         detruire_boules_suivantes(plateau_actuel);
      }

      detruire_plateau(plateau_actuel);
      plateau_actuel = NULL;
   }

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
      fprintf(stderr, "Difficulté inconnue, utilisation de la difficulté 0\n");
      plateau_actuel = creer_plateau(fenetre_principale, 7, 7, 5, 3, 0);
      break;
   }

   if (!plateau_actuel)
   {
      fprintf(stderr, "Erreur: échec de création du nouveau plateau\n");
      return;
   }

   plateau_set_score_nom(plateau_actuel, nom_joueur);

   recreer_grille(fenetre_principale, plateau_actuel);

   generation_boules(plateau_actuel);

   preparer_boules_suivantes(plateau_actuel);

   GtkWidget **boutons_suivants = plateau_get_boutons_suivants(plateau_actuel);
   if (boutons_suivants)
   {
      maj_boutons_suivants(boutons_suivants, plateau_actuel);
   }
   else
   {
      fprintf(stderr, "Avertissement: boutons_suivants est NULL après recreer_grille\n");
   }

   if (fenetre_principale && GTK_IS_WIDGET(fenetre_principale))
   {
      gtk_widget_show_all(fenetre_principale);
   }

   redemarrage_en_cours = false;
}
