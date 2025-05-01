#ifndef _VUE_H
#define _VUE_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../modele/modele.h"

GtkWidget *creer_fenetre(void);
GtkWidget *creer_barre_outils(void);

char *demander_nom_joueur(void);
GtkWidget *creer_grille(Plateau *plateau);
void maj_grille(GtkWidget *widget, gpointer data);

GtkWidget *creer_suivants_et_score(GtkWidget **boutons_suivants, GtkWidget **label_score,
   Plateau *plateau);

void changer_niveau(GtkMenuItem *item, gpointer user_data);
void recreer_grille(GtkWidget *parent_window, Plateau *nouveau_plateau);

void afficher_dialogue_scores(void);
void afficher_dialogue_a_propos(void);
void afficher_message_perdu(GtkWidget *parent);
void connecter_signaux_grille(GtkWidget *grille, Plateau *plateau);

void afficher_dialogue_fin_de_partie(GtkWindow *parent, int score);

#endif // _VUE_H
