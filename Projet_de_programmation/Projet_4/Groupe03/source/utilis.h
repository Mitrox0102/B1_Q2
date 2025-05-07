/**
 * @file utilis.h
 * @brief Définit les fonctions utilitaires et structures auxiliaires
 * @author Qayyum Muhammad & Gazouz Sami
 * @date Mai 2025
 */

#ifndef UTILIS_H
#define UTILIS_H

#include <stdio.h>
#include <gtk/gtk.h>
#include "modele/modele.h"

#define IMAGE_BLUE    "source/assets/images/blue.png"
#define IMAGE_CYAN    "source/assets/images/cyan.png"
#define IMAGE_GREEN   "source/assets/images/green.png"
#define IMAGE_ORANGE  "source/assets/images/orange.png"
#define IMAGE_PURPLE  "source/assets/images/purple.png"
#define IMAGE_RED     "source/assets/images/red.png"
#define IMAGE_YELLOW  "source/assets/images/yellow.png"
#define IMAGE_C_SHARP "source/assets/images/c_sharp.png"
#define IMAGE_C       "source/assets/images/c.png"
#define IMAGE_HTML    "source/assets/images/html.png"
#define IMAGE_JAVASCRIPT "source/assets/images/js.png"
#define IMAGE_PYTHON "source/assets/images/python.png"


/**
 * @struct Boule
 * @brief Structure représentant une boule avec sa couleur et son image
 */
typedef struct
{
   Couleur couleur;
   GtkWidget *image;
} Boule;

/**
 * @fn int generer_difficulte(Plateau* plateau)
 * @brief Génère un niveau de difficulté aléatoire pour le jeu
 * @param plateau Pointeur vers le plateau de jeu
 * @pre plateau != NULL
 * @post Retourne une valeur de difficulté entre 0 et 2
 * @return Niveau de difficulté généré (0-2)
 */
int generer_difficulte(Plateau *plateau);

/**
 * @fn void mettre_a_jour_score(GtkWidget *label, int score)
 * @brief Met à jour l'affichage du score dans l'interface
 * @param label Widget label affichant le score
 * @param score Nouvelle valeur du score
 * @pre label != NULL et GTK_IS_LABEL(label)
 * @post Le texte du label est mis à jour avec la nouvelle valeur du score
 */
void mettre_a_jour_score(GtkWidget *label, int score);

/**
 * @fn GtkWidget *charger_image_button(const char *filename)
 * @brief Crée un bouton avec une image à partir d'un fichier
 * @param filename Chemin du fichier image
 * @pre filename != NULL et le fichier existe
 * @post Retourne un bouton GTK contenant l'image ou NULL en cas d'erreur
 * @return Widget bouton créé ou NULL en cas d'erreur
 */
GtkWidget *charger_image_button(const char *filename);

/**
 * @fn const char *get_image_from_color(Couleur couleur)
 * @brief Obtient le chemin du fichier image correspondant à une couleur
 * @param couleur Couleur pour laquelle on veut l'image
 * @pre La valeur de couleur doit être valide (entre BLEU et JAUNE)
 * @post Retourne un chemin de fichier image valide ou NULL si couleur invalide
 * @return Chemin du fichier image ou NULL si couleur invalide
 */
const char *get_image_from_color(Couleur couleur);

/**
 * @fn void generation_boules(Plateau* plateau)
 * @brief Génère des boules aléatoirement sur le plateau
 * @param plateau Pointeur vers le plateau
 * @pre plateau != NULL
 * @post Des boules sont placées aléatoirement sur le plateau et 
 * nb_cases_remplies est mis à jour
 * @details Place des boules de couleurs aléatoires sur des cases vides 
 * du plateau
 */
void generation_boules(Plateau *plateau);

/**
 * @fn void preparer_boules_suivantes(Plateau* p)
 * @brief Prépare les boules qui apparaîtront au prochain tour
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Les couleurs des boules suivantes sont générées aléatoirement
 */
void preparer_boules_suivantes(Plateau *p);

/**
 * @fn void maj_boutons_suivants(GtkWidget **boutons_suivants, Plateau* p)
 * @brief Met à jour les boutons affichant les boules suivantes
 * @param boutons_suivants Tableau de widgets boutons
 * @param p Pointeur vers le plateau
 * @pre boutons_suivants != NULL et p != NULL
 * @post Les boutons affichent les images correspondant aux couleurs des boules 
 * suivantes
 */
void maj_boutons_suivants(GtkWidget **boutons_suivants, Plateau *p);

/**
 * @fn void generation_boules_depuis_liste(Plateau* p, int boules_a_placer)
 * @brief Génère des boules sur le plateau à partir de la liste des boules 
 * suivantes
 * @param p Pointeur vers le plateau
 * @param boules_a_placer Nombre de boules à placer
 * @pre p != NULL et boules_a_placer > 0
 * @post Des boules sont placées sur le plateau selon les couleurs des boules 
 * suivantes
 */
void generation_boules_depuis_liste(Plateau *p, int boules_a_placer);

/**
 * @fn void detruire_boules_suivantes(Plateau* p)
 * @brief Libère la mémoire des boules suivantes
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Les widgets des boules suivantes sont détruits et les références 
 * nullifiées
 */
void detruire_boules_suivantes(Plateau *p);

const char *recuperer_nom_joueur(void);

bool est_benoit_donnet(const char *nom);

#endif // UTILIS_H
