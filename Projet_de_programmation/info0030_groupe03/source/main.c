#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <ctype.h>
#include <getopt.h>
#include <gtk/gtk.h>
#include <stdbool.h>

#include "utilis.h"
#include "vue/vue.h"
#include "modele/modele.h"
#include "controle/controle.h"

// Déclaration des variables globales
GtkWidget *fenetre_principale = NULL;
GtkWidget *grille_actuelle = NULL;
char *fichier_scores = NULL;
Plateau *plateau_actuel = NULL;

int main(int argc, char **argv){
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
         printf("Niveau choisi : %s\n", niveau);
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
   if (help) {
      fprintf(stderr, "Utilisation : ./five -n <FACILE|MOYEN|DIFFICILE> -f <fichier> [-h]\n");
      fprintf(stderr, "  -n 0 : Facile (7x7)\n");
      fprintf(stderr, "  -n 1 : Moyen  (9x9)\n");
      fprintf(stderr, "  -n 2 : Difficile (20x15)\n");
      return EXIT_SUCCESS;
   }
   
   if (!niveau || !file)
   {
      fprintf(stderr, "Erreur: Arguments manquants. Utilisez -n <niveau> et -f <fichier>\n");
      return EXIT_FAILURE;
   }

   int difficulte = atoi(niveau);
   if (difficulte < 0 || difficulte > 2) {
      fprintf(stderr, "Erreur : la difficulté doit être 0 (facile), 1 (moyen), ou 2 (difficile).\n");
      return EXIT_FAILURE;
   }

   gtk_init(&argc, &argv);

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
   fenetre_principale = fenetre; // Sauvegarde la référence
   fichier_scores = g_strdup(file); // Sauvegarde le nom du fichier


   // Crée un conteneur principal vertical
   GtkWidget *vbox = gtk_vbox_new(false, 0);
   gtk_container_add(GTK_CONTAINER(fenetre), vbox);
   gtk_window_set_resizable(GTK_WINDOW(fenetre), FALSE);

   if (strcmp(niveau, "0") == 0) {
      plateau = creer_plateau(fenetre,7, 7, 5, 3, 0);
      plateau->difficulte = 0;
   } else if (strcmp(niveau, "1") == 0) {
      plateau = creer_plateau(fenetre,9, 9, 7, 3, 1);
      plateau->difficulte = 1;
   } else if (strcmp(niveau, "2") == 0) {
      plateau = creer_plateau(fenetre,20, 15, 7, 5, 2);
      plateau->difficulte = 2;
   } else {
      fprintf(stderr, "Difficulté invalide. Utilisez \"facile\", \"moyen\" ou \"difficile\".\n");
      return EXIT_FAILURE;
   }

   if (!plateau) 
   {
      fprintf(stderr, "Erreur de création du plateau\n");
      return EXIT_FAILURE;
   }  

   plateau->score.valeur = 0;
   plateau_actuel = plateau; // Sauvegarde la référence

   if (nom_joueur && plateau) {
      snprintf(plateau->score.nom, MAX_NOM + 1, "%s", nom_joueur);
      free(nom_joueur);
   }


   GtkWidget *barre_outils = creer_barre_outils();
   gtk_box_pack_start(GTK_BOX(vbox), barre_outils, FALSE, FALSE, 0);

   // Crée les boutons pour les boules restantes
   for (int i = 0; i < plateau->nb_suivantes; i++) {
      plateau->boutons_suivants[i] = gtk_button_new();
   }

   GtkWidget *label_score;

   GtkWidget *hbox_suivants_et_score = creer_suivants_et_score(plateau->boutons_suivants, &label_score, plateau);
   if (!hbox_suivants_et_score) {
      fprintf(stderr, "Erreur : création des boutons suivants/score.\n");
      return EXIT_FAILURE;
}
   preparer_boules_suivantes(plateau); 
   maj_boutons_suivants(plateau->boutons_suivants, plateau);
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
      detruire_plateau(plateau_actuel);
      plateau_actuel = NULL;
      g_free(fichier_scores);
   }
   return EXIT_SUCCESS;
}
