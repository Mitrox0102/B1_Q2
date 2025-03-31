#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "tresor.h"

struct donnees_jeu_t {
   int victoires;
   int defaites;
   int tresor_bon;
   int tresor_choisi;
   int nb_clique;

   gboolean etat_partie;
   GtkWidget *bouton[3];
   GtkWidget *recommencer;
   gboolean coffre_ouvert[3];
   GtkWidget *label_score;
   GtkWidget *label_etat_partie;
};

donnees_jeu* creer_donnees_jeu(void) {
   donnees_jeu *donnees = malloc(sizeof(donnees_jeu));
   if (donnees == NULL) {
      fprintf(stderr, "Erreur d'allocation mémoire pour donnees_jeu\n");
      exit(EXIT_FAILURE);
   }
   donnees->victoires = 0;
   donnees->defaites = 0;
   donnees->etat_partie = TRUE;
   donnees->tresor_bon = rand() % 3;
   donnees->nb_clique = 0;
   donnees->tresor_choisi = -1;

   for (int i = 0; i < 3; i++) {
      donnees->coffre_ouvert[i] = FALSE;
   }

   return donnees;
}

void maj_v_d(GtkWidget *label, donnees_jeu *donnees) {
   char v_d[30];
   sprintf(v_d, "Victoires: %d    Défaites: %d", 
               get_victoires(donnees), get_defaites(donnees));

   gtk_label_set_text(GTK_LABEL(label), v_d);
   }

void creer_recommencer(donnees_jeu *donnees, GtkWidget *pFenetre) {
   (void) donnees;
   GtkWidget *pRecommencer = gtk_button_new_with_mnemonic("_Recommencer");
   GtkAccelGroup *groupe_accel = gtk_accel_group_new();
   gtk_window_add_accel_group(GTK_WINDOW(pFenetre), groupe_accel);
   gtk_widget_add_accelerator(pRecommencer, "clicked", groupe_accel, 
                              'r', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
   set_recommencer(donnees, pRecommencer);
}

void creer_bouton(donnees_jeu *donnees){
   GtkWidget *pBouton[3];
   for(int i = 0; i < 3; i++) {
      pBouton[i] = charge_image_bouton("./coffre_ferme.jpg");
      if(pBouton[i] == NULL) {
         g_print("Erreur lors de la création du bouton avec image\n");
         return;
      }
      // Enregistrement des boutons dans la structure
      set_bouton(donnees, i, pBouton[i]);
      
      // Connexion des signaux pour chaque bouton
      g_signal_connect(G_OBJECT(pBouton[i]), "clicked", 
                     G_CALLBACK(gerer_clic_coffre), donnees);
   };
}


int get_victoires(const donnees_jeu *donnees) {
   if (donnees == NULL) return 0;
   return donnees->victoires;
}

int get_defaites(const donnees_jeu *donnees) {
   if (donnees == NULL) return 0;
   return donnees->defaites;
}

int get_tresor_bon(const donnees_jeu *donnees) {
   if (donnees == NULL) return -1;
   return donnees->tresor_bon;
}

gboolean get_etat_partie(const donnees_jeu *donnees) {
   if (donnees == NULL) return FALSE;
   return donnees->etat_partie;
}

GtkWidget* get_bouton(const donnees_jeu *donnees, int index) {
   if (donnees == NULL || index < 0 || index >= 3) return NULL;
   return donnees->bouton[index];
}

GtkWidget* get_recommencer(const donnees_jeu *donnees) {
   if (donnees == NULL) return NULL;
   return donnees->recommencer;
}

gboolean get_coffre_ouvert(const donnees_jeu *donnees, int index) {
   if (donnees == NULL || index < 0 || index >= 3) {
      return FALSE; // Retourne FALSE si les paramètres sont invalides
   }
   return donnees->coffre_ouvert[index];
}

GtkWidget* get_label_score(const donnees_jeu *donnees) {
   if (donnees == NULL) return NULL;
   return donnees->label_score;
}

GtkWidget* get_label_etat_partie(const donnees_jeu *donnees) {
   if (donnees == NULL) return NULL;
   return donnees->label_etat_partie;
}


void set_victoires(donnees_jeu *donnees, int victoires) {
   if (donnees == NULL) return;
   donnees->victoires = victoires;
}

void set_defaites(donnees_jeu *donnees, int defaites) {
   if (donnees == NULL) return;
   donnees->defaites = defaites;
}

void set_tresor_bon(donnees_jeu *donnees, int tresor_bon) {
   if (donnees == NULL || tresor_bon < 0 || tresor_bon >= 3) return;
   donnees->tresor_bon = tresor_bon;
}

void set_etat_partie(donnees_jeu *donnees, gboolean etat) {
   if (donnees == NULL) return;
   donnees->etat_partie = etat;
}

void set_bouton(donnees_jeu *donnees, int index, GtkWidget *bouton) {
   if (donnees == NULL || index < 0 || index >= 3) return;
   donnees->bouton[index] = bouton;
}

void set_recommencer(donnees_jeu *donnees, GtkWidget *recommencer) {
   if (donnees == NULL) return;
   donnees->recommencer = recommencer;
}

void set_coffre_ouvert(donnees_jeu *donnees, int index, gboolean etat) {
   if (donnees == NULL || index < 0 || index >= 3) {
      return;
   }
   donnees->coffre_ouvert[index] = etat;
}

void set_label_score(donnees_jeu *donnees, GtkWidget *label) {
   if (donnees == NULL) return;
   donnees->label_score = label;
}

void set_label_etat_partie(donnees_jeu *donnees, GtkWidget *label) {
   if (donnees == NULL) return;
   donnees->label_etat_partie = label;
}


void detruire_donnees_jeu(donnees_jeu *donnees) {
   if(donnees != NULL) {
      free(donnees);
   }
}

void gerer_etat_partie(donnees_jeu *donnees) {
   if (donnees == NULL) return;
   
   if (get_etat_partie(donnees)) {
      gtk_widget_set_sensitive(get_recommencer(donnees), FALSE);
      gtk_widget_set_sensitive(get_bouton(donnees, 0), TRUE);
      gtk_widget_set_sensitive(get_bouton(donnees, 1), TRUE);
      gtk_widget_set_sensitive(get_bouton(donnees, 2), TRUE);
   } else {
      gtk_widget_set_sensitive(get_recommencer(donnees), TRUE);
      gtk_widget_set_sensitive(get_bouton(donnees, 0), FALSE);
      gtk_widget_set_sensitive(get_bouton(donnees, 1), FALSE);
      gtk_widget_set_sensitive(get_bouton(donnees, 2), FALSE);
   }
}


GtkWidget *creer_fenetre(void){
   GtkWidget *pF = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pF), "Le jeu du trésor");
   gtk_window_set_default_size(GTK_WINDOW(pF), 480, 270);
   gtk_window_set_position(GTK_WINDOW(pF), GTK_WIN_POS_CENTER);
   g_signal_connect(G_OBJECT(pF), "destroy",
   G_CALLBACK(gtk_main_quit), NULL);
   return pF;
   }

void charger_nouvelle_image(GtkWidget *bouton, const char *chemin_image) {
   // Charger l'image depuis le fichier
   GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file(chemin_image, NULL);
   if (pb_temp == NULL) {
      fprintf(stderr, "Erreur de chargement de l'image %s!\n", chemin_image);
      return;
   }

   // Redimensionner l'image à 100x100 pixels
   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, 135, 140, GDK_INTERP_BILINEAR);
   g_object_unref(pb_temp);
   if (pb == NULL) {
      fprintf(stderr, "Erreur lors de la redimension de l'image!\n");
      return;
   }

   // Créer un widget image à partir du pixbuf
   GtkWidget *image = gtk_image_new_from_pixbuf(pb);
   g_object_unref(pb);

   if (image == NULL) {
      fprintf(stderr, "Erreur lors de la création de l'image\n");
      return;
   }

   // Appliquer l'image au bouton
   gtk_button_set_image(GTK_BUTTON(bouton), image);
}

void gerer_clic_coffre(GtkWidget *widget, gpointer data) {
   donnees_jeu *donnees = (donnees_jeu *)data;
   int coffre_clique = -1;

   for(int i = 0; i < 3; i++) {
      if(widget == donnees->bouton[i]) {
         coffre_clique = i;
         break;
      }
   }

   if (coffre_clique == -1 || get_coffre_ouvert(donnees, coffre_clique)) {
      return;
   }

   donnees->nb_clique++;

   if(donnees->nb_clique == 1) {

      int coffre_a_reveler;
      do {
         coffre_a_reveler = rand() % 3;
      } while(coffre_a_reveler == coffre_clique || 
            coffre_a_reveler == donnees->tresor_bon);

      donnees->tresor_choisi = coffre_a_reveler;
      donnees->coffre_ouvert[coffre_a_reveler] = TRUE;

      charger_nouvelle_image(donnees->bouton[coffre_a_reveler], "./coffre_vide.jpg");
      gtk_widget_set_sensitive(donnees->bouton[coffre_a_reveler], FALSE);


   } else if(donnees->nb_clique == 2) {

      if (coffre_clique == donnees->tresor_bon) {
         charger_nouvelle_image(donnees->bouton[coffre_clique], "./coffre_plein.jpg");
         int nv_victoires = get_victoires(donnees) + 1;
         printf("Victoire avant mise à jour : %d\n", get_victoires(donnees));
         set_victoires(donnees, nv_victoires);
         printf("Victoire après mise à jour : %d\n", get_victoires(donnees));
         maj_v_d(get_label_score(donnees), donnees);
         gtk_label_set_text(GTK_LABEL(get_label_etat_partie(donnees)),
                           "Vous avez gagné !");

   } else {
         charger_nouvelle_image(donnees->bouton[coffre_clique], "./coffre_vide.jpg");
         int nv_defaites = get_defaites(donnees) + 1;
         printf("Défaite avant mise à jour : %d\n", get_defaites(donnees));
         set_defaites(donnees, nv_defaites);
         printf("Défaite après mise à jour : %d\n", get_defaites(donnees));
         maj_v_d(get_label_score(donnees), donnees);
         gtk_label_set_text(GTK_LABEL(get_label_etat_partie(donnees)),
                           "Vous avez perdu !");
   }
      donnees->etat_partie = FALSE;
      gerer_etat_partie(donnees);
   }
}

GtkWidget *charge_image_bouton(const char *chemin_image) {
   GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file(chemin_image, NULL);
   if(pb_temp == NULL) {
      fprintf(stderr, "Erreur de chargement de l'image %s!\n", chemin_image);
      return NULL;
   }

   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, 135, 140, GDK_INTERP_NEAREST);
   g_object_unref(pb_temp);
   if(pb == NULL) {
      fprintf(stderr, "Erreur lors de la redimension de l'image!\n");
      return NULL;
   }

   GtkWidget *pBouton = gtk_button_new();
   if(pBouton == NULL) {
      g_object_unref(pb);
      fprintf(stderr, "Erreur lors de la création du bouton\n");
      return NULL;
   }

   GtkWidget *image = gtk_image_new_from_pixbuf(pb);
   g_object_unref(pb);
   if(image == NULL) {
      fprintf(stderr, "Erreur lors de la création de l'image\n");
      return NULL;
   }
   
   gtk_button_set_image(GTK_BUTTON(pBouton), image);

   gtk_widget_set_size_request(pBouton, 150, 150);

   return pBouton;
}
void recommencer_partie(GtkWidget *widget, gpointer data) {
   (void)widget; // Pour éviter l'avertissement de paramètre inutilisé
   donnees_jeu *donnees = (donnees_jeu *)data;

   if (donnees == NULL) return;

   donnees->nb_clique = 0;
   donnees->tresor_choisi = -1;
   donnees->etat_partie = TRUE;
   donnees->tresor_bon = rand() % 3;
   GtkWidget *label = get_label_etat_partie(donnees);

   if (label != NULL) {
      gtk_label_set_text(GTK_LABEL(label), "Choisissez un coffre !");
   }
   // Réinitialiser tous les coffres
   for (int i = 0; i < 3; i++) {
      donnees->coffre_ouvert[i] = FALSE;
      charger_nouvelle_image(donnees->bouton[i], "./coffre_ferme.jpg");
   }

   gerer_etat_partie(donnees);
}