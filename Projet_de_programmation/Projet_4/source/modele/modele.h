#ifndef MODELE_H
#define MODELE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <gtk/gtk.h>

#include "../utilis.h"

#define MAX_SCORES 10
#define MAX_NOM 50
#define MAX_SUIVANTS 5


typedef struct {
   char nom[MAX_NOM + 1];
   int valeur;
} Score;

typedef struct{
   bool occupe;
   Couleur col;
   GtkWidget *image;
} Case;

struct Plateau_t {
   int largeur;
   int hauteur;
   int nb_types_symboles;
   int symboles_par_tour;
   int nb_cases_remplies;
   Case *cases;
   int difficulte;
   Score score;
   int nb_suivantes;
   Case boules_suivantes[MAX_SUIVANTS];
   GtkWidget **boutons_suivants;
};


void initialiser_plateau(Plateau *plateau);
Plateau *creer_plateau(GtkWidget *fenetre, int largeur, int hauteur, int nb_types, int symboles_par_tour, int difficulte);
void detruire_plateau(Plateau *plateau);

void charger_scores(const char *fichier, Score *scores, int *nb_scores);
void sauvegarder_score(const char *fichier, const char *nom, int nouveau_score);

#endif // MODELE_H
