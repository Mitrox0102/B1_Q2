/**
 * pnm.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/02/2025
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * Prototypes des fonctions de manipulation d'images PNM
 *
 */

PNM *creer_pnm(char type[3], unsigned short longueur, unsigned short largeur, unsigned short valeurMax);
/**
 * creer_pnm
 *
 * Crée une nouvelle image PNM avec les spécifications données.
 *
 * @param type le type de l'image PNM (P1, P2, P3).
 * @param longueur la longueur de l'image.
 * @param largeur la largeur de l'image.
 * @param valeurMax la valeur maximale des pixels (pour les types P2 et P3).
 *
 * @pre: type != NULL, longueur > 0, largeur > 0, valeurMax > 0
 * @post: retourne un pointeur sur une nouvelle image PNM initialisée avec les valeurs spécifiées.
 *
 * @return:
 *     Un pointeur sur l'image PNM créée en cas de succès.
 *     NULL en cas d'erreur d'allocation de mémoire.
 */

void detruire_pnm(PNM *image);
/**
 * detruire_pnm
 *
 * Libère la mémoire allouée pour une image PNM.
 *
 * @param image un pointeur sur l'image PNM à détruire.
 *
 * @pre: image != NULL
 * @post: la mémoire allouée pour l'image PNM est libérée.
 */

char *get_type(PNM *image);
/**
 * get_type
 *
 * Retourne le type d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 *
 * @pre: image != NULL
 * @post: retourne le type de l'image PNM.
 *
 * @return:
 *     Le type de l'image PNM en cas de succès.
 *     NULL si l'image est NULL.
 */

int get_longueur(PNM *image);
/**
 * get_longueur
 *
 * Retourne la longueur d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 *
 * @pre: image != NULL
 * @post: retourne la longueur de l'image PNM.
 *
 * @return:
 *     La longueur de l'image PNM en cas de succès.
 *     -1 si l'image est NULL.
 */

int get_largeur(PNM *image);
/**
 * get_largeur
 *
 * Retourne la largeur d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 *
 * @pre: image != NULL
 * @post: retourne la largeur de l'image PNM.
 *
 * @return:
 *     La largeur de l'image PNM en cas de succès.
 *     -1 si l'image est NULL.
 */

int get_valeurMax(PNM *image);
/**
 * get_valeurMax
 *
 * Retourne la valeur maximale des pixels d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 *
 * @pre: image != NULL
 * @post: retourne la valeur maximale des pixels de l'image PNM.
 *
 * @return:
 *     La valeur maximale des pixels de l'image PNM en cas de succès.
 *     -1 si l'image est NULL.
 */

PNM *set_type(PNM *image, char type[3]);
/**
 * set_type
 *
 * Modifie le type d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 * @param type le nouveau type de l'image PNM (P1, P2, P3).
 *
 * @pre: image != NULL, type != NULL
 * @post: le type de l'image PNM est modifié.
 *
 * @return:
 *     Un pointeur sur l'image PNM modifiée en cas de succès.
 *     NULL si l'image est NULL.
 */

PNM *set_longueur(PNM *image, unsigned short longueur);
/**
 * set_longueur
 *
 * Modifie la longueur d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 * @param longueur la nouvelle longueur de l'image.
 *
 * @pre: image != NULL, longueur > 0
 * @post: la longueur de l'image PNM est modifiée.
 *
 * @return:
 *     Un pointeur sur l'image PNM modifiée en cas de succès.
 *     NULL si l'image est NULL.
 */

PNM *set_largeur(PNM *image, unsigned short largeur);
/**
 * set_largeur
 *
 * Modifie la largeur d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 * @param largeur la nouvelle largeur de l'image.
 *
 * @pre: image != NULL, largeur > 0
 * @post: la largeur de l'image PNM est modifiée.
 *
 * @return:
 *     Un pointeur sur l'image PNM modifiée en cas de succès.
 *     NULL si l'image est NULL.
 */

PNM *set_valeurMax(PNM *image, unsigned short valeurMax);
/**
 * set_valeurMax
 *
 * Modifie la valeur maximale des pixels d'une image PNM.
 *
 * @param image un pointeur sur l'image PNM.
 * @param valeurMax la nouvelle valeur maximale des pixels.
 *
 * @pre: image != NULL, valeurMax > 0
 * @post: la valeur maximale des pixels de l'image PNM est modifiée.
 *
 * @return:
 *     Un pointeur sur l'image PNM modifiée en cas de succès.
 *     NULL si l'image est NULL.
 */

void ignorer_commentaires(FILE *fp);
/**
 * ignorer_commentaires
 *
 * Ignore les lignes de commentaires dans un fichier PNM.
 *
 * @param fp un pointeur sur le fichier à lire.
 *
 * @pre: fp != NULL
 * @post: les lignes de commentaires dans le fichier sont ignorées.
 */

int load_pnm(PNM **image, char *filename);
/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */

int write_pnm(PNM *image, char *filename);
/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */

#endif