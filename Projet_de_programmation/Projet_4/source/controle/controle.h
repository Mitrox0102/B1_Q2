#ifndef CONTROLE_H
#define CONTROLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gtk/gtk.h>
#include "../modele/modele.h"
#include "../vue/vue.h"
#include "../utilis.h"

//Pour le changement de niveau en pleins partie
//Je crois qu'on peut faire une structure pour ça mais pas sur 
extern GtkWidget *fenetre_principale;
extern GtkWidget *grille_actuelle;
extern Plateau *plateau_actuel;
extern char *fichier_scores;

//Je crois qu'envr on n'a pas besoin de faire de type opaque pour cette struct
typedef struct
{
   int ligne_actuelle;
   int colonne_actuelle;
   Plateau *plateau;
   GtkWidget *est_bouton;
   GtkWidget *bouton_trouve;
} MiseAJour;

typedef struct
{
   GtkWidget *est_widget;
   gboolean est_trouve;
} Data;

void changer_niveau(GtkMenuItem *item, gpointer user_data);
void detruire_widget(GtkWidget *widget, gpointer data);
void maj_grille(GtkWidget *bouton_clique, gpointer donnees_plateau);
void recreer_grille(GtkWidget *fenetre_principale, Plateau *nouveau_plateau);
void connecter_signaux_grille(GtkWidget *grille, Plateau *plateau);

void callback_trouver_bouton(GtkWidget *bouton_case, gpointer donnees_ptr);
void callback_trouver_vbox(GtkWidget *widget, gpointer data);
void callback_trouver_table(GtkWidget *widget, gpointer data);
void callback_connecter_signal_bouton(GtkWidget *bouton, gpointer data_plateau);

bool chemin_possible(Plateau *plateau, Case *depart, Case *arrivee);

#endif // CONTROLE_H