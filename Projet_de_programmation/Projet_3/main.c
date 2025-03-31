#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "tresor.h"

int main(int argc, char **argv)
{
   donnees_jeu *donnees = creer_donnees_jeu();
   if (donnees == NULL)
   {
      fprintf(stderr, "Erreur d'allocation mémoire pour les données du jeu\n");
      return EXIT_FAILURE;
   }

   // Initialisation GTK
   gtk_init(&argc, &argv);

   // Création de la fenêtre principale
   GtkWidget *pFenetre = creer_fenetre();

   // Création du conteneur principal
   GtkWidget *pVBox = gtk_vbox_new(FALSE, 0);
   GtkWidget *pHBox = gtk_hbox_new(FALSE, 0);

   // Création des labels pour les victoires et défaites
   GtkWidget *pLabel_v_d = creer_v_d(donnees);

   // Création du label pour l'état de la partie
   GtkWidget *pLabel_etat_partie = creer_etat_partie(donnees);

   // Création du bouton Recommencer
   creer_recommencer(donnees, pFenetre);

   // Création des boutons coffres
   creer_bouton(donnees);

   // Enregistrement du bouton recommencer
   set_recommencer(donnees, get_recommencer(donnees));

   // Connexion du signal pour le bouton recommencer
   g_signal_connect(G_OBJECT(get_recommencer(donnees)), "clicked",
                     G_CALLBACK(recommencer_partie), donnees);

   // Organisation des widgets

   // Ajout des labels et boutons dans le conteneur
   gtk_box_pack_start(GTK_BOX(pVBox), pLabel_v_d, FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), pLabel_etat_partie, FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), get_recommencer(donnees), FALSE, 
                     FALSE, 0);

   // Ajout des boutons coffres dans le conteneur horizontal
   gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, FALSE, 30);

   for (int i = 0; i < 3; i++)
   {
      gtk_box_pack_start(GTK_BOX(pHBox), get_bouton(donnees, i), FALSE, FALSE,
                        30);
   }

   // Ajout du conteneur vertical dans la fenêtre
   gtk_container_add(GTK_CONTAINER(pFenetre), pVBox);

   // Initialisation de l'état de la partie
   gerer_etat_partie(donnees);

   // Affichage de la fenêtre
   gtk_widget_show_all(pFenetre);

   // Boucle principale
   gtk_main();

   // Nettoyage
   detruire_donnees_jeu(donnees);
   return EXIT_SUCCESS;
}
