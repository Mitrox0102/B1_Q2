#include <stdio.h>
#include <gtk/gtk.h>

#ifndef UTILIS_H
#define UTILIS_H

typedef enum{
   BLEU,
   CYAN,
   VERT,
   ORANGE,
   MAUVE,
   ROUGE,
   JAUNE
} Couleur;

typedef struct
{
   Couleur couleur;
   GtkWidget *image;
}Boule;

typedef struct Plateau_t Plateau;

int generer_difficulte(Plateau *plateau);

void mettre_a_jour_score(GtkWidget *label, int score);

GtkWidget *charger_image_button(const char *filename);
const char *get_image_from_color(Couleur couleur);
void generation_boules(Plateau *plateau);

void preparer_boules_suivantes(Plateau *p);
void maj_boutons_suivants(GtkWidget **boutons_suivants, Plateau *p);
void generation_boules_depuis_liste(Plateau *p, int boules_a_placer);
void detruire_boules_suivantes(Plateau *p);

#endif // UTILIS_H