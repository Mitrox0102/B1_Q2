/**
 * @file pnm.h
 *
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * @author Ouazouz Sami S2404629
 * @date 23/02/2025
 */

#ifndef __PNM__
#define __PNM__

/**
 * @brief Types d'images PNM supportés
 */
typedef enum PNMType_t {
    P1, /**< Image en noir et blanc */
    P2, /**< Image en niveaux de gris */
    P3  /**< Image couleur */
} PNMType;

/**
 * @brief Structure opaque représentant une image PNM
 */
typedef struct PNM_t PNM;

/**
 * @brief Crée une nouvelle image PNM
 * @param type Type de l'image PNM (P1, P2, P3)
 * @param longueur Longueur de l'image
 * @param largeur Largeur de l'image
 * @param valeurMax Valeur maximale des pixels
 * @return Pointeur vers l'image créée ou NULL en cas d'erreur
 * 
 * @pre:
 *   - type est P1, P2 ou P3
 *   - longueur > 0
 *   - largeur > 0
 *   - valeurMax > 0
 * @post Retourne un pointeur valide vers une image PNM si succès, NULL sinon
 */
PNM *creer_pnm(PNMType type, unsigned short longueur, 
                unsigned short largeur, unsigned short valeurMax);

/**
 * @brief Libère la mémoire d'une image PNM
 * @param image Pointeur vers l'image à détruire
 * 
 * @pre image != NULL
 * @post La mémoire associée à l'image est libérée
 */
void detruire_pnm(PNM *image);

/**
 * @brief Retourne le type d'une image
 * @param image Pointeur vers l'image
 * @return Type de l'image ou -1 si erreur
 * 
 * @pre image != NULL
 * @post Retourne le type de l'image si succès, -1 sinon
 */
PNMType get_type(PNM *image);

/**
 * @brief Obtient la longueur de l'image
 * @param image Pointeur vers l'image
 * @return Longueur de l'image ou -1 si erreur
 * 
 * @pre image != NULL
 * @post Retourne la longueur de l'image si succès, -1 sinon
 */
int get_longueur(PNM *image);

/**
 * @brief Obtient la largeur de l'image
 * @param image Pointeur vers l'image
 * @return Largeur de l'image ou -1 si erreur
 * 
 * @pre image != NULL
 * @post Retourne la largeur de l'image si succès, -1 sinon
 */
int get_largeur(PNM *image);

/**
 * @brief Obtient la valeur maximale des pixels
 * @param image Pointeur vers l'image
 * @return Valeur maximale ou -1 si erreur
 * 
 * @pre image != NULL
 * @post Retourne la valeur maximale des pixels si succès, -1 sinon
 */
int get_valeurMax(PNM *image);

/**
 * @brief Obtient la valeur d'un pixel
 * @param image Pointeur vers l'image
 * @param pixel Index du pixel à lire
 * @return Valeur du pixel ou -1 si erreur
 * 
 * @pre:
 *   - image != NULL
 *   - pixel >= 0
 * @post Retourne la valeur du pixel si succès, -1 sinon
 */
int get_pixel(PNM *image, int pixel);

/**
 * @brief Modifie le type d'une image
 * @param image Pointeur vers l'image
 * @param type Nouveau type d'image
 * @return Pointeur vers l'image modifiée ou NULL si erreur
 * 
 * @pre:
 *   - image != NULL
 *   - type est P1, P2 ou P3
 * @post Retourne un pointeur valide vers l'image modifiée si succès, NULL sinon
 */
PNM *set_type(PNM *image, PNMType type);

/**
 * @brief Modifie la longueur d'une image
 * @param image Pointeur vers l'image
 * @param longueur Nouvelle longueur
 * @return Pointeur vers l'image modifiée ou NULL si erreur
 * 
 * @pre:
 *   - image != NULL
 *   - longueur > 0
 * @post Retourne un pointeur valide vers l'image modifiée si succès, NULL sinon
 */
PNM *set_longueur(PNM *image, unsigned short longueur);

/**
 * @brief Modifie la largeur d'une image
 * @param image Pointeur vers l'image
 * @param largeur Nouvelle largeur
 * @return Pointeur vers l'image modifiée ou NULL si erreur
 * 
 * @pre: 
 *   - image != NULL
 *   - largeur > 0
 * @post Retourne un pointeur valide vers l'image modifiée si succès, NULL sinon
 */
PNM *set_largeur(PNM *image, unsigned short largeur);

/**
 * @brief Modifie la valeur maximale des pixels
 * @param image Pointeur vers l'image
 * @param valeurMax Nouvelle valeur maximale
 * @return Pointeur vers l'image modifiée ou NULL si erreur
 * 
 * @pre:
 *   - image != NULL
 *   - valeurMax > 0
 * @post Retourne un pointeur valide vers l'image modifiée si succès, NULL sinon
 */
PNM *set_valeurMax(PNM *image, unsigned short valeurMax);

/**
 * @brief Modifie la valeur d'un pixel
 * @param image Pointeur vers l'image
 * @param pixel_i Index du pixel à modifier
 * @param pixel_f Nouvelle valeur du pixel
 * @return Pointeur vers l'image modifiée ou NULL si erreur
 * 
 * @pre:
 *   - image != NULL
 *   - pixel_i >= 0
 *   - pixel_f >= 0
 * @post Retourne un pointeur valide vers l'image modifiée si succès, NULL sinon
 */
PNM *set_pixel(PNM *image, int pixel_i, int pixel_f);

/**
 * @brief Charge une image depuis un fichier
 * @param image Pointeur vers le pointeur de l'image à créer
 * @param filename Nom du fichier à charger
 * @return 0 si succès, code d'erreur sinon
 * 
 * @pre:
 *   - image != NULL
 *   - filename != NULL
 * @post Retourne 0 si l'image est chargée avec succès, un code d'erreur sinon
 */
int load_pnm(PNM **image, char *filename);

/**
 * @brief Sauvegarde une image dans un fichier
 * @param image Pointeur vers l'image
 * @param filename Nom du fichier de destination
 * @return 0 si succès, code d'erreur sinon
 * 
 * @pre:
 *   - image != NULL
 *   - filename != NULL
 * @post Retourne 0 si l'image est sauvegardée avec succès, un code d'erreur sinon
 */
int write_pnm(PNM *image, char *filename);

#endif