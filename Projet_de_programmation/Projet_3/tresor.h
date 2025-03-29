#ifndef TRESOR_H
#define TRESOR_H

#include <gtk/gtk.h>

void on_button_clicked(GtkWidget *widget, gpointer data);
GtkWidget *creer_fenetre(void);
void detruire_fenetre(GtkWidget *pW, gpointer data);
void mise_a_jour(GtkWidget *pLabel, int v, int d);

#endif