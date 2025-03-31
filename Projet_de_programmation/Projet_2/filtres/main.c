/**
 * @file main.c
 *
 * @brief Ce fichier contient la fonction main() du programme d'application de filtres
 * à des fichiers pnm.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/03/2025
 * @projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>
#include "filtres.h"
#include <pnm.h>

int main(int argc, char *argv[])
{
// Déclaration des variables
char *optstring = "f:i:o:p:";
int opt;             // Option courante
char *input = NULL;  // Fichier d'entrée
char *filtre = NULL; // Filtre appliqué
char *output = NULL; // Fichier de sortie
char *param = NULL;  // Paramètre du filtre

// Parsing des arguments
while ((opt = getopt(argc, argv, optstring)) != -1)
{
   switch (opt)
   {
      case 'f':
         filtre = optarg;
         break;
      case 'i':
         input = optarg;
         break;
      case 'o':
         output = optarg;
         break;
      case 'p':
         param = optarg;
         break;
      default:
         fprintf(stderr,"Usage: %s -f <filtre> -i <input> -o <output> [-p <param>]\n",
               argv[0]);
         return EXIT_FAILURE;
   }
}

// Vérification des arguments obligatoires
if (!filtre || !input || !output)
{
   fprintf(stderr,"Les paramètres -f, -i et -o sont obligatoires.\n");
   return EXIT_FAILURE;
}

// Création et chargement de l'image
PNM *image = NULL;
if (load_pnm(&image, input) != 0)
{
   fprintf(stderr,"Erreur lors du chargement de l'image : %s\n", input);
   return EXIT_FAILURE;
}

// Application du filtre approprié
Filtre type_filtre;

// Conversion de la chaîne en type de filtre
if (strcmp(filtre, "retournement") == 0)
      type_filtre = retournement;
else if (strcmp(filtre, "monochrome") == 0)
      type_filtre = monochrome;
else if (strcmp(filtre, "negatif") == 0)
      type_filtre = negatif;
else if (strcmp(filtre, "gris") == 0)
      type_filtre = gris;
else if (strcmp(filtre, "nb") == 0 || strcmp(filtre, "NB") == 0)
      type_filtre = nb;
else {
      fprintf(stderr, "Filtre inconnu : %s\n", filtre);
      detruire_pnm(image);
      return EXIT_FAILURE;
}

// Application du filtre approprié selon son type
switch(type_filtre) {
      case retournement:
         filtre_retournement(&image);
         break;
   
      case monochrome:
         if (!param || (param[0] != 'r' && param[0] != 'v' && param[0] != 'b')){
            fprintf(stderr, "Paramètre invalide pour le filtre monochrome. "
                           "Utilisez 'r', 'v' ou 'b'.\n");
            detruire_pnm(image);
            return EXIT_FAILURE;
         }
         filtre_monochrome(&image, param[0]);
         break;
   
      case negatif:
         filtre_negatif(&image);
         break;
   
      case gris:
         if (!param || (param[0] != '1' && param[0] != '2')){
            fprintf(stderr, "Paramètre invalide pour le filtre gris. "
               "Utilisez '1' ou '2'.\n");
            detruire_pnm(image);
            return EXIT_FAILURE;
         }
         filtre_gris(&image ,param[0]);
         break;
   
      case nb:
         if (!param) {
            fprintf(stderr, "Paramètre manquant pour le filtre nb. "
                           "Veuillez fournir un seuil.\n");
            detruire_pnm(image);
            return EXIT_FAILURE;
         }
         filtre_nb(&image, atoi(param));
         break;
   
      default:
         fprintf(stderr, "Filtre inconnu\n");
         detruire_pnm(image);
         return EXIT_FAILURE;
   }

// Sauvegarde de l'image
if (write_pnm(image, output) != 0)
{
   fprintf(stderr,"Erreur lors de la sauvegarde de l'image : %s\n", output);
   detruire_pnm(image);
   return EXIT_FAILURE;
}

printf("Sauvegarde réussie dans %s\n", output);
printf("Filtre '%s' appliqué avec succès. Image sauvegardée dans '%s'.\n", filtre, output);

// Libération de la mémoire
detruire_pnm(image);
return EXIT_SUCCESS;
}