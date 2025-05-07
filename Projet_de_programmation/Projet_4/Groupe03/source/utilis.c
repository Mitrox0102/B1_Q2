#include <stdio.h>
#include <stdbool.h>
#include "utilis.h"
#include "vue/vue.h"
#include <gtk/gtk.h>

extern GtkWidget *fenetre_principale;

const char *recuperer_nom_joueur(void)
{
   return plateau_get_score_nom(plateau_actuel);
}


int generer_difficulte(Plateau *plateau)
{
   if (!plateau)
   {
      fprintf(stderr, "Erreur: le plateau est NULL.\n");
      return -1;
   }

   int difficulte = plateau_get_difficulte(plateau);

   if (difficulte == 0)
   {
      return 0;
   }
   else if (difficulte == 1)
   {
      return 1;
   }
   else if (difficulte == 2)
   {
      return 2;
   }
   else
   {
      fprintf(stderr, "Erreur: difficulté invalide.\n");
      return -1;
   }
}

bool est_benoit_donnet(const char *nom) {
   if (!nom) 
      return false;

   return strcmp(nom, "Benoit Donnet") == 0;
}

GtkWidget *charger_image_button(const char *chemin_image)
{
   if (!chemin_image)
   {
      fprintf(stderr, "Erreur: chemin_image est NULL dans charger_image_button\n");
      return NULL;
   }

   GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file(chemin_image, NULL);
   if (pb_temp == NULL)
   {
      fprintf(stderr, "Erreur de chargement de l'image %s!\n", chemin_image);
      return NULL;
   }

   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, 30, 30, GDK_INTERP_BILINEAR);
   g_object_unref(pb_temp);
   if (pb == NULL)
   {
      fprintf(stderr, "Erreur lors de la redimension de l'image!\n");
      return NULL;
   }

   GtkWidget *pBouton = gtk_button_new();
   if (pBouton == NULL)
   {
      g_object_unref(pb);
      fprintf(stderr, "Erreur lors de la création du bouton\n");
      return NULL;
   }

   GtkWidget *image = gtk_image_new_from_pixbuf(pb);
   g_object_unref(pb);
   if (image == NULL)
   {
      fprintf(stderr, "Erreur lors de la création de l'image\n");
      return NULL;
   }

   gtk_button_set_image(GTK_BUTTON(pBouton), image);
   gtk_widget_set_size_request(pBouton, 30, 30);

   return pBouton;
}

void mettre_a_jour_score(GtkWidget *label, int score)
{
   if (!label || !GTK_IS_LABEL(label) || score < 0)
   {
      fprintf(stderr, "Erreur: label invalide dans mettre_a_jour_score\n");
      return;
   }

   char buffer[32];
   snprintf(buffer, sizeof(buffer), "%d", score);
   gtk_label_set_text(GTK_LABEL(label), buffer);
}

const char *get_image_from_color(Couleur couleur)
{
   switch (couleur)
   {
   case BLEU:
      return IMAGE_BLUE;
   case CYAN:
      return IMAGE_CYAN;
   case VERT:
      return IMAGE_GREEN;
   case ORANGE:
      return IMAGE_ORANGE;
   case MAUVE:
      return IMAGE_PURPLE;
   case ROUGE:
      return IMAGE_RED;
   case JAUNE:
      return IMAGE_YELLOW;
   case C:
      return IMAGE_C;
   case C_SHARP:
      return IMAGE_C_SHARP;
   case HTML:
      return IMAGE_HTML;
   case JS:
      return IMAGE_JAVASCRIPT;
   case PYTHON:
      return IMAGE_PYTHON;
   default:
      fprintf(stderr, "Erreur: couleur inconnue dans get_image_from_color\n");
      return NULL;
   }
}

void generation_boules(Plateau *plateau)
{
   if (!plateau)
   {
      fprintf(stderr, "Erreur: le plateau est NULL.\n");
      return;
   }

   int cases_a_remplir = plateau_get_symboles_par_tour(plateau);
   int largeur = plateau_get_largeur(plateau);
   int hauteur = plateau_get_hauteur(plateau);
   int nb_types = plateau_get_nb_types_symboles(plateau);

   srand(time(NULL));

   // Compter les cases libres
   int cases_libres = 0;
   for (int i = 0; i < hauteur; i++)
   {
      for (int j = 0; j < largeur; j++)
      {
         Case *c = plateau_get_case(plateau, j, i);
         if (!case_est_occupe(c))
         {
            cases_libres++;
         }
      }
   }

   int places_vides = cases_a_remplir;

   while (places_vides > 0)
   {
      int x = rand() % largeur;
      int y = rand() % hauteur;
      Case *c = plateau_get_case(plateau, x, y);

      if (!case_est_occupe(c))
      {
         Couleur couleur;
         if (est_benoit_donnet(recuperer_nom_joueur()))
         {
            couleur = 7 + rand() % 5;
            //printf("Wow, c'est Benoit Donnet !\n");
         }else{
            couleur = rand() % nb_types;}
         const char *chemin = get_image_from_color(couleur);
         GtkWidget *temp_bouton = charger_image_button(chemin);

         if (!temp_bouton)
         {
            fprintf(stderr, "Erreur lors de la génération de l'image.\n");
            continue;
         }

         GtkWidget *image = gtk_button_get_image(GTK_BUTTON(temp_bouton));
         if (!image)
         {
            fprintf(stderr, "Erreur : aucune image trouvée dans le bouton temporaire.\n");
            continue;
         }

         GtkWidget *bouton_existant = case_get_image(c);
         if (!GTK_IS_BUTTON(bouton_existant))
         {
            fprintf(stderr, "Erreur : case (%d,%d) ne contient pas un GtkButton.\n", x, y);
            continue;
         }

         gtk_button_set_image(GTK_BUTTON(bouton_existant), image);

         case_set_couleur(c, couleur);
         case_set_occupe(c, true);
         plateau_set_nb_cases_remplies(plateau, plateau_get_nb_cases_remplies(plateau) + 1);
         places_vides--;
      }
   }

   if (cases_libres < cases_a_remplir)
   {
      //fprintf(stderr, "Plus de place sur le plateau : partie terminée.\n");
      int score = plateau_get_score_valeur(plateau);
      afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), score);
      return;
   }

   int nb_cases_remplies = plateau_get_nb_cases_remplies(plateau);
   int total_cases = largeur * hauteur;

   if (nb_cases_remplies > cases_a_remplir && total_cases - nb_cases_remplies 
      < plateau_get_symboles_par_tour(plateau))
   {
      int score = plateau_get_score_valeur(plateau);
      //printf("Plus assez de cases libres après génération! Fin de partie.\n");
      afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), score);
      return;
   }
}

void preparer_boules_suivantes(Plateau *p)
{
   if (!p)
      return;

   int nb_suivantes = plateau_get_nb_suivantes(p);
   int nb_types = plateau_get_nb_types_symboles(p);

   for (int i = 0; i < nb_suivantes; i++)
   {
      Couleur nouvelle_couleur;
      if(est_benoit_donnet(recuperer_nom_joueur()))
      {
         nouvelle_couleur = 7 + rand() % 5;
         //printf("Wow, c'est Benoit Donnet !\n");
      }else{
         nouvelle_couleur = rand() % nb_types;}

      plateau_set_boule_suivante_couleur(p, i, nouvelle_couleur);
   }
}

void maj_boutons_suivants(GtkWidget **boutons_suivants, Plateau *p)
{
   if (!p || !boutons_suivants)
   {
      fprintf(stderr, "Erreur : pointeur nul dans maj_boutons_suivants\n");
      return;
   }

   int nb_suivantes = plateau_get_nb_suivantes(p);
   if (nb_suivantes <= 0)
   {
      fprintf(stderr, "Erreur : nb_suivantes incohérent (%d)\n", nb_suivantes);
      return;
   }

   int difficulte = plateau_get_difficulte(p);

   // S'assurer que les boutons sont correctement initialisés
   GtkWidget **boutons_stored = plateau_get_boutons_suivants(p);
   if (!boutons_stored)
   {
      fprintf(stderr, "Erreur: boutons_stored est NULL\n");
      plateau_set_boutons_suivants(p, boutons_suivants);
   }
   else if (boutons_stored != boutons_suivants)
   {
      fprintf(stderr, "Attention: tableau de boutons différent\n");
      plateau_set_boutons_suivants(p, boutons_suivants);
   }

   for (int i = 0; i < nb_suivantes; i++)
   {
      // Bloc d'initialisation des boutons si nécessaire
      if (!boutons_suivants[i] || !GTK_IS_BUTTON(boutons_suivants[i]))
      {
         fprintf(stderr, "Avertissement: bouton suivant %d invalide, "
            "création d'un nouveau\n", i);
         boutons_suivants[i] = gtk_button_new();
         if (!boutons_suivants[i])
         {
            fprintf(stderr, "Erreur critique: création du bouton %d a échoué\n", i);
            continue;
         }
         gtk_widget_show(boutons_suivants[i]); // S'assurer que le bouton est visible
      }

      // Récupérer la couleur de la boule suivante
      Couleur couleur = plateau_get_boule_suivante_couleur(p, i);
      const char *chemin = get_image_from_color(couleur);
      if (!chemin)
      {
         fprintf(stderr, "Erreur lors de la génération de l'image.\n");
         continue;
      }

      // Reste du code pour afficher l'image (inchangé)...
      GdkPixbuf *pixbuf_original = gdk_pixbuf_new_from_file(chemin, NULL);
      if (!pixbuf_original)
      {
         g_warning("Erreur de chargement d'image : %s", chemin);
         continue;
      }

      GdkPixbuf *pixbuf_redim = NULL;
      switch (difficulte)
      {
      case 0:
      case 2:
         pixbuf_redim = gdk_pixbuf_scale_simple(pixbuf_original, 20, 20, 
            GDK_INTERP_BILINEAR);
         break;
      case 1:
         pixbuf_redim = gdk_pixbuf_scale_simple(pixbuf_original, 25, 25, 
            GDK_INTERP_BILINEAR);
         break;
      default:
         fprintf(stderr, "Erreur: difficulté invalide dans maj_boutons_suivants\n");
         pixbuf_redim = gdk_pixbuf_scale_simple(pixbuf_original, 20, 20, 
            GDK_INTERP_BILINEAR);
         break;
      }
      g_object_unref(pixbuf_original);

      if (!pixbuf_redim)
      {
         g_warning("Erreur de redimensionnement !");
         continue;
      }

      // Créer une nouvelle image à chaque fois
      GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf_redim);
      g_object_unref(pixbuf_redim);

      if (GTK_IS_BUTTON(boutons_suivants[i]))
      {
         gtk_button_set_image(GTK_BUTTON(boutons_suivants[i]), image);

         gtk_widget_show_all(boutons_suivants[i]);
      }
   }
}

void generation_boules_depuis_liste(Plateau *p, int boules_a_placer)
{
   if (!p)
      return;

   int largeur = plateau_get_largeur(p);
   int hauteur = plateau_get_hauteur(p);
   int total_cases = largeur * hauteur;
   int nb_cases_remplies = plateau_get_nb_cases_remplies(p);

   int libres = 0;

   // Compter les cases libres
   for (int i = 0; i < hauteur; i++)
   {
      for (int j = 0; j < largeur; j++)
      {
         Case *c = plateau_get_case(p, j, i);
         if (!case_est_occupe(c))
         {
            libres++;
         }
      }
   }

   // Si pas assez de cases libres pour placer les boules, partie terminée
   if (libres < boules_a_placer)
   {
      int score = plateau_get_score_valeur(p);
      //printf("Plus assez de cases libres! Fin de partie.\n");
      afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), score);
      return;
   }

   // Placement des boules
   while (boules_a_placer > 0)
   {
      int x = rand() % largeur;
      int y = rand() % hauteur;
      Case *c = plateau_get_case(p, x, y);

      if (!case_est_occupe(c))
      {
         Couleur couleur = plateau_get_boule_suivante_couleur(p, boules_a_placer - 1);
         case_set_couleur(c, couleur);
         case_set_occupe(c, true);
         nb_cases_remplies++; // Incrémenter le compteur de cases remplies

         if (total_cases - nb_cases_remplies < boules_a_placer - 1)
         {
            int score = plateau_get_score_valeur(p);
            //printf("Plus assez de cases libres! Fin de partie.\n");
            afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), score);
            return;
         }

         plateau_set_nb_cases_remplies(p, nb_cases_remplies);

         const char *chemin = get_image_from_color(couleur);
         if (!chemin)
         {
            fprintf(stderr, "Erreur lors de la génération de l'image.\n");
            continue;
         }

         GtkWidget *temp_bouton = charger_image_button(chemin);
         if (!temp_bouton)
         {
            fprintf(stderr, "Erreur lors de la génération de l'image.\n");
            continue;
         }

         GtkWidget *image = gtk_button_get_image(GTK_BUTTON(temp_bouton));
         if (!image)
         {
            fprintf(stderr, "Erreur : aucune image trouvée dans le bouton "
               "temporaire.\n");
            continue;
         }

         GtkWidget *bouton_existant = case_get_image(c);
         if (!GTK_IS_BUTTON(bouton_existant))
         {
            fprintf(stderr, "Erreur : case (%d,%d) ne contient pas un "
               "GtkButton.\n", x, y);
            continue;
         }

         gtk_button_set_image(GTK_BUTTON(bouton_existant), image);
         boules_a_placer--;
      }
   }

   // Vérifier s'il y a des alignements avec les nouvelles boules
   bool alignements_trouves = verifier_lignes(p);
   if (alignements_trouves)
   {
      //printf("Des alignements ont été trouvés et supprimés\n");
   }

   // Vérifier si le plateau est plein après placement des boules
   int cases_restantes = total_cases - nb_cases_remplies;
   int prochain_tour = plateau_get_symboles_par_tour(p);
   if (cases_restantes < prochain_tour)
   {
      int score = plateau_get_score_valeur(p);
      //printf("Plus assez de cases libres! Fin de partie.\n");
      afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), score);
      return;
   }
}

void detruire_boules_suivantes(Plateau *p)
{
   if (!p)
      return;

   GtkWidget **boutons = plateau_get_boutons_suivants(p);
   if (!boutons)
      return;

   int nb_suivantes = plateau_get_nb_suivantes(p);

   for (int i = 0; i < nb_suivantes; i++)
   {
      GtkWidget *bouton = boutons[i];
      if (bouton && G_IS_OBJECT(bouton) && GTK_IS_WIDGET(bouton))
      {
         GtkWidget *parent = gtk_widget_get_parent(bouton);
         if (!parent || !GTK_IS_CONTAINER(parent))
         {
            gtk_widget_destroy(bouton);
         }

         boutons[i] = NULL;
      }
   }
}