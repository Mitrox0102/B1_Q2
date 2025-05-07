/**
 * @file controle.h
 * @brief Définit les fonctions de contrôle du jeu
 * @author Qayyum Muhammad & Gazouz Sami
 * @date Mai 2025
 */

#ifndef CONTROLE_H
#define CONTROLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gtk/gtk.h>
#include "../modele/modele.h"
#include "../vue/vue.h"
#include "../utilis.h"

// Variables globales
/**
 * @var fenetre_principale
 * @brief Widget de la fenêtre principale du jeu
 */
extern GtkWidget *fenetre_principale;

/**
 * @var grille_actuelle
 * @brief Widget de la grille de jeu actuelle
 */
extern GtkWidget *grille_actuelle;

/**
 * @var plateau_actuel
 * @brief Pointeur vers le plateau de jeu actuel
 */
extern Plateau *plateau_actuel;

/**
 * @var fichier_scores
 * @brief Chemin vers le fichier de scores
 */
extern char *fichier_scores;

/**
 * @var label_score_global
 * @brief Widget du label affichant le score
 */
extern GtkWidget *label_score_global;

/**
 * @struct InfosCallback
 * @brief Structure pour stocker des informations dans les callbacks
 */
typedef struct
{
   int ligne_actuelle;
   int colonne_actuelle;
   Plateau *plateau;
} InfosCallback;

/**
 * @fn void maj_grille(GtkWidget *bouton_clique, gpointer donnees_plateau)
 * @brief Met à jour la grille suite à un clic sur un bouton
 * @param bouton_clique Bouton sur lequel l'utilisateur a cliqué
 * @param donnees_plateau Pointeur vers le plateau
 * @pre bouton_clique != NULL et donnees_plateau != NULL
 * @post La grille est mise à jour selon l'action effectuée (sélection ou déplacement)
 */
void maj_grille(GtkWidget *bouton_clique, gpointer donnees_plateau);

/**
 * @fn void detruire_widget(GtkWidget *widget, gpointer data)
 * @brief Détruit un widget
 * @param widget Widget à détruire
 * @param data Données supplémentaires (non utilisées)
 * @pre widget != NULL
 * @post Le widget est détruit s'il est valide
 */
void detruire_widget(GtkWidget *widget, gpointer data);

/**
 * @fn void recreer_grille(GtkWidget *fenetre_principale, Plateau* nouveau_plateau)
 * @brief Recrée la grille de jeu
 * @param fenetre_principale Fenêtre principale du jeu
 * @param nouveau_plateau Nouveau plateau de jeu
 * @pre fenetre_principale != NULL et nouveau_plateau != NULL
 * @post Une nouvelle grille est créée et intégrée à l'interface
 */
void recreer_grille(GtkWidget *fenetre_principale, Plateau *nouveau_plateau);

/**
 * @fn void changer_niveau(GtkMenuItem *item, gpointer user_data)
 * @brief Change le niveau de difficulté du jeu
 * @param item Item de menu activé
 * @param user_data Niveau de difficulté (GINT_TO_POINTER)
 * @pre fenetre_principale != NULL
 * @post Le niveau de difficulté est changé et une nouvelle partie est lancée
 */
void changer_niveau(GtkMenuItem *item, gpointer user_data);

/**
 * @fn void nouvelle_partie(GtkMenuItem *item, gpointer user_data)
 * @brief Commence une nouvelle partie
 * @param item Item de menu activé (peut être NULL)
 * @param user_data Données supplémentaires (non utilisées)
 * @pre fenetre_principale != NULL
 * @post Une nouvelle partie est créée avec les paramètres appropriés
 */
void nouvelle_partie(GtkMenuItem *item, gpointer user_data);

/**
 * @fn void quitter_jeu(GtkMenuItem *item, gpointer user_data)
 * @brief Quitte le jeu
 * @param item Item de menu activé
 * @param user_data Données supplémentaires (non utilisées)
 * @pre Aucune précondition forte
 * @post La boucle principale GTK est terminée
 */
void quitter_jeu(GtkMenuItem *item, gpointer user_data);

/**
 * @fn void afficher_meilleurs_scores(GtkMenuItem *item, gpointer user_data)
 * @brief Affiche les meilleurs scores
 * @param item Item de menu activé
 * @param user_data Données supplémentaires (non utilisées)
 * @pre fenetre_principale != NULL
 * @post La boîte de dialogue des scores est affichée
 */
void afficher_meilleurs_scores(GtkMenuItem *item, gpointer user_data);

/**
 * @fn void afficher_a_propos(GtkMenuItem *item, gpointer user_data)
 * @brief Affiche la boîte de dialogue "À propos"
 * @param item Item de menu activé
 * @param user_data Données supplémentaires (non utilisées)
 * @pre fenetre_principale != NULL
 * @post La boîte de dialogue "À propos" est affichée
 */
void afficher_a_propos(GtkMenuItem *item, gpointer user_data);

/**
 * @fn void afficher_regles(GtkMenuItem *item, gpointer user_data)
 * @brief Affiche les règles du jeu
 * @param item Item de menu activé
 * @param user_data Données supplémentaires (non utilisées)
 * @pre fenetre_principale != NULL
 * @post La boîte de dialogue des règles est affichée
 */
void afficher_regles(GtkMenuItem *item, gpointer user_data);

/**
 * @fn int trouver_alignements(Plateau* plateau, GtkWidget *label_score)
 * @brief Trouve les alignements de boules et met à jour le score
 * @param plateau Pointeur vers le plateau
 * @param label_score Label affichant le score
 * @pre plateau != NULL et label_score != NULL
 * @post Les alignements sont identifiés, le score est mis à jour
 * @return Nombre d'alignements trouvés
 */
int trouver_alignements(Plateau *plateau, GtkWidget *label_score);

/**
 * @fn bool chercher_chemin(Plateau* plateau, int depart_x, int depart_y, int arrivee_x, int arrivee_y)
 * @brief Recherche un chemin entre deux cases
 * @param plateau Pointeur vers le plateau
 * @param depart_x Coordonnée X de départ
 * @param depart_y Coordonnée Y de départ
 * @param arrivee_x Coordonnée X d'arrivée
 * @param arrivee_y Coordonnée Y d'arrivée
 * @pre plateau != NULL, coordonnées valides (dans les limites du plateau)
 * @post Retourne true si un chemin existe, false sinon
 * @return true si un chemin existe, false sinon
 */
bool chercher_chemin(Plateau *plateau, int depart_x, int depart_y, int arrivee_x, int arrivee_y);

/**
 * @fn bool chemin_possible(Plateau* plateau, Case* depart, Case* arrivee)
 * @brief Vérifie s'il existe un chemin entre deux cases
 * @param plateau Pointeur vers le plateau
 * @param depart Case de départ
 * @param arrivee Case d'arrivée
 * @pre plateau != NULL, depart != NULL, arrivee != NULL
 * @post Retourne true si un chemin existe, false sinon
 * @return true si un chemin existe, false sinon
 */
bool chemin_possible(Plateau *plateau, Case *depart, Case *arrivee);

#endif // CONTROLE_H
