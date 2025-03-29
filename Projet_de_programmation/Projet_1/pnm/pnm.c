/**
 * pnm.c
 *
 * Ce fichier contient les définitions de types et
 * les fonctions de manipulation d'images PNM.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/02/2025
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pnm.h"

struct PNM_t
{
   char type[3];                                // Type de l'image PNM (P1, P2, P3)
   unsigned short longueur, largeur, valeurMax; // Dimensions de l'image et valeur maximale des pixels
   unsigned short *cases;                       // Tableau de pixels de l'image
};

PNM *creer_pnm(char type[3], unsigned short longueur, unsigned short largeur, unsigned short valeurMax)
{
   if (type != NULL || longueur > 0 || largeur > 0 || valeurMax > 0)
   {
      // Alloue de la mémoire pour une nouvelle structure PNM
      PNM *pnm_image = malloc(sizeof(PNM));
      if (!pnm_image)
      {
         // Affiche un message d'erreur si l'allocation échoue
         printf("Erreur d'alloctaion memoire !");
         return NULL;
      }

      // Initialise les champs de la structure PNM avec les valeurs fournies
      pnm_image->type[0] = type[0];
      pnm_image->type[1] = type[1];
      pnm_image->type[2] = type[2];
      pnm_image->longueur = longueur;
      pnm_image->largeur = largeur;
      pnm_image->valeurMax = valeurMax;

      // Vérifie si le type d'image est P3 (image couleur)
      if (pnm_image->type[1] == '3')
      {
         // Alloue de la mémoire pour les pixels de l'image couleur
         pnm_image->cases = malloc(largeur * longueur * 3 * sizeof(unsigned short));
         if (!pnm_image->cases)
         {
            // Affiche un message d'erreur si l'allocation échoue et libère la mémoire allouée précédemment
            printf("Erreur d'alloctaion memoire !\n");
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
      printf("Erreur dans les valeurs donnees.");
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

char *get_type(PNM *pnm_image)
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
      // Retourne le type de l'image PNM
      return pnm_image->type;
   return NULL;
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

PNM *set_type(PNM *pnm_image, char type[3])
{
   // Vérifie si le pointeur pnm_image n'est pas NULL
   if (pnm_image != NULL)
   {
      // Modifie le type de l'image PNM
      pnm_image->type[0] = type[0];
      pnm_image->type[1] = type[1];
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

void ignorer_commentaires(FILE *fp)
{
   // Lit les commentaires dans le fichier
   int c;
   while ((c = fgetc(fp)) == '#')
   {
      // Ignore les lignes de commentaires
      while ((c = fgetc(fp)) != '\n')
         ;
   }
   // Remet le caractère lu dans le flux
   if (c != EOF)
   {
      // Remet le caractère lu dans le flux
      ungetc(c, fp);
   }
}

int load_pnm(PNM **image, char *filename)
{
   if (image != NULL || filename != NULL)
   {
      // Ouverture du fichier en lecture
      FILE *fp = fopen(filename, "r");
      if (!fp)
      {
         // Affiche un message d'erreur si fp n'existe pas
         printf("Fichier non-existant !");
         return -2;
      }

      char type[3];                                // Type de l'image
      unsigned short longueur, largeur, valeurMax; // Longueur, largeur et valeur maximale des pixels de l'image

      // Ignore les commentaires
      ignorer_commentaires(fp);

      // Lit le type de l'image
      fscanf(fp, "%2s\n ", type);

      if (type[0] != 'P')
      {
         printf("Format de fichier non supporte");
         fclose(fp);
         return -2;
      }

      ignorer_commentaires(fp);

      // Lit les dimensions de l'image
      fscanf(fp, "%hu %hu", &largeur, &longueur);

      ignorer_commentaires(fp);

      // Lit la valeur maximale des pixels si le type n'est pas P1
      if (type[1] != '1')
      {
         fscanf(fp, "%hu", &valeurMax);
      }

      // Crée une nouvelle image PNM avec les valeurs lues
      *image = creer_pnm(type, longueur, largeur, valeurMax);
      if (!*image)
      {
         fclose(fp);
         return -1;
      }

      // Lit les pixels de l'image en fonction du type
      switch (type[1])
      {
      // Lit les pixels pour une image en noir et blanc (P1)
      case '1':
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

      // Lit les pixels pour une image en niveaux de gris (P2)
      case '2':
         for (int i = 0; i < longueur; i++)
         {
            for (int j = 0; j < largeur; j++)
            {
               ignorer_commentaires(fp);
               fscanf(fp, "%hu", &(*image)->cases[i * largeur + j]);
            }
         };
         fclose(fp);
         return 0;

      // Lit les pixels pour une image couleur (P3)
      case '3':
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
         printf("Format de fichier non supporte");
         fclose(fp);
         return -2;
      }
      return 0;
   }
   else
   {
      printf("Nom du fichier mal formule");
      return -1;
   }
}

int write_pnm(PNM *image, char *filename)
{
   if (image != NULL || filename != NULL)
   {
      // Ouverture le fichier en écriture
      FILE *fp = fopen(filename, "w");
      if (!fp)
      {
         // Affiche un message d'erreur si le fichier ne peut pas être ouvert
         printf("Fichier non-existant !");
         return -1;
      }

      // Ecrit le type de l'image et ses dimensions dans le fichier
      fprintf(fp, "%s\n%hu %hu\n", image->type, image->largeur, image->longueur);

      // Ecrit la valeur maximale des pixels si le type n'est pas P1
      if (image->type[1] != '1')
      {
         fprintf(fp, "%hu\n", image->valeurMax);
      }

      // Ecrit les pixels de l'image en fonction du type
      switch (image->type[1])
      {
      case '1':
         // Ecrit les pixels pour une image en noir et blanc (P1)
         for (int i = 0; i < image->longueur; i++)
         {
            for (int j = 0; j < image->largeur; j++)
            {
               fprintf(fp, "%hu ", image->cases[i * image->largeur + j]);
            }
         }
         fclose(fp);
         return 0;

      case '2':
         // Ecrit la valeur maximale des pixels pour une image en niveaux de gris (P2)
         for (int i = 0; i < image->longueur; i++)
         {
            for (int j = 0; j < image->largeur; j++)
            {
               fprintf(fp, "%hu ", image->cases[i * image->largeur + j]);
            }
         };
         fclose(fp);
         return 0;

      case '3':
         // Ecrit la valeur maximale des pixels pour une image couleur (P3)
         for (int i = 0; i < image->longueur; i++)
         {
            for (int j = 0; j < image->largeur; j++)
            {
               fprintf(fp, " %hu %hu %hu", image->cases[(i * image->largeur + j) * 3],
                       image->cases[(i * image->largeur + j) * 3 + 1],
                       image->cases[(i * image->largeur + j) * 3 + 2]);
            }
         };
         fclose(fp);
         return 0;

      default:
         printf("Format de fichier non supporte");
         fclose(fp);
         return -2;
      };

      return 0;
   }
   else
   {
      printf("Nom du fichier mal formule");
      return -1;
   }
}