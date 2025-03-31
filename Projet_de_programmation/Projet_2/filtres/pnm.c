/**
 * @file pnm.c
 *
 * @brief Ce fichier contient les définitions de types et
 * les fonctions de manipulation d'images PNM.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/02/2025
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"

struct PNM_t
{
   PNMType type;                                // Type de l'image PNM (P1, P2, P3)
   unsigned short longueur, largeur, valeurMax; // Dimensions de l'image et valeur maximale des pixels
   unsigned short *cases;                       // Tableau de pixels de l'image
};

PNM *creer_pnm(PNMType type, unsigned short longueur, unsigned short largeur, unsigned short valeurMax)
{
   if (type >= 0 && type <= 2 && longueur > 0 && largeur > 0 && valeurMax > 0)
   {
      // Alloue de la mémoire pour une nouvelle structure PNM
      PNM *pnm_image = malloc(sizeof(PNM));
      if (!pnm_image)
      {
         // Affiche un message d'erreur si l'allocation échoue
         printf("Erreur d'alloctaion memoire !\n");
         return NULL;
      }

      // Initialise les champs de la structure PNM avec les valeurs fournies
      pnm_image->type = type;
      pnm_image->longueur = longueur;
      pnm_image->largeur = largeur;
      pnm_image->valeurMax = valeurMax;

      // Vérifie si le type d'image est P3 (image couleur)
      if (pnm_image->type == 2)
      {
         // Alloue de la mémoire pour les pixels de l'image couleur
         pnm_image->cases = malloc(largeur * longueur * 3 * sizeof(unsigned short));
         if (!pnm_image->cases)
         {
            // Affiche un message d'erreur si l'allocation échoue et libère la mémoire allouée précédemment
            printf("Erreur d'allocation memoire !\n");
            free(pnm_image->cases);
            free(pnm_image);
            return NULL;
         }
      }
      else
      {
         // Alloue de la mémoire pour les pixels de l'image en niveaux de gris
         pnm_image->cases = malloc(largeur * longueur * sizeof(unsigned short));
         if (!pnm_image->cases)
         {
            // Affiche un message d'erreur si l'allocation échoue et libère la mémoire allouée précédemment
            printf("Erreur d'alloctaion memoire !\n");
            free(pnm_image->cases);
            free(pnm_image);
            return NULL;
         }
      }
      // Retourne le pointeur vers la nouvelle structure PNM
      return pnm_image;
   }
   else
   {
      printf("Erreur dans les valeurs donnees.\n");
      return NULL;
   }
}

void detruire_pnm(PNM *pnm_image)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
   {
      // Libère la mémoire allouée pour les pixels de l'image
      free(pnm_image->cases);
      // Libère la mémoire allouée pour la structure PNM
      free(pnm_image);
   }
}

PNMType get_type(PNM *pnm_image)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
      // Retourne le type de l'image PNM
      return pnm_image->type;
   return -1;
}

int get_longueur(PNM *pnm_image)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
      // Retourne la longueur de l'image PNM
      return pnm_image->longueur;
   return -1;
}

int get_largeur(PNM *pnm_image)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
      // Retourne la largeur de l'image PNM
      return pnm_image->largeur;
   return -1;
}

int get_valeurMax(PNM *pnm_image)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
      // Retourne la valeur maximale des pixels de l'image PNM
      return pnm_image->valeurMax;
   return -1;
}

int get_pixel(PNM *pnm_image, int pixel)
{
   if (pnm_image != NULL && pixel >=0)
   {
      return pnm_image->cases[pixel];
      return 0;
   }
   return -1;
}


PNM *set_type(PNM *pnm_image, PNMType type)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
   {
      // Modifie le type de l'image PNM
      pnm_image->type = type;
      return pnm_image;
   }
   return NULL;
}

PNM *set_longueur(PNM *pnm_image, unsigned short longueur)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
   {
      // Modifie la longueur de l'image PNM
      pnm_image->longueur = longueur;
      return pnm_image;
   }
   return NULL;
}

PNM *set_largeur(PNM *pnm_image, unsigned short largeur)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
   {
      // Modifie la largeur de l'image PNM
      pnm_image->largeur = largeur;
      return pnm_image;
   }
   return NULL;
}

PNM *set_valeurMax(PNM *pnm_image, unsigned short valeurMax)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
   {
      // Modifie la valeur maximale des pixels de l'image PNM
      pnm_image->valeurMax = valeurMax;
      return pnm_image;
   }
   return NULL;
}

PNM *set_pixel(PNM *pnm_image, int pixel_i, int pixel_f)
{
   if (pnm_image != NULL && pixel_i >= 0 && pixel_f >= 0)
   {
      pnm_image->cases[pixel_i] = pixel_f;
   }
   return NULL;
}

static void ignorer_commentaires(FILE *fp)
{
   // Lit les commentaires dans le fichier
   int c;
   while ((c = fgetc(fp)) == '#')
   {
      // Ignore les lignes de commentaires
      while ((c = fgetc(fp)) != '\n' && c != EOF)
         ;
   }

   // Remet le caractère lu dans le flux
   ungetc(c, fp);
}

// Vérifie l'extension du fichier

static int verif_extension(char *filename)
{
   if (filename == NULL)
   {
      printf("Nom de fichier invalide\n");
      return -1;
   }

   int len = strlen(filename);
   if (len < 4 || (strcmp(filename + len - 3, "pbm") != 0 && strcmp(filename + len - 3, "pgm") != 0 && strcmp(filename + len - 3, "ppm") != 0))
   {
      printf("Extension du fichier incorrecte\n");
      return -2;
   }
   return 0;
}

static char *type_vers_chaine(PNMType type)
{
   // Retourne le type de l'image PNM sous forme de chaîne de caractères
   switch (type)
   {
   case 0:
      return "P1";
   case 1:
      return "P2";
   case 2:
      return "P3";
   default:
      printf("Type non reconnu!");
      return NULL;
   }
}

static PNMType chaine_vers_type(char *chaine)
{
   // Retourne le type de l'image PNM en fonction de la chaîne de caractères
   if (strcmp(chaine, "P1") == 0)
   {
      return 0;
   }
   else if (strcmp(chaine, "P2") == 0)
   {
      return 1;
   }
   else if (strcmp(chaine, "P3") == 0)
   {
      return 2;
   }
   else
   {
      printf("Chaine_vers_type_echec");
      return 3;
   }
}

int load_pnm(PNM **image, char *filename)
{
   if (image != NULL && filename != NULL)
   {
      // Vérifie l'extension du fichier
      printf("Résultat verif_extension : %d\n", verif_extension(filename));
      if (verif_extension(filename) < 0)
      {
         return -1;
      }

      // Ouverture du fichier en lecture
      FILE *fp = fopen(filename, "r");
      if (!fp)
      {
         // Affiche un message d'erreur si fp n'existe pas
         printf("Fichier non-existant !\n");
         return -2;
      }

      PNMType type;                                    // Type de l'image
      unsigned short longueur, largeur, valeurMax = 1; // Longueur, largeur et valeur maximale des pixels de l'image
      char format[3];                                  // Chaîne de caractères pour stocker le type de l'image

      // Ignore les commentaires
      ignorer_commentaires(fp);

      // Lit le type de l'image
      fscanf(fp, "%2s\n ", format);

      printf("Format détecté : '%s'\n", format);
      

      type = chaine_vers_type(format);
      printf("Type détecté : %d\n", type);
      // if (type >= 0 && type <= 2)
      // {
      //    printf("Type valide : %d\n", type);
      // }
      // else
      // {
      //    printf("Format de fichier non supporte\n");
      //    fclose(fp);
      //    return -2;
      // }

      ignorer_commentaires(fp);

      // Lit les dimensions de l'image
      fscanf(fp, "%hu %hu", &largeur, &longueur);

      if (largeur == 0 || longueur == 0)
      {
         printf("Dimensions erronees\n");
         return -3;
      };

      ignorer_commentaires(fp);

      // Lit la valeur maximale des pixels si le type n'est pas P1
      if (type != 0)
      {
         fscanf(fp, "%hu", &valeurMax);
         if (valeurMax <= 0 || valeurMax > 255)
         {
            printf("Valeur maximum d'un pixel erronee\n");
            return -3;
         }
      }

      // Crée une nouvelle image PNM avec les valeurs lues
      *image = creer_pnm(type, longueur, largeur, valeurMax);
      if (!*image)
      {
         fclose(fp);
         return -1;
      }

      // Lit les pixels de l'image en fonction du type
      switch (type)
      {
      // Lit les pixels pour une image en noir et blanc (P1)
      case 0:
      case 1:
         for (int i = 0; i < longueur; i++)
         {
            for (int j = 0; j < largeur; j++)
            {
               ignorer_commentaires(fp);
               fscanf(fp, "%hu ", &(*image)->cases[i * largeur + j]);
            }
         }
         fclose(fp);
         return 0;

      // Lit les pixels pour une image couleur (P3)
      case 2:
         for (int i = 0; i < longueur; i++)
         {
            for (int j = 0; j < largeur; j++)
            {
               ignorer_commentaires(fp);
               fscanf(fp, " %hu %hu %hu", &(*image)->cases[(i * largeur + j) * 3],
                      &(*image)->cases[(i * largeur + j) * 3 + 1],
                      &(*image)->cases[(i * largeur + j) * 3 + 2]);
            }
         };
         fclose(fp);
         return 0;
      default:
         // Affiche un message d'erreur si le format de fichier n'est pas supporté
         printf("Format de fichier non supporte\n");
         fclose(fp);
         return -2;
      }
      return 0;
   }
   else
   {
      printf("Nom du fichier mal formule\n");
      return -1;
   }
}

int write_pnm(PNM *image, char *filename)
{
   if (image == NULL || filename == NULL)
   {
      printf("Paramètres invalides\n");
      return -1;
   }

   char *type_str = type_vers_chaine(image->type);
   if (type_str == NULL)
   {
      printf("Type d'image non supporté\n");
      return -2;
   }

   FILE *fp = fopen(filename, "w");
   if (!fp)
   {
      printf("Impossible d'ouvrir le fichier en écriture\n");
      return -1;
   }

   // Écriture de l'en-tête
   fprintf(fp, "%s\n%hu %hu\n", type_str, image->largeur, image->longueur);

   // Écriture de la valeur max pour P2 et P3
   if (image->type != 0)
   {
      fprintf(fp, "%hu\n", image->valeurMax);
   }

   // Écriture des pixels
   switch (image->type)
   {
      case 0:  // PBM
      case 1:  // PGM
            for (int i = 0; i < image->longueur; i++)
            {
               for (int j = 0; j < image->largeur; j++)
               {
                  fprintf(fp, "%hu ", image->cases[i * image->largeur + j]);
               }
            }
            break;

      case 2:  // PPM
            for (int i = 0; i < image->longueur; i++)
            {
               for (int j = 0; j < image->largeur; j++)
               {
                  fprintf(fp, " %hu %hu %hu ", image->cases[(i * image->largeur + j) * 3],
                       image->cases[(i * image->largeur + j) * 3 + 1],
                       image->cases[(i * image->largeur + j) * 3 + 2]);
               }
            }
            break;

      default:
            fclose(fp);
            return -2;
   }

   fclose(fp);
   return 0;
}