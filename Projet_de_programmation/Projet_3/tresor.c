#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "tresor.h"

GtkWidget *creer_fenetre(void){
   GtkWidget *pF = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pF), "Les Boxes");
   gtk_window_set_default_size(GTK_WINDOW(pF), 320, 200);
   gtk_window_set_position(GTK_WINDOW(pF), GTK_WIN_POS_CENTER);
   g_signal_connect(G_OBJECT(pF), "destroy",
   G_CALLBACK(gtk_main_quit), NULL);
   return pF;
   }

void on_button_clicked(GtkWidget *widget, gpointer data) {
   (void) widget;
   
   g_print("Bouton activé !\n");
   // Pour tester que data contient bien le label
   GtkWidget *label = (GtkWidget*)data;
   gtk_label_set_text(GTK_LABEL(label), "Bouton cliqué !");
}

void detruire_fenetre(GtkWidget *pW, gpointer data){
   (void) pW;
   (void) data;
   gtk_main_quit();
}

void mise_a_jour(GtkWidget *pLabel, int v, int d){
   if(pLabel == NULL)
      return;
   
   char v_d[30];
   sprintf(v_d, "Victoires: %d    Défaites: %d", v, d);
   gtk_label_set_text(GTK_LABEL(pLabel), v_d);
}

GtkButton *charge_image_bouton(void) {
   // 1a. Charger l'image
   GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file("img1.jpg", NULL);
   if(pb_temp == NULL) {
      printf("Erreur de chargement de l'image img1.jpg!\n");
      return NULL;
   }

   // 1b. Redimensionner l'image en 100*100 pixels
   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, 100, 100, GDK_INTERP_NEAREST);
   if(pb == NULL) {
      printf("Erreur lors de la redimension de l'image!\n");
      return NULL;
   }

   // 2. Créer le bouton
   GtkWidget *pBouton = gtk_button_new();
   if(pBouton == NULL) {
      printf("Erreur lors de la création du bouton\n");
      return NULL;
   }

   // 3. Placer l'image
   GtkWidget *image = gtk_image_new_from_pixbuf(pb);
   if(image == NULL) {
      printf("Erreur lors de la création de l'image\n");
      return NULL;
   }
   gtk_button_set_image(GTK_BUTTON(pBouton), image);

   return pBouton;
}