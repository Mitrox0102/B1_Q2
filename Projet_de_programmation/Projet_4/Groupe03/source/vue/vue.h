/**
 * @file vue.h
 * @brief Définit les fonctions de l'interface graphique
 * @author Qayyum Muhammad & Gazouz Sami
 * @date Mai 2025
 */

#ifndef _VUE_H
#define _VUE_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../modele/modele.h"
#include "../controle/controle.h"

/**
 * @struct Data
 * @brief Structure pour stocker des données lors de la recherche d'un widget
 */
typedef struct
{
   GtkWidget *est_widget;
   gboolean est_trouve;
} Data;

/**
 * @struct MiseAJour
 * @brief Structure pour stocker des informations lors de la mise à jour d'un bouton
 */
typedef struct
{
   int ligne_actuelle;
   int colonne_actuelle;
   GtkWidget *est_bouton;
   Plateau *plateau;
} MiseAJour;

/**
 * @fn GtkWidget *creer_fenetre(void)
 * @brief Crée la fenêtre principale du jeu
 * @pre GTK doit être initialisé
 * @post Une fenêtre GTK est créée et configurée
 * @return Widget de la fenêtre créée
 */
GtkWidget *creer_fenetre(void);

/**
 * @fn GtkWidget *creer_barre_outils(void)
 * @brief Crée la barre d'outils avec les menus
 * @pre GTK doit être initialisé
 * @post Une barre d'outils avec menus est créée
 * @return Widget de la barre d'outils
 */
GtkWidget *creer_barre_outils(void);

/**
 * @fn char *demander_nom_joueur(void)
 * @brief Affiche une boîte de dialogue pour demander le nom du joueur
 * @pre GTK doit être initialisé et fenetre_principale != NULL
 * @post Retourne une chaîne allouée contenant le nom du joueur ou NULL
 * @return Nom du joueur ou NULL si annulé
 */
char *demander_nom_joueur(void);

/**
 * @fn GtkWidget *creer_grille(Plateau* plateau)
 * @brief Crée la grille de jeu à partir du plateau
 * @param plateau Pointeur vers le plateau
 * @pre plateau != NULL
 * @post Une grille GTK est créée avec des boutons pour chaque case
 * @return Widget de la grille créée
 */
GtkWidget *creer_grille(Plateau *plateau);

/**
 * @fn GtkWidget *creer_suivants_et_score(GtkWidget **boutons_suivants, GtkWidget **label_score, Plateau* plateau)
 * @brief Crée les widgets pour afficher les boules suivantes et le score
 * @param boutons_suivants Tableau pour stocker les boutons des boules suivantes
 * @param label_score Pointeur pour stocker le label du score
 * @param plateau Pointeur vers le plateau
 * @pre boutons_suivants != NULL et label_score != NULL et plateau != NULL
 * @post Les widgets sont créés et les pointeurs mis à jour
 * @return Widget conteneur créé
 */
GtkWidget *creer_suivants_et_score(GtkWidget **boutons_suivants, GtkWidget **label_score, Plateau *plateau);

/**
 * @fn void afficher_dialogue_scores(void)
 * @brief Affiche une boîte de dialogue avec les meilleurs scores
 * @pre fenetre_principale != NULL et fichier_scores accessibles
 * @post Un dialogue modal affichant les scores est montré
 */
void afficher_dialogue_scores(void);

/**
 * @fn void afficher_dialogue_a_propos(void)
 * @brief Affiche une boîte de dialogue avec les informations sur le jeu
 * @pre fenetre_principale != NULL
 * @post Un dialogue modal "À propos" est affiché
 */
void afficher_dialogue_a_propos(void);

/**
 * @fn void afficher_dialogue_regles(void)
 * @brief Affiche une boîte de dialogue avec les règles du jeu
 * @pre fenetre_principale != NULL
 * @post Un dialogue modal avec les règles du jeu est affiché
 */
void afficher_dialogue_regles(void);

/**
 * @fn void afficher_dialogue_fin_de_partie(GtkWindow *parent, int score)
 * @brief Affiche une boîte de dialogue de fin de partie
 * @param parent Fenêtre parente
 * @param score Score final du joueur
 * @pre parent != NULL
 * @post Un dialogue modal de fin de partie est affiché avec le score final
 */
void afficher_dialogue_fin_de_partie(GtkWindow *parent, int score);

/**
 * @fn void afficher_message_perdu(GtkWidget *parent)
 * @brief Affiche un message indiquant que le joueur a perdu
 * @param parent Widget parent pour la boîte de dialogue
 * @pre parent != NULL
 * @post Une boîte de dialogue d'information est affichée
 */
void afficher_message_perdu(GtkWidget *parent);

/**
 * @fn void callback_trouver_bouton(GtkWidget *bouton_case, gpointer donnees_ptr)
 * @brief Fonction callback pour trouver un bouton spécifique
 * @param bouton_case Bouton à vérifier
 * @param donnees_ptr Pointeur vers les données de recherche
 * @pre bouton_case != NULL et donnees_ptr != NULL
 * @post Les données de recherche sont mises à jour si le bouton correspond
 */
void callback_trouver_bouton(GtkWidget *bouton_case, gpointer donnees_ptr);

/**
 * @fn void callback_trouver_vbox(GtkWidget *widget, gpointer data)
 * @brief Fonction callback pour trouver une boîte verticale
 * @param widget Widget à vérifier
 * @param data Pointeur vers les données de recherche
 * @pre widget != NULL et data != NULL
 * @post Les données de recherche sont mises à jour si le widget est une VBox
 */
void callback_trouver_vbox(GtkWidget *widget, gpointer data);

/**
 * @fn void callback_trouver_table(GtkWidget *widget, gpointer data)
 * @brief Fonction callback pour trouver une table
 * @param widget Widget à vérifier
 * @param data Pointeur vers les données de recherche
 * @pre widget != NULL et data != NULL
 * @post Les données de recherche sont mises à jour si le widget est une Table
 */
void callback_trouver_table(GtkWidget *widget, gpointer data);

/**
 * @fn void callback_connecter_signal_bouton(GtkWidget *bouton, gpointer data_plateau)
 * @brief Fonction callback pour connecter un signal à un bouton
 * @param bouton Bouton à connecter
 * @param data_plateau Données du plateau
 * @pre bouton != NULL et GTK_IS_BUTTON(bouton) et data_plateau != NULL
 * @post Le signal "clicked" du bouton est connecté à la fonction maj_grille
 */
void callback_connecter_signal_bouton(GtkWidget *bouton, gpointer data_plateau);

/**
 * @fn void connecter_signaux_grille(GtkWidget *grille, Plateau* plateau)
 * @brief Connecte les signaux à tous les boutons de la grille
 * @param grille Widget de la grille
 * @param plateau Pointeur vers le plateau
 * @pre grille != NULL et plateau != NULL
 * @post Tous les boutons de la grille sont connectés à maj_grille
 */
void connecter_signaux_grille(GtkWidget *grille, Plateau *plateau);

/**
 * @fn void callback_nouvelle_partie(GtkWidget *button, gpointer dialog)
 * @brief Fonction callback pour commencer une nouvelle partie
 * @param button Bouton activé
 * @param dialog Boîte de dialogue à fermer
 * @pre Aucune précondition forte
 * @post Le dialogue est fermé et une nouvelle partie est lancée
 */
void callback_nouvelle_partie(GtkWidget *button, gpointer dialog);

/**
 * @fn void redemarrer_jeu(GtkWidget *widget, gpointer data)
 * @brief Redémarre le jeu avec les paramètres actuels
 * @param widget Widget activateur
 * @param data Données supplémentaires (non utilisées)
 * @pre plateau_actuel != NULL
 * @post Le jeu est redémarré avec les mêmes paramètres et un nouveau plateau
 */
void redemarrer_jeu(GtkWidget *widget, gpointer data);

#endif // _VUE_H
