/**
 * @file filtres.c
 *
 * @brief Ce fichier contient les définitions de types et
 * les fonctions de filtres d'images PNM.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/03/2025
 * @projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "filtres.h"


void filtre_retournement(PNM **image) {
   //vérifie si l'image existe
   if (*image == NULL) {
      fprintf(stderr,"Image invalide\n");
      return;
   }
      // Alloue de la mémoire pour une nouvelle image retournée et vérifie si
      // elle a bien été allouée
      PNM *retourne = creer_pnm(get_type(*image), get_longueur(*image), 
                              get_largeur(*image), get_valeurMax(*image));
      if (!retourne) {
         fprintf(stderr,"Erreur d'allocation mémoire !\n");
         return;
      }

      //Déclaration des dimensions de l'image
      int lg = get_longueur(*image);
      int lr = get_largeur(*image);

      // Copie les pixels de l'image originale dans la nouvelle image retournée
      switch (get_type(*image)) {
      case 0: // PBM (noir et blanc)
      case 1: // PGM (niveaux de gris)
         {
         int taille_totale = lg * lr;

         for (int i = 0; i < taille_totale; i++) {

               int pixel_retourne = taille_totale - 1 - i;

               set_pixel(retourne, pixel_retourne, get_pixel(*image, i));
            }
         break;
         }
      
      case 2: // PPM (couleur)
      {
         int taille_totale = lg * lr * 3;
      
         for (int i = 0; i < taille_totale; i += 3) {

            int pixel_retourne = taille_totale - 3 - i;
      
            set_pixel(retourne, pixel_retourne, get_pixel(*image, i));
            set_pixel(retourne, pixel_retourne + 1, get_pixel(*image, i + 1));
            set_pixel(retourne, pixel_retourne + 2, get_pixel(*image, i + 2));
         }
         break;
      }

      default:
         fprintf(stderr,"Type d'image non supporté pour le retournement.\n");
         detruire_pnm(retourne);
         return;
      }

      // Libère la mémoire de l'image originale
      detruire_pnm(*image);

      // Remplace l'image originale par la nouvelle image retournée
      *image = retourne;
   }


void filtre_negatif(PNM **image){
   //Vérifie que l'image existe et que le format de l'image est bien PPM
   if (*image != NULL && get_type(*image) != 2)
   {
      fprintf(stderr,"Image invalide\n");
      return;
   }
      // Alloue de la mémoire pour une nouvelle image PNM
      PNM *negatif = creer_pnm(get_type(*image), get_longueur(*image), 
                              get_largeur(*image), get_valeurMax(*image));
      if (!negatif)
      {
         fprintf(stderr,"Erreur d'allocation memoire !\n");
         return;
      }

      //Déclaration des dimensions de l'image
      int lg = get_longueur(*image);
      int lr = get_largeur(*image);

      //Prend chaque pixel et donne sa couleur négative
      for (int i = 0; i < lg; i++) {
         for (int j = 0; j < lr * 3; j++) {
            set_pixel(negatif, i * lr * 3 + j, 
                     255 - get_pixel(*image, i * lr * 3 + j));
         }
      }

      // Libère la mémoire de l'image originale
      detruire_pnm(*image);

      // Remplace l'image originale par la nouvelle image
      *image = negatif;
   }


void filtre_monochrome(PNM **image, char couleur)
{
   //Vérifie que l'image existe et que le type est bien PPM
   if ((*image == NULL && get_type(*image) != 2) || (couleur != 'r' 
   && couleur != 'v' && couleur != 'b'))
   {
      fprintf(stderr,"Image invalide\n");
      return;
   }
   // Alloue de la mémoire pour une nouvelle image PNM
   PNM *monochrome = creer_pnm(get_type(*image), get_longueur(*image), 
                              get_largeur(*image), get_valeurMax(*image));

   if (!monochrome)
   {
      fprintf(stderr,"Erreur d'allocation mémoire\n");
      return;
   }

   //Décalration des dimensions de l'image
   int lg = get_longueur(*image);
   int lr = get_largeur(*image);

   //On garde uniquement la couleur qui a été passée en paramètre
   for (int i = 0; i < lg; i++)
   {
      for (int j = 0; j < lr; j++)
      {

         switch (couleur) {
            case 'r': // Rouge
               set_pixel(monochrome, (i * lr + j) * 3, 
                        get_pixel(*image, (i * lr + j) * 3));

               set_pixel(monochrome, (i * lr + j) * 3 + 1, 0);
               set_pixel(monochrome, (i * lr + j) * 3 + 2, 0);
               break;

            case 'v': // Vert
               set_pixel(monochrome, (i * lr + j) * 3, 0);
               set_pixel(monochrome, (i * lr + j) * 3 + 1, 
                        get_pixel(*image, (i * lr + j) * 3 + 1));

               set_pixel(monochrome, (i * lr + j) * 3 + 2, 0);
               break;

            case 'b': // Bleu
               set_pixel(monochrome, (i * lr + j) * 3, 0);
               set_pixel(monochrome, (i * lr + j) * 3 + 1, 0);
               set_pixel(monochrome, (i * lr + j) * 3 + 2, 
                        get_pixel(*image, (i * lr + j) * 3 + 2));
               break;
            default:
               fprintf(stderr,"Couleur non supportée\n");
               detruire_pnm(monochrome);
               return;
         }
      }
   }

   //Libère la mémoire de l'image originale
   detruire_pnm(*image);

   //Remplace l'image originale par la nouvelle
   *image = monochrome;
}

void filtre_gris(PNM **image, char methode)
{
   //Vérifie que l'image existe et que l'image est bien au format PPM
   if ((*image == NULL && get_type(*image) != 2)|| 
      (methode != '1' && methode != '2'))
   {
      fprintf(stderr,"Image invalide\n");
      return;
   }
   // Alloue de la mémoire pour une nouvelle image PNM
   PNM *gris = creer_pnm(1, get_longueur(*image), 
                        get_largeur(*image), get_valeurMax(*image));

   if (!gris)
   {
      free(gris);
      fprintf(stderr,"Erreur d'allocation mémoire\n");
      return;
   }

   //Déclaration des dimensions de l'image
   int lg = get_longueur(*image);
   int lr = get_largeur(*image);

   switch (methode)
   {
   case '1':
      //On fait un moyenne des trois couleurs d'un pixel qu'on va stocker dans
      //un seul pixel
      for (int i = 0; i < lg; i++) {
         for (int j = 0; j < lr; j++) {
            int moyenne = round((get_pixel(*image, (i * lr + j) * 3) +
                                 get_pixel(*image, (i * lr + j) * 3 + 1) +
                                 get_pixel(*image, (i * lr + j) * 3 + 2))/ 3.0);
            set_pixel(gris, i * lr + j, moyenne);
         }
      }
      printf("Méthode 1\n");
         break;

   case '2':
      //
      for (int i = 0; i < lg; i++)
      {
         for (int j = 0; j < lr; j++)
         {
            int moyenne = round(get_pixel(*image, (i * lr + j) * 3) * 0.299 +
                              get_pixel(*image, (i * lr + j) * 3 + 1) * 0.587 +
                              get_pixel(*image, (i * lr + j) * 3 + 2) * 0.114);

            set_pixel(gris, i * lr + j, moyenne);
         }
         
      }
      printf("Methode 2\n");
      break;
   default:
      fprintf(stderr, "Paramètre non-existant");
      return;
   }

   //Libère la mémoire de l'image originale
   detruire_pnm(*image);

   //Remplace l'image orignale par la nouvelle
   *image = gris;
}

void filtre_nb(PNM **image, const int seuil) {
   if (*image == NULL || seuil < 0 || seuil > get_valeurMax(*image)) {
      fprintf(stderr,"Image ou seuil invalide\n");
      return;
   }

   // Si l'image est de type PPM (couleur), on la convertit en niveaux de gris
   if (get_type(*image) == 2) {
      filtre_gris(image, '2');
   }

   // Crée une nouvelle image PBM (noir et blanc)
   PNM *nb = creer_pnm(0, get_longueur(*image), get_largeur(*image), 1);
   if (!nb) {
      fprintf(stderr,"Erreur d'allocation mémoire\n");
      return;
   }

   //Déclaration des dimensions de l'image
   int lg = get_longueur(*image);
   int lr = get_largeur(*image);

   // Applique le filtre noir et blanc
   for (int i = 0; i < lg; i++) {
      for (int j = 0; j < lr; j++) {
         int pixel_actuel = get_pixel(*image, i * lr + j);
         if (pixel_actuel >= seuil) {
            set_pixel(nb, i * lr + j, 0); // Blanc
         } else {
            set_pixel(nb, i * lr + j, 1); // Noir
         }
      }
   }

   // Libère la mémoire de l'image originale
   detruire_pnm(*image);

   // Remplace l'image originale par la nouvelle image noir et blanc
   *image = nb;
}