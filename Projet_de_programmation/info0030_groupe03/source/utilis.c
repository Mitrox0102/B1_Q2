#include <stdio.h>
#include <stdbool.h>
#include "utilis.h"
#include "modele/modele.h"
#include "vue/vue.h"
#include <gtk/gtk.h>

extern GtkWidget *fenetre_principale;

int generer_difficulte(Plateau *plateau)
{
   if (!plateau)
   {
      fprintf(stderr, "Erreur: le plateau est NULL.\n");
      return -1;
   }

   if(plateau->difficulte == 0){
      return 0;
   } else if(plateau->difficulte == 1){
      return 1;
   } else if(plateau->difficulte == 2){
      return 2;
   }else{
      fprintf(stderr, "Erreur: difficulté invalide.\n");
      return -1;
   }
}

GtkWidget *charger_image_button(const char *chemin_image) {
   GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file(chemin_image, NULL);
   if (pb_temp == NULL) {
      fprintf(stderr, "Erreur de chargement de l'image %s!\n", chemin_image);
      return NULL;
   }

   
   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, 30, 30, GDK_INTERP_BILINEAR);
   g_object_unref(pb_temp);
   if (pb == NULL) {
      fprintf(stderr, "Erreur lors de la redimension de l'image!\n");
      return NULL;
   }

   GtkWidget *pBouton = gtk_button_new();
   if (pBouton == NULL) {
      g_object_unref(pb);
      fprintf(stderr, "Erreur lors de la création du bouton\n");
      return NULL;
   }

   GtkWidget *image = gtk_image_new_from_pixbuf(pb);
   g_object_unref(pb);
   if (image == NULL) {
      fprintf(stderr, "Erreur lors de la création de l'image\n");
      return NULL;
   }

   gtk_button_set_image(GTK_BUTTON(pBouton), image);
   gtk_widget_set_size_request(pBouton, 30, 30);

   return pBouton;
}



void mettre_a_jour_score(GtkWidget *label, int score) {
   char buffer[32];
   snprintf(buffer, sizeof(buffer), "%d", score);
   gtk_label_set_text(GTK_LABEL(label), buffer);
}

const char *get_image_from_color(Couleur couleur)
{

   if (couleur < 0 || couleur > 6)
   {
      couleur = couleur % 7;
   }

   switch (couleur)
   {
   case BLEU:
      return "assets/images/blue.png";
   case CYAN:
      return "assets/images/cyan.png";
   case VERT:
      return "assets/images/green.png";
   case ORANGE:
      return "assets/images/orange.png";
   case MAUVE:
      return "assets/images/purple.png";
   case ROUGE:
      return "assets/images/red.png";
   case JAUNE:
      return "assets/images/yellow.png";
   default:
      fprintf(stderr, "Erreur: couleur inconnue (%d).\n", couleur);
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

   int cases_a_remplir = plateau->symboles_par_tour;

   srand(time(NULL));

   int total_cases = plateau->largeur * plateau->hauteur;
   int cases_libres= 0;

   for (int i = 0; i < total_cases; i++){
      if (plateau->cases[i].occupe == false){
         cases_libres++;
      }
   }

   int places_vides = cases_a_remplir;

   while (places_vides > 0)
   {
      int x = rand() % plateau->largeur;
      int y = rand() % plateau->hauteur;
      int index = y * plateau->largeur + x;

   
      if (plateau->cases[index].occupe == false)
      {
         Couleur couleur = rand() % plateau->nb_types_symboles;
         const char *chemin = get_image_from_color(couleur);
         GtkWidget *temp_bouton = charger_image_button(chemin);
         if (!temp_bouton) {
            fprintf(stderr, "Erreur lors de la génération de l’image via charger_image_button.\n");
            continue;
         }

         GtkWidget *image = gtk_button_get_image(GTK_BUTTON(temp_bouton));
         if (!image) {
            fprintf(stderr, "Erreur : aucune image trouvée dans le bouton temporaire.\n");
            continue;
         }

         GtkWidget *bouton_existant = plateau->cases[index].image;
         if (!GTK_IS_BUTTON(bouton_existant)) {
            fprintf(stderr, "Erreur : case %d ne contient pas un GtkButton.\n", index);
            continue;
         }

         gtk_button_set_image(GTK_BUTTON(bouton_existant), image);

         plateau->cases[index].col = couleur;
         plateau->cases[index].occupe = true;
         places_vides--;
      }
   }
   if (cases_libres < cases_a_remplir) {
      fprintf(stderr, "Plus de place sur le plateau : partie terminée.\n");
      afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), plateau->score.valeur);
      return;
   }
}

void preparer_boules_suivantes(Plateau *p)
{
   for (int i = 0; i < p->nb_suivantes; i++) {
      p->boules_suivantes[i].col = rand() % p->nb_types_symboles;
   }
}

void maj_boutons_suivants(GtkWidget **boutons_suivants, Plateau *p)
{
   if (!p) {
      fprintf(stderr, "Erreur : pointeur Plateau nul dans maj_boutons_suivants\n");
      return;
   }
   if (!boutons_suivants) {
      fprintf(stderr, "Erreur : pointeur boutons_suivants nul dans maj_boutons_suivants\n");
      return;
   }
   if (p->nb_suivantes <= 0) {
      fprintf(stderr, "Erreur : nb_suivantes incohérent (%d)\n", p->nb_suivantes);
      return;
   }

   for (int i = 0; i < p->nb_suivantes; i++) {
      if (!boutons_suivants[i]) continue;

      const char *chemin = get_image_from_color(p->boules_suivantes[i].col);
      if (!chemin) {
         fprintf(stderr, "Erreur lors de la génération de l’image via get_image_from_color.\n");
         continue;
      }

      // Charger l'image en Pixbuf
      GdkPixbuf *pixbuf_original = gdk_pixbuf_new_from_file(chemin, NULL);
      if (!pixbuf_original) {
         g_warning("Erreur de chargement d'image : %s", chemin);
         continue;
      }

      GdkPixbuf *pixbuf_redim = NULL;

      // Redimensionner l'image à la taille appropriée
      switch (p->difficulte)
      {
      case 0:
      case 2:
      pixbuf_redim = gdk_pixbuf_scale_simple(pixbuf_original, 20, 20, GDK_INTERP_BILINEAR);
         break;
      case 1:
      pixbuf_redim = gdk_pixbuf_scale_simple(pixbuf_original, 25, 25, GDK_INTERP_BILINEAR);
         break;
      default:
         fprintf(stderr, "Erreur: difficulté invalide dans maj_boutons_suivants\n");
         break;
      }
      g_object_unref(pixbuf_original);

      if (!pixbuf_redim) {
         g_warning("Erreur de redimensionnement !");
         continue;
      }

      // Créer un GtkImage avec la bonne taille
      GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf_redim);
      g_object_unref(pixbuf_redim); // Libère après création du GtkImage

      if (GTK_IS_BUTTON(boutons_suivants[i])) {
         gtk_button_set_image(GTK_BUTTON(boutons_suivants[i]), image);
      }else {
         fprintf(stderr, "Erreur : bouton_suivants[%d] n’est pas un GtkButton\n", i);
      }
   }
}


void generation_boules_depuis_liste(Plateau *p, int boules_a_placer)
{
   if (!p) return;

   int libres = 0;
   int total = p->largeur * p->hauteur;
   for (int i = 0; i < total; i++) {
      if (!p->cases[i].occupe) libres++;
   }
   if (libres < boules_a_placer) {
      afficher_dialogue_fin_de_partie(GTK_WINDOW(fenetre_principale), p->score.valeur);
      return;
   }

   if (p->largeur * p->hauteur - p->nb_cases_remplies < boules_a_placer) {
      return;
   }

   while (boules_a_placer > 0)
   {
      int x = rand() % p->largeur;
      int y = rand() % p->hauteur;
      int index = y * p->largeur + x;

      if (p->cases[index].occupe == false)
      {
         p->cases[index].col = p->boules_suivantes[boules_a_placer-1].col;
         p->cases[index].occupe = true;

         const char *chemin = get_image_from_color(p->cases[index].col);
         if (!chemin) {
            fprintf(stderr, "Erreur lors de la génération de l’image via get_image_from_color.\n");
            continue;
         }

         GtkWidget *temp_bouton = charger_image_button(chemin);
         if (!temp_bouton) {
            fprintf(stderr, "Erreur lors de la génération de l’image via charger_image_button.\n");
            continue;
         }

         GtkWidget *image = gtk_button_get_image(GTK_BUTTON(temp_bouton));
         if (!image) {
            fprintf(stderr, "Erreur : aucune image trouvée dans le bouton temporaire.\n");
            continue;
         }

         GtkWidget *bouton_existant = p->cases[index].image;
         if (!GTK_IS_BUTTON(bouton_existant)) {
            fprintf(stderr, "Erreur : case %d ne contient pas un GtkButton.\n", index);
            continue;
         }

         gtk_button_set_image(GTK_BUTTON(bouton_existant), image);

         boules_a_placer--;
      }
   }
}

void detruire_boules_suivantes(Plateau *p)
{
   if (!p) return;
   
   if (p->boutons_suivants) {
      for (int i = 0; i < p->nb_suivantes; i++) {
         if (p->boutons_suivants[i] && GTK_IS_WIDGET(p->boutons_suivants[i])) {
            gtk_widget_destroy(p->boutons_suivants[i]);
         }
      }
      g_free(p->boutons_suivants);
      p->boutons_suivants = NULL;
   }
}


