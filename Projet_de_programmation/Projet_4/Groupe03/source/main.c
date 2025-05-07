#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <ctype.h>
#include <getopt.h>
#include <gtk/gtk.h>
#include <stdbool.h>

#include "modele/modele.h"
#include "utilis.h"
#include "vue/vue.h"
#include "controle/controle.h"

// Déclaration des variables globales
GtkWidget *fenetre_principale = NULL;
GtkWidget *grille_actuelle = NULL;
char *fichier_scores = NULL;
Plateau *plateau_actuel = NULL;
bool dialogue_fin_partie_affiche = false;

int main(int argc, char **argv)
{
   char *optstring = "n:f:h";
   char *niveau = NULL;
   char *file = NULL;
   bool help = false;
   int val, index = -1;
   srand(time(NULL));

   const struct option lopts[] = {
      {"difficulty", required_argument, NULL, 'n'},
      {"file", required_argument, NULL, 'f'},
      {"help", optional_argument, NULL, 'h'},
      {NULL, 0, NULL, 0}};

   while ((val = getopt_long(argc, argv, optstring, lopts, &index)) != -1)
   {
      switch (val)
      {
      case 'n':
         niveau = optarg;
         //printf("Niveau choisi : %s\n", niveau);
         break;
      case 'f':
         file = optarg;
         break;
      case 'h':
         help = true;
         break;
      case ':':
         fprintf(stderr, "Erreur: option %c requiert un argument.\n", optopt);
         return EXIT_FAILURE;
         break;
      } // fin switch
   } // fin while

   // Vérification des arguments
   if (help)
   {
      fprintf(stderr, "Utilisation : ./five -n <FACILE|MOYEN|DIFFICILE> "
                     "-f <fichier> [-h]\n");
      fprintf(stderr, "  -n 0 : Facile (7x7)\n");
      fprintf(stderr, "  -n 1 : Moyen  (9x9)\n");
      fprintf(stderr, "  -n 2 : Difficile (20x15)\n");
      return EXIT_SUCCESS;
   }

   if (!niveau || !file)
   {
      fprintf(stderr, "Erreur: Arguments manquants. Utilisez -n <niveau> "
                     "et -f <fichier>\n");
      return EXIT_FAILURE;
   }

   int difficulte = atoi(niveau);
   if (difficulte < 0 || difficulte > 2)
   {
      fprintf(stderr, "Erreur : la difficulté doit être 0 (facile), "
                     "1 (moyen), ou 2 (difficile).\n");
      return EXIT_FAILURE;
   }

   gtk_init(&argc, &argv);

   // Initialisation des properties GTK pour le menu
   gtk_settings_set_long_property(
      gtk_settings_get_default(), "gtk-menu-images", TRUE, "main");

   // Initialise le modèle (plateau)
   Plateau *plateau = NULL;

   char *nom_joueur = demander_nom_joueur();
   if (!nom_joueur)
   {
      fprintf(stderr, "Erreur: impossible de demander le nom du joueur.\n");
      return EXIT_FAILURE;
   }

   // Crée la fenêtre principale
   GtkWidget *fenetre = creer_fenetre();
   if (!fenetre)
   {
      fprintf(stderr, "Erreur: impossible de créer la fenêtre principale.\n");
      return EXIT_FAILURE;
   }

   fenetre_principale = fenetre;    // Sauvegarde la référence
   fichier_scores = g_strdup(file); // Sauvegarde le nom du fichier

   // Crée un conteneur principal vertical
   GtkWidget *vbox = gtk_vbox_new(false, 0);
   if (!vbox)
   {
      fprintf(stderr, "Erreur: impossible de créer le conteneur principal.\n");
      return EXIT_FAILURE;
   }

   gtk_container_add(GTK_CONTAINER(fenetre), vbox);
   gtk_window_set_resizable(GTK_WINDOW(fenetre), FALSE);

   switch (difficulte)
   {
   case 0:
      plateau = creer_plateau(fenetre, 7, 7, 5, 3, 0);
      plateau_set_difficulte(plateau, 0);
      break;
   case 1:
      plateau = creer_plateau(fenetre, 9, 9, 7, 3, 1);
      plateau_set_difficulte(plateau, 1);
      break;
   case 2:
      plateau = creer_plateau(fenetre, 20, 15, 7, 7, 2);
      plateau_set_difficulte(plateau, 2);
      break;
   default:
      fprintf(stderr, "Difficulté invalide. Utilisez 0, 1 ou 2.\n");
      return EXIT_FAILURE;
   }

   if (!plateau)
   {
      fprintf(stderr, "Erreur de création du plateau\n");
      return EXIT_FAILURE;
   }

   plateau_set_score_valeur(plateau, 0);
   plateau_actuel = plateau; // Sauvegarde la référence

   if (nom_joueur && plateau)
   {
         plateau_set_score_nom(plateau, nom_joueur);

         if (est_benoit_donnet(nom_joueur)) {
            plateau_set_score_valeur(plateau, 99999);
            //printf("Bienvenue Benoit Donnet ! Score initialisé à 99999.\n");
         }

      plateau_set_score_nom(plateau, nom_joueur);
      free(nom_joueur);
   }

   GtkWidget *barre_outils = creer_barre_outils();
   if (!barre_outils)
   {
      fprintf(stderr, "Erreur : création de la barre d'outils.\n");
      return EXIT_FAILURE;
   }

   gtk_box_pack_start(GTK_BOX(vbox), barre_outils, FALSE, FALSE, 0);

   // Crée les boutons pour les boules restantes
   int nb_suivantes = plateau_get_nb_suivantes(plateau);
   GtkWidget **boutons_suivants = plateau_get_boutons_suivants(plateau);

   if (!boutons_suivants)
   {
      boutons_suivants = g_new(GtkWidget *, nb_suivantes);
      plateau_set_boutons_suivants(plateau, boutons_suivants);
   }

   for (int i = 0; i < nb_suivantes; i++)
   {
      boutons_suivants[i] = gtk_button_new();
   }

   GtkWidget *label_score;
   GtkWidget *hbox_suivants_et_score = creer_suivants_et_score(boutons_suivants,
                                                               &label_score, plateau);

   if (!hbox_suivants_et_score)
   {
      fprintf(stderr, "Erreur : création des boutons suivants/score.\n");
      return EXIT_FAILURE;
   }

   preparer_boules_suivantes(plateau);
   maj_boutons_suivants(boutons_suivants, plateau);
   gtk_box_pack_start(GTK_BOX(vbox), hbox_suivants_et_score, FALSE, FALSE, 5);

   // Crée la grille de boutons à partir du modèle
   GtkWidget *grille = creer_grille(plateau);
   grille_actuelle = grille;
   gtk_box_pack_start(GTK_BOX(vbox), grille, TRUE, TRUE, 0);

   // Connecte les signaux (clics sur les boutons)
   connecter_signaux_grille(grille, plateau);

   // Génère les boules sur le plateau
   generation_boules(plateau);

   gtk_widget_show_all(fenetre);

   gtk_main();

   // Libération mémoire
   if (plateau_actuel != NULL)
   {
      plateau_destroy(plateau_actuel);
      plateau_actuel = NULL;
      g_free(fichier_scores);
   }

   return EXIT_SUCCESS;
}
