#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "tresor.h"


int main(int argc, char **argv) {
    donnees_jeu *donnees = creer_donnees_jeu();
    if(donnees == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les données du jeu\n");
        return EXIT_FAILURE;
    }

    // Initialisation GTK
    gtk_init(&argc, &argv);

    // Création de la fenêtre principale
    GtkWidget *pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pFenetre), "Le jeu du trésor");
    gtk_window_set_default_size(GTK_WINDOW(pFenetre), 480, 270);
    
    GtkWidget *pVBox = gtk_vbox_new(FALSE, 0);
    GtkWidget *pHBox = gtk_hbox_new(FALSE, 0);

    // Labels pour l'affichage
    char v_d[30], etat_partie[30];
    GtkWidget *pLabel_v_d, *pLabel_etat_partie;
    
    sprintf(v_d, "Victoires: %d    Défaites: %d", 
                get_victoires(donnees), get_defaites(donnees));

    pLabel_v_d = gtk_label_new(v_d);
    gtk_widget_set_size_request(pLabel_v_d, 420, 35);
    set_label_score(donnees, pLabel_v_d);

    sprintf(etat_partie, "Choisissez un coffre !");
    pLabel_etat_partie = gtk_label_new(etat_partie);
    gtk_widget_set_size_request(pLabel_etat_partie, 420, 35);
    set_label_etat_partie(donnees, pLabel_etat_partie);

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
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel_v_d, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel_etat_partie, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), get_recommencer(donnees), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, FALSE, 30);

    for(int i = 0; i < 3; i++) {
        gtk_box_pack_start(GTK_BOX(pHBox), get_bouton(donnees, i), FALSE, FALSE, 30);
    }

    gtk_container_add(GTK_CONTAINER(pFenetre), pVBox);

    // Connexion du signal de fermeture de la fenêtre
    g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

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
