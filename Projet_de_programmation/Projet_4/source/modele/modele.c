#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "modele.h"

void initialiser_plateau(Plateau *plateau)
{
   if (!plateau)
   {
      return;
   }

   srand(time(NULL));
}

Plateau *creer_plateau(GtkWidget *fenetre, int largeur, int hauteur, int nb_types, int symboles_par_tour, int difficulte)
{
   Plateau *p = malloc(sizeof(Plateau));
   if (!p)
   {
      fprintf(stderr, "Erreur d'allocation du plateau.\n");
      exit(EXIT_FAILURE);
   }

   if (nb_types < 1 || nb_types > 7) {
      fprintf(stderr, "Erreur : nb_types invalide (%d). Doit être entre 1 et 7.\n", nb_types);
      exit(EXIT_FAILURE);
   }

   p->largeur = largeur;
   p->hauteur = hauteur;
   p->nb_types_symboles = nb_types;
   p->symboles_par_tour = symboles_par_tour;
   p->nb_cases_remplies = 0;
   p->difficulte = difficulte;
   p->score.valeur = 0;

   switch (p->difficulte)
   {
   case 0:
   case 1:
      p->nb_suivantes = 3;
      break;
   case 2:
      p->nb_suivantes = 5;
      break;
   default:
      fprintf(stderr, "Erreur lors de l'assignation des boules suivantes");
      break;
   }

   p->boutons_suivants = g_new0(GtkWidget *, p->nb_suivantes);
   if (!p->boutons_suivants) {
      fprintf(stderr, "Erreur d'allocation de boutons_suivants\n");
      free(p->cases);
      free(p);
      exit(EXIT_FAILURE);
   }
   for (int i = 0; i < p->nb_suivantes; i++) {
      p->boutons_suivants[i] = NULL;
   }

   int total_cases = largeur * hauteur;
   
   p->cases = malloc(total_cases * sizeof(Case));
   if (!p->cases)
   {
      fprintf(stderr, "Erreur d'allocation des cases.\n");
      free(p);
      exit(EXIT_FAILURE);
   }

   for (int i = 0; i < total_cases; i++) {
      p->cases[i].occupe = false;
      p->cases[i].image = NULL;
      p->cases[i].col = rand() % nb_types;
   }



   return p;
}

// Faut ajouter une fonction qui libère tout un par un. (barre d'outils, grille, etc.)
void detruire_plateau(Plateau *plateau)
{
   if (!plateau)
      return;

   if (plateau->boutons_suivants) {
      for (int i = 0; i < plateau->nb_suivantes; i++) {
            if (plateau->boutons_suivants[i]) {
               gtk_widget_destroy(plateau->boutons_suivants[i]);
            }
      }
      g_free(plateau->boutons_suivants);
   }

   if (plateau->cases) {
      free(plateau->cases);
      plateau->cases = NULL;
   }

   free(plateau);
}


void charger_scores(const char *fichier, Score *scores, int *nb_scores)
{
   FILE *fp = fopen(fichier, "r");
   *nb_scores = 0;

   if (!fp)
   {
      perror("Erreur ouverture fichier scores");
      return;
   }

   while (*nb_scores < MAX_SCORES &&
         fscanf(fp, "%s %d", scores[*nb_scores].nom, &scores[*nb_scores].valeur) == 2)
   {
      (*nb_scores)++;
   }

   fclose(fp);
}
void sauvegarder_score(const char *fichier, const char *nom, int nouveau_score)
{
   Score scores[MAX_SCORES + 1];
   int nb_scores = 0;

   charger_scores(fichier, scores, &nb_scores);

   strncpy(scores[nb_scores].nom, nom, MAX_NOM);
   scores[nb_scores].valeur = nouveau_score;
   nb_scores++;

   for (int i = 0; i < nb_scores - 1; i++)
   {
      for (int j = i + 1; j < nb_scores; j++)
      {
         if (scores[j].valeur > scores[i].valeur)
         {
            Score tmp = scores[i];
            scores[i] = scores[j];
            scores[j] = tmp;
         }
      }
   }

   FILE *fp = fopen(fichier, "w");
   if (!fp)
   {
      fprintf(stderr, "Erreur ouverture fichier scores");
      return;
   }

   int limite;
   if (nb_scores < MAX_SCORES)
   {
      limite = nb_scores;
   }
   else
   {
      limite = MAX_SCORES;
   }

   for (int i = 0; i < limite; i++)
   {
      fprintf(fp, "%s %d\n", scores[i].nom, scores[i].valeur);
   }
   fclose(fp);
}