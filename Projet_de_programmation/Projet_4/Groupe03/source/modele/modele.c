#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "modele.h"

// Définition complète des structures
struct Case_t
{
   bool occupe;
   Couleur col;
   GtkWidget *image;
};

struct Score_t
{
   char nom[MAX_NOM + 1];
   int valeur;
};

struct Plateau_t
{
   int largeur;
   int hauteur;
   int nb_types_symboles;
   int symboles_par_tour;
   int nb_cases_remplies;
   struct Case_t *cases;
   int difficulte;
   struct Score_t score;
   int nb_suivantes;
   struct Case_t boules_suivantes[MAX_SUIVANTS];
   GtkWidget **boutons_suivants;
};

// Implémentation des getters pour Plateau
int plateau_get_largeur(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_largeur\n");
      return 0;
   }
   return p->largeur;
}

int plateau_get_hauteur(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_hauteur\n");
      return 0;
   }
   return p->hauteur;
}

int plateau_get_nb_types_symboles(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_nb_types_symboles\n");
      return 0;
   }
   return p->nb_types_symboles;
}

int plateau_get_symboles_par_tour(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_symboles_par_tour\n");
      return 0;
   }
   return p->symboles_par_tour;
}

int plateau_get_difficulte(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_difficulte\n");
      return 0;
   }
   return p->difficulte;
}

int plateau_get_nb_cases_remplies(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_nb_cases_remplies\n");
      return 0;
   }
   return p->nb_cases_remplies;
}

int plateau_get_nb_suivantes(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_nb_suivantes\n");
      return 0;
   }
   return p->nb_suivantes;
}

Case *plateau_get_case(Plateau *p, int x, int y)
{
   if (!p || x < 0 || y < 0 || x >= p->largeur || y >= p->hauteur)
   {
      fprintf(stderr, "Erreur: Plateau nul ou coordonnées invalides dans plateau_get_case\n");
      return NULL;
   }
   return &(p->cases[y * p->largeur + x]);
}

const char *plateau_get_score_nom(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_score_nom\n");
      return "";
   }
   return p->score.nom;
}

int plateau_get_score_valeur(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_score_valeur\n");
      return 0;
   }
   return p->score.valeur;
}

Couleur plateau_get_boule_suivante_couleur(Plateau *p, int index)
{
   if (!p || index < 0 || index >= p->nb_suivantes)
   {
      fprintf(stderr, "Erreur: Plateau nul ou index invalide dans plateau_get_boule_suivante_couleur\n");
      return 0;
   }
   return p->boules_suivantes[index].col;
}

GtkWidget **plateau_get_boutons_suivants(Plateau *p)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul dans plateau_get_boutons_suivants\n");
      return NULL;
   }
   return p->boutons_suivants;
}

GtkWidget *plateau_get_bouton_suivant(Plateau *p, int index)
{
   if (!p || index < 0 || index >= p->nb_suivantes || !p->boutons_suivants)
   {
      fprintf(stderr, "Erreur: Plateau nul ou index invalide dans plateau_get_bouton_suivant\n");
      return NULL;
   }
   return p->boutons_suivants[index];
}

// Implémentation des setters pour Plateau
void plateau_set_largeur(Plateau *p, int largeur)
{
   if (!p || largeur <= 0)
   {
      fprintf(stderr, "Erreur: Plateau nul ou largeur invalide dans plateau_set_largeur\n");
      return;
   }
   p->largeur = largeur;
}

void plateau_set_hauteur(Plateau *p, int hauteur)
{
   if (!p || hauteur <= 0)
   {
      fprintf(stderr, "Erreur: Plateau nul ou hauteur invalide dans plateau_set_hauteur\n");
      return;
   }
   p->hauteur = hauteur;
}

void plateau_set_nb_types_symboles(Plateau *p, int nb_types)
{
   if (!p || nb_types < 1 || nb_types > 7)
   {
      fprintf(stderr, "Erreur: Plateau nul ou nb_types invalide dans plateau_set_nb_types_symboles\n");
      return;
   }
   p->nb_types_symboles = nb_types;
}

void plateau_set_symboles_par_tour(Plateau *p, int symboles)
{
   if (!p || symboles <= 0)
   {
      fprintf(stderr, "Erreur: Plateau nul ou symboles invalide dans plateau_set_symboles_par_tour\n");
      return;
   }
   p->symboles_par_tour = symboles;
}

void plateau_set_difficulte(Plateau *p, int difficulte)
{
   if (!p || difficulte < 0 || difficulte > 2)
   {
      fprintf(stderr, "Erreur: Plateau nul ou difficulte invalide dans plateau_set_difficulte\n");
      return;
   }
   p->difficulte = difficulte;
}

void plateau_set_nb_cases_remplies(Plateau *p, int nb)
{
   if (!p || nb < 0)
   {
      fprintf(stderr, "Erreur: Plateau nul ou nb_cases_remplies invalide dans plateau_set_nb_cases_remplies\n");
      return;
   }
   p->nb_cases_remplies = nb;
}

void plateau_set_nb_suivantes(Plateau *p, int nb)
{
   if (!p || nb < 0)
   {
      fprintf(stderr, "Erreur: Plateau nul ou nb_suivantes invalide dans plateau_set_nb_suivantes\n");
      return;
   }
   p->nb_suivantes = nb;
}

void plateau_set_score_nom(Plateau *p, const char *nom)
{
   if (!p || !nom)
   {
      fprintf(stderr, "Erreur: Plateau nul ou nom invalide dans plateau_set_score_nom\n");
      return;
   }
   strncpy(p->score.nom, nom, MAX_NOM);
   p->score.nom[MAX_NOM] = '\0';
}

void plateau_set_score_valeur(Plateau *p, int valeur)
{
   if (!p || valeur < 0)
   {
      fprintf(stderr, "Erreur: Plateau nul ou valeur invalide dans plateau_set_score_valeur\n");
      return;
   }
   p->score.valeur = valeur;
}

void plateau_set_boule_suivante_couleur(Plateau *p, int index, Couleur couleur)
{
   if (!p || index < 0 || index >= p->nb_suivantes)
   {
      fprintf(stderr, "Erreur: Plateau nul ou index invalide dans plateau_set_boule_suivante_couleur\n");
      return;
   }
   p->boules_suivantes[index].col = couleur;
}

void plateau_set_boutons_suivants(Plateau *p, GtkWidget **boutons)
{
   if (!p)
   {
      fprintf(stderr, "Erreur: Plateau nul ou boutons invalide dans plateau_set_boutons_suivants\n");
      return;
   }

   if (p->boutons_suivants)
   {
      g_free(p->boutons_suivants);
   }
   p->boutons_suivants = boutons;
}

void plateau_set_bouton_suivant(Plateau *p, int index, GtkWidget *bouton)
{
   if (!p || index < 0 || index >= p->nb_suivantes || !p->boutons_suivants || !bouton)
   {
      fprintf(stderr, "Erreur: Plateau nul ou index invalide dans plateau_set_bouton_suivant\n");
      return;
   }
   p->boutons_suivants[index] = bouton;
}

// Implémentation des getters/setters pour Case
bool case_est_occupe(Case *c)
{
   if (!c)
   {
      fprintf(stderr, "Erreur: Case nulle dans case_est_occupe\n");
      return false;
   }
   return c->occupe;
}

Couleur case_get_couleur(Case *c)
{
   if (!c)
   {
      fprintf(stderr, "Erreur: Case nulle dans case_get_couleur\n");
      return 0;
   }
   return c->col;
}

GtkWidget *case_get_image(Case *c)
{
   if (!c)
   {
      fprintf(stderr, "Erreur: Case nulle dans case_get_image\n");
      return NULL;
   }
   return c->image;
}

void case_set_occupe(Case *c, bool occupe)
{
   if (!c)
   {
      fprintf(stderr, "Erreur: Case nulle dans case_set_occupe\n");
      return;
   }
   c->occupe = occupe;
}

void case_set_couleur(Case *c, Couleur couleur)
{
   if (!c)
   {
      fprintf(stderr, "Erreur: Case nulle dans case_set_couleur\n");
      return;
   }
   c->col = couleur;
}

void case_set_image(Case *c, GtkWidget *image)
{
   if (!c)
   {
      fprintf(stderr, "Erreur: Case nulle dans case_set_image\n");
      return;
   }
   c->image = image;
}

Score *score_create(const char *nom, int valeur)
{
   if (!nom || valeur < 0)
   {
      fprintf(stderr, "Erreur: nom invalide ou valeur négative dans score_create\n");
      return NULL;
   }

   Score *s = malloc(sizeof(struct Score_t));
   if (!s)
      return NULL;

   strncpy(s->nom, nom, MAX_NOM);
   s->nom[MAX_NOM] = '\0';
   s->valeur = valeur;

   return s;
}

void score_destroy(Score *s)
{
   if (!s)
   {
      fprintf(stderr, "Erreur: Score nul dans score_destroy\n");
      return;
   }

   if (s)
      free(s);
}

const char *score_get_nom(Score *s)
{
   if (!s)
   {
      fprintf(stderr, "Erreur: Score nul dans score_get_nom\n");
      return "";
   }
   return s->nom;
}

int score_get_valeur(Score *s)
{
   if (!s)
   {
      fprintf(stderr, "Erreur: Score nul dans score_get_valeur\n");
      return 0;
   }
   return s->valeur;
}

void initialiser_plateau(Plateau *plateau)
{
   if (!plateau)
   {
      fprintf(stderr, "Erreur: Plateau nul dans initialiser_plateau\n");
      return;
   }
   srand(time(NULL));
}

Plateau *creer_plateau(GtkWidget *fenetre, int largeur, int hauteur, 
                     int nb_types, int symboles_par_tour, int difficulte)
{
   if (!fenetre || largeur <= 0 || hauteur <= 0 || symboles_par_tour <= 0 
         || difficulte < 0)
   {
      fprintf(stderr, "Erreur: paramètres invalides pour la création du plateau\n");
      return NULL;
   }

   if (nb_types < 1 || nb_types > 7)
   {
      fprintf(stderr, "Erreur : nb_types invalide (%d). Doit être entre 1 et 7.\n", nb_types);
      exit(EXIT_FAILURE);
   }

   (void)fenetre; // Paramètre non utilisé

   Plateau *p = malloc(sizeof(struct Plateau_t));
   if (!p)
   {
      fprintf(stderr, "Erreur d'allocation du plateau.\n");
      exit(EXIT_FAILURE);
   }

   p->largeur = largeur;
   p->hauteur = hauteur;
   p->nb_types_symboles = nb_types;
   p->symboles_par_tour = symboles_par_tour;
   p->nb_cases_remplies = 0;
   p->difficulte = difficulte;
   p->score.valeur = 0;
   p->score.nom[0] = '\0';

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
   if (!p->boutons_suivants)
   {
      fprintf(stderr, "Erreur d'allocation de boutons_suivants\n");
      free(p);
      exit(EXIT_FAILURE);
   }

   for (int i = 0; i < p->nb_suivantes; i++)
   {
      p->boutons_suivants[i] = NULL;
   }

   int total_cases = largeur * hauteur;

   p->cases = malloc(total_cases * sizeof(struct Case_t));
   if (!p->cases)
   {
      fprintf(stderr, "Erreur d'allocation des cases.\n");
      free(p->boutons_suivants);
      free(p);
      exit(EXIT_FAILURE);
   }

   for (int i = 0; i < total_cases; i++)
   {
      p->cases[i].occupe = false;
      p->cases[i].image = NULL;
      p->cases[i].col = rand() % nb_types;
   }

   return p;
}

void detruire_plateau(Plateau *plateau)
{
   if (!plateau)
      return;

   if (plateau->boutons_suivants)
   {
      g_free(plateau->boutons_suivants);
      plateau->boutons_suivants = NULL;
   }

   // Libérer les cases
   if (plateau->cases)
   {
      free(plateau->cases);
      plateau->cases = NULL;
   }

   free(plateau);
}

void plateau_destroy(Plateau *p)
{
   detruire_plateau(p);
}

// Les fonctions pour les scores
void charger_scores(const char *fichier, Score **scores, int *nb_scores)
{
   if (!fichier || !scores || !nb_scores)
   {
      fprintf(stderr, "Erreur: paramètres invalides dans charger_scores\n");
      return;
   }

   FILE *fp = fopen(fichier, "r");
   *nb_scores = 0;

   if (!fp)
   {
      perror("Erreur ouverture fichier scores");
      return;
   }

   char nom_temp[MAX_NOM + 1];
   int valeur_temp;

   while (*nb_scores < MAX_SCORES &&
         fscanf(fp, "%s %d", nom_temp, &valeur_temp) == 2)
   {
      scores[*nb_scores] = score_create(nom_temp, valeur_temp);
      if (!scores[*nb_scores])
      {
         fprintf(stderr, "Erreur de création d'un score\n");
         break;
      }
      (*nb_scores)++;
   }

   fclose(fp);
}

void sauvegarder_score(const char *fichier, const char *nom, int nouveau_score)
{
   if (!fichier || !nom || nouveau_score < 0)
   {
      fprintf(stderr, "Erreur: paramètres invalides dans sauvegarder_score\n");
      return;
   }

   struct Score_t scores[MAX_SCORES + 1];
   int nb_scores = 0;

   // Charger les scores existants
   FILE *fp_read = fopen(fichier, "r");
   if (fp_read)
   {
      while (nb_scores < MAX_SCORES &&
            fscanf(fp_read, "%s %d", scores[nb_scores].nom, &scores[nb_scores].valeur) == 2)
      {
         nb_scores++;
      }
      fclose(fp_read);
   }

   // Ajouter le nouveau score
   strncpy(scores[nb_scores].nom, nom, MAX_NOM);
   scores[nb_scores].valeur = nouveau_score;
   nb_scores++;

   // Trier les scores
   for (int i = 0; i < nb_scores - 1; i++)
   {
      for (int j = i + 1; j < nb_scores; j++)
      {
         if (scores[j].valeur > scores[i].valeur)
         {
            struct Score_t tmp = scores[i];
            scores[i] = scores[j];
            scores[j] = tmp;
         }
      }
   }

   // Sauvegarder les scores
   FILE *fp = fopen(fichier, "w");
   if (!fp)
   {
      fprintf(stderr, "Erreur ouverture fichier scores pour écriture");
      return;
   }

   int limite = (nb_scores < MAX_SCORES) ? nb_scores : MAX_SCORES;
   for (int i = 0; i < limite; i++)
   {
      fprintf(fp, "%s %d\n", scores[i].nom, scores[i].valeur);
   }

   fclose(fp);
}

bool verifier_lignes(Plateau *p)
{
   if (!p)
      return false;

   int largeur = plateau_get_largeur(p);
   int hauteur = plateau_get_hauteur(p);
   bool ligne_trouvee = false;
   int score_ajoute = 0;

   // Créer tableau pour marquer les cases à supprimer
   bool **cases_a_supprimer = malloc(largeur * sizeof(bool *));
   if (!cases_a_supprimer)
   {
      fprintf(stderr, "Erreur d'allocation mémoire\n");
      return false;
   }

   for (int i = 0; i < largeur; i++)
   {
      cases_a_supprimer[i] = malloc(hauteur * sizeof(bool));
      if (!cases_a_supprimer[i])
      {
         // Libérer la mémoire déjà allouée
         for (int j = 0; j < i; j++)
            free(cases_a_supprimer[j]);
         free(cases_a_supprimer);
         fprintf(stderr, "Erreur d'allocation mémoire\n");
         return false;
      }

      for (int j = 0; j < hauteur; j++)
      {
         cases_a_supprimer[i][j] = false;
      }
   }

   // Lignes horizontales
   for (int i = 0; i < largeur; i++)
   {
      for (int j = 0; j < hauteur; j++)
      {
         Case *c = plateau_get_case(p, i, j);
         if (!c || !case_est_occupe(c))
            continue;

         Couleur couleur = case_get_couleur(c);
         int count = 1;

         for (int k = 1; i + k < largeur; k++)
         {
            Case *prochaine_case = plateau_get_case(p, i + k, j);
            if (!prochaine_case || !case_est_occupe(prochaine_case) ||
               case_get_couleur(prochaine_case) != couleur)
            {
               break;
            }
            count++;
         }

         if (count >= 5)
         {
            ligne_trouvee = true;
            score_ajoute += count * 2;

            for (int k = 0; k < count; k++)
            {
               cases_a_supprimer[i + k][j] = true;
            }
         }
      }
   }

   // Colonnes verticales
   for (int j = 0; j < hauteur; j++)
   {
      for (int i = 0; i < largeur; i++)
      {
         Case *c = plateau_get_case(p, i, j);
         if (!c || !case_est_occupe(c))
            continue;

         Couleur couleur = case_get_couleur(c);
         int count = 1;

         for (int k = 1; j + k < hauteur; k++)
         {
            Case *prochaine_case = plateau_get_case(p, i, j + k);
            if (!prochaine_case || !case_est_occupe(prochaine_case) ||
               case_get_couleur(prochaine_case) != couleur)
            {
               break;
            }
            count++;
         }

         if (count >= 5)
         {
            ligne_trouvee = true;
            score_ajoute += count * 2;

            for (int k = 0; k < count; k++)
            {
               cases_a_supprimer[i][j + k] = true;
            }
         }
      }
   }

   // Diagonales descendantes
   for (int i = 0; i < largeur; i++)
   {
      for (int j = 0; j < hauteur; j++)
      {
         Case *c = plateau_get_case(p, i, j);
         if (!c || !case_est_occupe(c))
            continue;

         Couleur couleur = case_get_couleur(c);
         int count = 1;

         for (int k = 1; i + k < largeur && j + k < hauteur; k++)
         {
            Case *prochaine_case = plateau_get_case(p, i + k, j + k);
            if (!prochaine_case || !case_est_occupe(prochaine_case) ||
               case_get_couleur(prochaine_case) != couleur)
            {
               break;
            }
            count++;
         }

         if (count >= 5)
         {
            ligne_trouvee = true;
            score_ajoute += count * 2;

            for (int k = 0; k < count; k++)
            {
               cases_a_supprimer[i + k][j + k] = true;
            }
         }
      }
   }

   // Diagonales montantes
   for (int i = 0; i < largeur; i++)
   {
      for (int j = hauteur - 1; j >= 0; j--)
      {
         Case *c = plateau_get_case(p, i, j);
         if (!c || !case_est_occupe(c))
            continue;

         Couleur couleur = case_get_couleur(c);
         int count = 1;

         for (int k = 1; i + k < largeur && j - k >= 0; k++)
         {
            Case *prochaine_case = plateau_get_case(p, i + k, j - k);
            if (!prochaine_case || !case_est_occupe(prochaine_case) ||
               case_get_couleur(prochaine_case) != couleur)
            {
               break;
            }
            count++;
         }

         if (count >= 5)
         {
            ligne_trouvee = true;
            score_ajoute += count * 2;

            for (int k = 0; k < count; k++)
            {
               cases_a_supprimer[i + k][j - k] = true;
            }
         }
      }
   }

   if (ligne_trouvee)
   {
      // Mettre à jour le score
      int val_actuelle = plateau_get_score_valeur(p);
      plateau_set_score_valeur(p, val_actuelle + score_ajoute);

      printf("Lignes trouvées! Score augmenté de %d points (total: %d)\n",
            score_ajoute, val_actuelle + score_ajoute);

      // Mettre à jour le plateau en supprimant les cases alignées
      for (int i = 0; i < largeur; i++)
      {
         for (int j = 0; j < hauteur; j++)
         {
            if (cases_a_supprimer[i][j])
            {
               Case *c = plateau_get_case(p, i, j);
               if (c && case_est_occupe(c))
               {
                  case_set_occupe(c, false);
                  // Mise à jour du compteur
                  int cases_actuelles = plateau_get_nb_cases_remplies(p);
                  plateau_set_nb_cases_remplies(p, cases_actuelles - 1);

                  GtkWidget *bouton = case_get_image(c);
                  if (GTK_IS_BUTTON(bouton))
                  {
                     gtk_button_set_image(GTK_BUTTON(bouton), NULL);
                     gtk_widget_queue_draw(bouton);
                  }
               }
            }
         }
      }
   }

   // Libérer la mémoire allouée
   for (int i = 0; i < largeur; i++)
   {
      free(cases_a_supprimer[i]);
   }
   free(cases_a_supprimer);

   return ligne_trouvee;
}
