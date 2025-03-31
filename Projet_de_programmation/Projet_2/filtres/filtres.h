/**
 * @file filtres.h
 *
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour l'application de filtres à des images PNM.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/03/2025
 * @projet: INFO0030 Projet 2
 */

#ifndef FILTRES_H
#define FILTRES_H

#include <pnm.h>

/**
 * @brief Enumération des différents types de filtres disponibles
 */
typedef enum Filtre_t {
   retournement,   /**< Retournement de l'image */
   monochrome,     /**< Conversion en monochrome (r,v,b)*/
   negatif,        /**< Inversion des couleurs */
   gris,           /**< Conversion en niveaux de gris*/
   nb              /**< Conversion en noir et blanc avec seuil*/
} Filtre;


/**
 * @pre: 
 *   - image != NULL
 *   - *image doit être un pointeur valide vers une structure PNM.
 * @post: 
 *   - L'image PNM est retournée avec un retournement à 180°.
 * 
 * @brief Applique un retournement 180° sur une image PNM.
 * @param image Pointeur vers l'image PNM à modifier.
 */
void filtre_retournement(PNM **image);

/**
 * @pre: 
 *   - image != NULL
 *   - *image doit être un pointeur valide vers une structure PNM.
 *   - L'image doit être de type PPM (type 2).
 *   - couleur doit être 'r', 'v' ou 'b'.
 * @post: 
 *   - L'image PNM est retournée avec un filtre monochrome appliqué.
 * 
 * @brief Applique un filtre monochrome sur une image PPM.
 * @param image Pointeur vers l'image PNM à modifier.
 * @param couleur 'r' pour rouge, 'v' pour vert, 'b' pour bleu.
 */
void filtre_monochrome(PNM **image, char couleur);

/**
 * @pre: 
 *   - image != NULL
 *   - *image doit être un pointeur valide vers une structure PNM.
 *   - Le format de l'image doit être de type PPM (type 2).
 * @post: 
 *   - L'image PNM est retournée avec un filtre négatif appliqué.
 * 
 * @brief Applique un filtre négatif sur une image PNM.
 * @param image Pointeur vers l'image PNM à modifier.
 */
void filtre_negatif(PNM **image);

/**
 * @pre: 
 *   - image != NULL
 *   - *image doit être un pointeur valide vers une structure PNM.
 *   - L'image doit être de type PPM (type 2).
 * @post: 
 *   - L'image PNM est retournée en nuances de gris.
 * 
 * @brief Applique un filtre de conversion en nuances de gris sur une image PPM.
 * @param image Pointeur vers l'image PNM à modifier.
 * @param methode Indique la méthode que l'utilisateur va utiliser '1' ou '2'
 */
void filtre_gris(PNM **image, char methode);

/**
 * @pre: 
 *   - image != NULL
 *   - *image doit être un pointeur valide vers une structure PNM.
 *   - seuil doit être compris entre 0 et la valeur maximale des pixels 
 *   - de l'image.
 * @post: 
 *   - L'image PNM est retournée en noir et blanc.
 * 
 * @brief Applique un filtre Noir & Blanc sur une image PPM ou PGM et renvoie
 *        une image PBM (type 0).
 * @param image Pointeur vers l'image PNM à modifier.
 * @param seuil Seuil de binarisation (0-255).
 */
void filtre_nb(PNM **image, const int seuil);

#endif