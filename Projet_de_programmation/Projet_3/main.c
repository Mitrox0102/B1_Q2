#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "tresor.h"


int main(int argc, char **argv){

  int v = 0, d = 0;
  char v_d[30];
  char etat_partie[30];

  GtkWidget *pLabel_v_d, *pLabel_etat_partie;
  gtk_init(&argc, &argv);

  GtkWidget *pFenetre = creer_fenetre();

  GtkWidget *pVBox = gtk_vbox_new(TRUE, 0);

  GtkWidget *pBouton;

  pBouton = gtk_button_new_with_mnemonic("_Recommencer");
  GtkAccelGroup *groupe_accel = gtk_accel_group_new();
    
  gtk_widget_add_accelerator(pBouton, "clicked", groupe_accel, 'r',
                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);


  sprintf(v_d, "Victoires: %d    Défaites: %d", v, d);
  pLabel_v_d = gtk_label_new(v_d);

  sprintf(etat_partie, "Choisissez un coffre !");
  pLabel_etat_partie = gtk_label_new(etat_partie);


  g_signal_connect(G_OBJECT(pBouton), "clicked", G_CALLBACK(on_button_clicked), 
  pLabel_etat_partie);

  gtk_box_pack_start(GTK_BOX(pVBox), pLabel_v_d, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pVBox), pLabel_etat_partie, TRUE, TRUE, 0);
  
  gtk_box_pack_start(GTK_BOX(pVBox), pBouton, TRUE, TRUE, 0);
  gtk_widget_set_sensitive(pBouton, FALSE);

  gtk_container_add(GTK_CONTAINER(pFenetre), pVBox);

  gtk_window_add_accel_group(GTK_WINDOW(pFenetre), groupe_accel);

  gtk_widget_show_all(pFenetre);

  gtk_main();

  return EXIT_SUCCESS;
}
