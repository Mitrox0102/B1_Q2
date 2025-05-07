/**
 * @file modele.h
 * @brief Définit les structures de données principales et leurs fonctions associées
 * @author Qayyum Muhammad & Gazouz Sami
 * @date Mai 2025
 */

#ifndef MODELE_H
#define MODELE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <gtk/gtk.h>

#define MAX_SCORES 10
#define MAX_NOM 50
#define MAX_SUIVANTS 5

/**
 * @enum Couleur
 * @brief Énumération des couleurs possibles pour les boules du jeu
 */
typedef enum
{
   BLEU,
   CYAN,
   VERT,
   ORANGE,
   MAUVE,
   ROUGE,
   JAUNE,
   C,
   C_SHARP,
   HTML,
   JS,
   PYTHON
} Couleur;

/**
 * @struct Plateau_t
 * @brief Structure principale représentant le plateau de jeu (type opaque)
 * @details Contient toutes les informations sur l'état du jeu
 */
typedef struct Plateau_t Plateau;

/**
 * @struct Case_t
 * @brief Structure représentant une case du plateau de jeu (type opaque)
 * @details Contient l'état d'occupation, la couleur et l'image associée
 */
typedef struct Case_t Case;

/**
 * @struct Score_t
 * @brief Structure représentant un score dans le jeu (type opaque)
 * @details Contient le nom du joueur et la valeur du score
 */
typedef struct Score_t Score;

/**
 * @fn Plateau* plateau_create(int largeur, int hauteur, int nb_types, int symboles_par_tour, int difficulte)
 * @brief Crée un nouveau plateau de jeu avec les paramètres spécifiés
 * @param largeur Largeur du plateau (nombre de colonnes)
 * @param hauteur Hauteur du plateau (nombre de lignes)
 * @param nb_types Nombre de types de symboles différents
 * @param symboles_par_tour Nombre de nouveaux symboles par tour
 * @param difficulte Niveau de difficulté du jeu (0=facile, 1=moyen, 2=difficile)
 * @pre largeur > 0, hauteur > 0, nb_types > 0, symboles_par_tour > 0, 0 <= difficulte <= 2
 * @post Un plateau est créé et initialisé ou NULL en cas d'erreur
 * @return Pointeur vers le nouveau plateau ou NULL en cas d'erreur
 */
Plateau *plateau_create(int largeur, int hauteur, int nb_types, int symboles_par_tour, int difficulte);

/**
 * @fn void plateau_destroy(Plateau* p)
 * @brief Libère la mémoire allouée pour un plateau de jeu
 * @param p Pointeur vers le plateau à détruire
 * @pre p peut être NULL (fonction sans effet dans ce cas)
 * @post La mémoire allouée pour le plateau est libérée
 */
void plateau_destroy(Plateau *p);

/**
 * @fn int plateau_get_largeur(Plateau* p)
 * @brief Obtient la largeur du plateau
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne la largeur du plateau
 * @return Largeur du plateau (nombre de colonnes)
 */
int plateau_get_largeur(Plateau *p);

/**
 * @fn int plateau_get_hauteur(Plateau* p)
 * @brief Obtient la hauteur du plateau
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne la hauteur du plateau
 * @return Hauteur du plateau (nombre de lignes)
 */
int plateau_get_hauteur(Plateau *p);

/**
 * @fn int plateau_get_nb_types_symboles(Plateau* p)
 * @brief Obtient le nombre de types de symboles différents
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne le nombre de types de symboles
 * @return Nombre de types de symboles
 */
int plateau_get_nb_types_symboles(Plateau *p);

/**
 * @fn int plateau_get_symboles_par_tour(Plateau* p)
 * @brief Obtient le nombre de nouveaux symboles par tour
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne le nombre de symboles par tour
 * @return Nombre de symboles par tour
 */
int plateau_get_symboles_par_tour(Plateau *p);

/**
 * @fn int plateau_get_difficulte(Plateau* p)
 * @brief Obtient le niveau de difficulté du jeu
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne le niveau de difficulté
 * @return Niveau de difficulté (0=facile, 1=moyen, 2=difficile)
 */
int plateau_get_difficulte(Plateau *p);

/**
 * @fn int plateau_get_nb_cases_remplies(Plateau* p)
 * @brief Obtient le nombre de cases occupées sur le plateau
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne le nombre de cases remplies
 * @return Nombre de cases remplies
 */
int plateau_get_nb_cases_remplies(Plateau *p);

/**
 * @fn int plateau_get_nb_suivantes(Plateau* p)
 * @brief Obtient le nombre de boules à venir (visibles à l'utilisateur)
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne le nombre de boules suivantes
 * @return Nombre de boules suivantes
 */
int plateau_get_nb_suivantes(Plateau *p);

/**
 * @fn Case* plateau_get_case(Plateau* p, int x, int y)
 * @brief Obtient une case spécifique du plateau
 * @param p Pointeur vers le plateau
 * @param x Coordonnée X de la case
 * @param y Coordonnée Y de la case
 * @pre p != NULL et 0 <= x < largeur et 0 <= y < hauteur
 * @post Retourne un pointeur vers la case demandée ou NULL si coordonnées invalides
 * @return Pointeur vers la case demandée ou NULL si coordonnées invalides
 */
Case *plateau_get_case(Plateau *p, int x, int y);

/**
 * @fn const char* plateau_get_score_nom(Plateau* p)
 * @brief Obtient le nom du joueur associé au score
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne le nom du joueur
 * @return Nom du joueur
 */
const char *plateau_get_score_nom(Plateau *p);

/**
 * @fn int plateau_get_score_valeur(Plateau* p)
 * @brief Obtient la valeur du score actuel
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne la valeur du score
 * @return Valeur du score
 */
int plateau_get_score_valeur(Plateau *p);

/**
 * @fn Couleur plateau_get_boule_suivante_couleur(Plateau* p, int index)
 * @brief Obtient la couleur d'une boule à venir
 * @param p Pointeur vers le plateau
 * @param index Index de la boule (0 à nb_suivantes-1)
 * @pre p != NULL et 0 <= index < nb_suivantes
 * @post Retourne la couleur de la boule suivante
 * @return Couleur de la boule suivante
 */
Couleur plateau_get_boule_suivante_couleur(Plateau *p, int index);

/**
 * @fn GtkWidget** plateau_get_boutons_suivants(Plateau* p)
 * @brief Obtient le tableau des boutons représentant les boules suivantes
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne le tableau de pointeurs vers les widgets de boutons
 * @return Tableau de pointeurs vers les widgets de boutons
 */
GtkWidget **plateau_get_boutons_suivants(Plateau *p);

/**
 * @fn GtkWidget* plateau_get_bouton_suivant(Plateau* p, int index)
 * @brief Obtient un bouton spécifique des boules suivantes
 * @param p Pointeur vers le plateau
 * @param index Index du bouton
 * @pre p != NULL et 0 <= index < nb_suivantes
 * @post Retourne un pointeur vers le widget du bouton
 * @return Pointeur vers le widget du bouton
 */
GtkWidget *plateau_get_bouton_suivant(Plateau *p, int index);

/**
 * @fn void plateau_set_largeur(Plateau* p, int largeur)
 * @brief Définit la largeur du plateau
 * @param p Pointeur vers le plateau
 * @param largeur Nouvelle largeur
 * @pre p != NULL et largeur > 0
 * @post La largeur du plateau est mise à jour
 */
void plateau_set_largeur(Plateau *p, int largeur);

/**
 * @fn void plateau_set_hauteur(Plateau* p, int hauteur)
 * @brief Définit la hauteur du plateau
 * @param p Pointeur vers le plateau
 * @param hauteur Nouvelle hauteur
 * @pre p != NULL et hauteur > 0
 * @post La hauteur du plateau est mise à jour
 */
void plateau_set_hauteur(Plateau *p, int hauteur);

/**
 * @fn void plateau_set_nb_types_symboles(Plateau* p, int nb_types)
 * @brief Définit le nombre de types de symboles
 * @param p Pointeur vers le plateau
 * @param nb_types Nouveau nombre de types
 * @pre p != NULL et nb_types > 0
 * @post Le nombre de types de symboles est mis à jour
 */
void plateau_set_nb_types_symboles(Plateau *p, int nb_types);

/**
 * @fn void plateau_set_symboles_par_tour(Plateau* p, int symboles)
 * @brief Définit le nombre de symboles par tour
 * @param p Pointeur vers le plateau
 * @param symboles Nouveau nombre de symboles par tour
 * @pre p != NULL et symboles > 0
 * @post Le nombre de symboles par tour est mis à jour
 */
void plateau_set_symboles_par_tour(Plateau *p, int symboles);

/**
 * @fn void plateau_set_difficulte(Plateau* p, int difficulte)
 * @brief Définit le niveau de difficulté
 * @param p Pointeur vers le plateau
 * @param difficulte Nouveau niveau de difficulté
 * @pre p != NULL et 0 <= difficulte <= 2
 * @post Le niveau de difficulté est mis à jour
 */
void plateau_set_difficulte(Plateau *p, int difficulte);

/**
 * @fn void plateau_set_nb_cases_remplies(Plateau* p, int nb)
 * @brief Définit le nombre de cases remplies
 * @param p Pointeur vers le plateau
 * @param nb Nouveau nombre de cases remplies
 * @pre p != NULL et 0 <= nb <= largeur*hauteur
 * @post Le nombre de cases remplies est mis à jour
 */
void plateau_set_nb_cases_remplies(Plateau *p, int nb);

/**
 * @fn void plateau_set_nb_suivantes(Plateau* p, int nb)
 * @brief Définit le nombre de boules suivantes
 * @param p Pointeur vers le plateau
 * @param nb Nouveau nombre de boules suivantes
 * @pre p != NULL et nb > 0
 * @post Le nombre de boules suivantes est mis à jour
 */
void plateau_set_nb_suivantes(Plateau *p, int nb);

/**
 * @fn void plateau_set_score_nom(Plateau* p, const char* nom)
 * @brief Définit le nom du joueur pour le score
 * @param p Pointeur vers le plateau
 * @param nom Nouveau nom
 * @pre p != NULL et nom != NULL
 * @post Le nom du joueur est mis à jour
 */
void plateau_set_score_nom(Plateau *p, const char *nom);

/**
 * @fn void plateau_set_score_valeur(Plateau* p, int valeur)
 * @brief Définit la valeur du score
 * @param p Pointeur vers le plateau
 * @param valeur Nouvelle valeur du score
 * @pre p != NULL
 * @post La valeur du score est mise à jour
 */
void plateau_set_score_valeur(Plateau *p, int valeur);

/**
 * @fn void plateau_set_boule_suivante_couleur(Plateau* p, int index, Couleur couleur)
 * @brief Définit la couleur d'une boule suivante
 * @param p Pointeur vers le plateau
 * @param index Index de la boule
 * @param couleur Nouvelle couleur
 * @pre p != NULL et 0 <= index < nb_suivantes
 * @post La couleur de la boule suivante est mise à jour
 */
void plateau_set_boule_suivante_couleur(Plateau *p, int index, Couleur couleur);

/**
 * @fn void plateau_set_boutons_suivants(Plateau* p, GtkWidget** boutons)
 * @brief Définit le tableau des boutons des boules suivantes
 * @param p Pointeur vers le plateau
 * @param boutons Nouveau tableau de boutons
 * @pre p != NULL
 * @post Le tableau des boutons des boules suivantes est mis à jour
 */
void plateau_set_boutons_suivants(Plateau *p, GtkWidget **boutons);

/**
 * @fn void plateau_set_bouton_suivant(Plateau* p, int index, GtkWidget* bouton)
 * @brief Définit un bouton spécifique des boules suivantes
 * @param p Pointeur vers le plateau
 * @param index Index du bouton
 * @param bouton Nouveau bouton
 * @pre p != NULL et 0 <= index < nb_suivantes
 * @post Le bouton de la boule suivante à l'index spécifié est mis à jour
 */
void plateau_set_bouton_suivant(Plateau *p, int index, GtkWidget *bouton);

/**
 * @fn bool case_est_occupe(Case* c)
 * @brief Vérifie si une case est occupée
 * @param c Pointeur vers la case
 * @pre c != NULL
 * @post Retourne l'état d'occupation de la case
 * @return true si la case est occupée, false sinon
 */
bool case_est_occupe(Case *c);

/**
 * @fn Couleur case_get_couleur(Case* c)
 * @brief Obtient la couleur d'une case
 * @param c Pointeur vers la case
 * @pre c != NULL
 * @post Retourne la couleur de la case
 * @return Couleur de la case
 */
Couleur case_get_couleur(Case *c);

/**
 * @fn GtkWidget* case_get_image(Case* c)
 * @brief Obtient le widget d'image associé à une case
 * @param c Pointeur vers la case
 * @pre c != NULL
 * @post Retourne le widget d'image de la case
 * @return Pointeur vers le widget d'image
 */
GtkWidget *case_get_image(Case *c);

/**
 * @fn void case_set_occupe(Case* c, bool occupe)
 * @brief Définit l'état d'occupation d'une case
 * @param c Pointeur vers la case
 * @param occupe Nouvel état d'occupation
 * @pre c != NULL
 * @post L'état d'occupation de la case est mis à jour
 */
void case_set_occupe(Case *c, bool occupe);

/**
 * @fn void case_set_couleur(Case* c, Couleur couleur)
 * @brief Définit la couleur d'une case
 * @param c Pointeur vers la case
 * @param couleur Nouvelle couleur
 * @pre c != NULL
 * @post La couleur de la case est mise à jour
 */
void case_set_couleur(Case *c, Couleur couleur);

/**
 * @fn void case_set_image(Case* c, GtkWidget* image)
 * @brief Définit le widget d'image associé à une case
 * @param c Pointeur vers la case
 * @param image Nouveau widget d'image
 * @pre c != NULL
 * @post Le widget d'image de la case est mis à jour
 */
void case_set_image(Case *c, GtkWidget *image);

/**
 * @fn Score* score_create(const char* nom, int valeur)
 * @brief Crée un nouveau score
 * @param nom Nom du joueur
 * @param valeur Valeur du score
 * @pre nom != NULL
 * @post Un nouveau score est créé ou NULL en cas d'erreur
 * @return Pointeur vers le nouveau score ou NULL en cas d'erreur
 */
Score *score_create(const char *nom, int valeur);

/**
 * @fn void score_destroy(Score* s)
 * @brief Libère la mémoire allouée pour un score
 * @param s Pointeur vers le score à détruire
 * @pre s peut être NULL (fonction sans effet dans ce cas)
 * @post La mémoire allouée pour le score est libérée
 */
void score_destroy(Score *s);

/**
 * @fn const char* score_get_nom(Score* s)
 * @brief Obtient le nom associé à un score
 * @param s Pointeur vers le score
 * @pre s != NULL
 * @post Retourne le nom du joueur
 * @return Nom du joueur
 */
const char *score_get_nom(Score *s);

/**
 * @fn int score_get_valeur(Score* s)
 * @brief Obtient la valeur d'un score
 * @param s Pointeur vers le score
 * @pre s != NULL
 * @post Retourne la valeur du score
 * @return Valeur du score
 */
int score_get_valeur(Score *s);

/**
 * @fn void initialiser_plateau(Plateau* plateau)
 * @brief Initialise les valeurs par défaut d'un plateau de jeu
 * @param plateau Le plateau à initialiser
 * @pre plateau != NULL
 * @post Toutes les propriétés du plateau sont initialisées avec des valeurs par défaut
 */
void initialiser_plateau(Plateau *plateau);

/**
 * @fn Plateau* creer_plateau(GtkWidget *fenetre, int largeur, int hauteur, int nb_types, int symboles_par_tour, int difficulte)
 * @brief Crée un nouveau plateau de jeu
 * @param fenetre Fenêtre principale du jeu
 * @param largeur Largeur du plateau
 * @param hauteur Hauteur du plateau
 * @param nb_types Nombre de types de symboles
 * @param symboles_par_tour Nombre de symboles par tour
 * @param difficulte Niveau de difficulté
 * @pre fenetre != NULL, largeur > 0, hauteur > 0, nb_types > 0, symboles_par_tour > 0, 0 <= difficulte <= 2
 * @post Un nouveau plateau est créé et initialisé ou NULL en cas d'erreur
 * @return Pointeur vers le nouveau plateau ou NULL en cas d'erreur
 */
Plateau *creer_plateau(GtkWidget *fenetre, int largeur, int hauteur, int nb_types, int symboles_par_tour, int difficulte);

/**
 * @fn void detruire_plateau(Plateau* plateau)
 * @brief Libère la mémoire allouée pour un plateau
 * @param plateau Pointeur vers le plateau à détruire
 * @pre plateau peut être NULL (fonction sans effet dans ce cas)
 * @post La mémoire allouée pour le plateau est libérée
 */
void detruire_plateau(Plateau *plateau);

/**
 * @fn void charger_scores(const char *fichier, Score** scores, int *nb_scores)
 * @brief Charge les scores depuis un fichier
 * @param fichier Chemin du fichier de scores
 * @param scores Tableau de pointeurs vers les scores (sortie)
 * @param nb_scores Nombre de scores chargés (sortie)
 * @pre fichier != NULL, scores != NULL, nb_scores != NULL
 * @post Les scores sont chargés dans le tableau et nb_scores contient leur nombre
 */
void charger_scores(const char *fichier, Score **scores, int *nb_scores);

/**
 * @fn void sauvegarder_score(const char *fichier, const char *nom, int nouveau_score)
 * @brief Sauvegarde un nouveau score dans le fichier
 * @param fichier Chemin du fichier de scores
 * @param nom Nom du joueur
 * @param nouveau_score Valeur du score
 * @pre fichier != NULL, nom != NULL
 * @post Le score est ajouté au fichier si suffisamment élevé
 */
void sauvegarder_score(const char *fichier, const char *nom, int nouveau_score);

/**
 * @fn bool verifier_lignes(Plateau *p)
 * @brief Vérifie s'il existe des alignements sur le plateau
 * @param p Pointeur vers le plateau
 * @pre p != NULL
 * @post Retourne true si des alignements sont trouvés et les traite
 * @return true si des alignements ont été trouvés, false sinon
 * @details Vérifie les alignements horizontaux, verticaux et diagonaux d'au moins 5 boules
 */
bool verifier_lignes(Plateau *p);

#endif // MODELE_H
