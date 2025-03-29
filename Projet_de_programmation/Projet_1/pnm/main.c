/**
 * main.c
 *
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/02/2025
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"

int main(int argc, char *argv[])
{
   // Déclaration des variables
   char *optstring = "f:i:o:";
   int opt;             // Option courante
   char *format = NULL; // Format de l'image
   char *input = NULL;  // Fichier d'entrée
   char *output = NULL; // Fichier de sortie

   // Parsing des arguments
   while ((opt = getopt(argc, argv, optstring)) != -1)
   {
      switch (opt)
      {
      case 'f':
         format = optarg;
         break;
      case 'i':
         input = optarg;
         break;
      case 'o':
         output = optarg;
         break;
      default:
         printf("Utilisez cette configuration : -f <format> -i <input> -o <output>\n");
         return -1;
         break;
      }
   }

   // Verification des arguments
   if (!format || !input || !output)
   {
      printf("Les parametres (-f, -i, -o) sont obligatoires.\n");
      return -1;
   }

   // Verification du format
   if (!(format[0] == 'P' && (format[1] == 'P' || format[1] == 'B' || format[1] == 'G') && format[2] == 'M'))
   {
      printf("Format invalde. Supporte uniquement PPM, PBM et PGM\n");
      return -1;
   }

   // Creation du pointeur de l'image
   PNM *image = NULL;

   // Chargement de l'image
   if (load_pnm(&image, input) != 0)
   {
      printf("Erreur lors du chargement de l'image : %s\n", input);
      return -1;
   }

   // Sauvegarde de l'image
   if (write_pnm(image, output) != 0)
   {
      printf("Erreur lors de la sauvegarde de l'image : %s\n", output);
      detruire_pnm(image);
      return -1;
   }

   // Affichage de la reussite de la sauvegarde
   printf("Sauvegarde reussie dans %s\n", output);

   // Liberation de la mémoire
   detruire_pnm(image);
   return 0;
}
