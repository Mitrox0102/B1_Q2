/**
 * @file tresor.h
 *
 * @brief Ce fichier contient les déclarations des fonctions et des structures
 *       nécessaires pour le jeu de trésor.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 31/03/2025
 * @projet: INFO0030 Projet 3
 */


#ifndef TRESOR_H
#define TRESOR_H

#include <gtk/gtk.h>

// Type opaque
/**
 * @brief Structure contenant les données du jeu.
 */
typedef struct donnees_jeu_t donnees_jeu;

// Fonctions de base
/**
 * @brief Créer et initialise les données du jeu.
 * 
 * @pre Aucune.
 * @post Les données du jeu sont allouées dynamiquement et initialisées.
 * 
 * @return Un pointeur vers la structure `donnees_jeu` initialisée.
 *         Retourne `NULL` en cas d'erreur d'allocation mémoire.
 */
donnees_jeu* creer_donnees_jeu(void);

/**
 * @brief Créer la fenêtre principale de l'application.
 * 
 * @pre GTK doit être initialisé avec `gtk_init`.
 * @post Une fenêtre GTK est créée avec les propriétés définies.
 * 
 * @return Un pointeur vers la fenêtre GTK créée.
 */
GtkWidget *creer_fenetre(void);

/**
 * @brief Créer un label pour afficher les victoires et défaites.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Un label GTK est créé et initialisé avec les victoires et défaites.
 * 
 * @return Un pointeur vers le label GTK créé.
 */
GtkWidget *creer_v_d(donnees_jeu *donnees);

/**
 * @brief Créer un label pour afficher l'état de la partie.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Un label GTK est créé et initialisé avec l'état de la partie.
 * 
 * @return Un pointeur vers le label GTK créé.
 */
GtkWidget *creer_etat_partie(donnees_jeu *donnees);

/**
 * @brief Libère la mémoire allouée pour les données du jeu.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide ou `NULL`.
 * @post La mémoire allouée pour `donnees` est libérée.
 */
void detruire_donnees_jeu(donnees_jeu *donnees);

/**
 * @brief Crée le bouton "Recommencer" et l'ajoute à la fenêtre.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param pFenetre Un pointeur vers la fenêtre GTK principale.
 * 
 * @pre `donnees` et `pFenetre` doivent être des pointeurs valides.
 * @post Un bouton GTK est créé, configuré et enregistré dans `donnees`.
 */
void creer_recommencer(donnees_jeu *donnees, GtkWidget *pFenetre);

/**
 * @brief Crée les boutons représentant les coffres et les initialise.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Trois boutons GTK sont créés, configurés et enregistrés dans `donnees`.
 */
void creer_bouton(donnees_jeu *donnees);

// Getters

/**
 * @brief Récupère le nombre de victoires.
 * 
 * @param donnees Un pointeur constant vers la structure contenant
 *  les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Aucune.
 * 
 * @return Le nombre de victoires. Retourne -1 si `donnees` est NULL.
 */
int get_victoires(const donnees_jeu *donnees);

/**
 * @brief Récupère le nombre de défaites.
 * 
 * @param donnees Un pointeur constant vers la structure contenant
 *  les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Aucune.
 * 
 * @return Le nombre de défaites. Retourne -1 si `donnees` est NULL.
 */
int get_defaites(const donnees_jeu *donnees);

/**
 * @brief Récupère l'indice du coffre contenant le trésor.
 * 
 * @param donnees Un pointeur constant vers la structure contenant
 *  les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Aucune.
 * 
 * @return L'indice du coffre contenant le trésor. Retourne -1 si
 *  `donnees` est NULL.
 */
int get_tresor_bon(const donnees_jeu *donnees);

/**
 * @brief Récupère l'état de la partie.
 * 
 * @param donnees Un pointeur constant vers la structure contenant les
 *  données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Aucune.
 * 
 * @return `TRUE` si la partie est en cours, `FALSE` sinon. Retourne
 *  `FALSE` si `donnees` est NULL.
 */
gboolean get_etat_partie(const donnees_jeu *donnees);

/**
 * @brief Récupère un bouton spécifique.
 * 
 * @param donnees Un pointeur constant vers la structure contenant les
 *  données du jeu.
 * @param index L'indice du bouton (0, 1 ou 2).
 * 
 * @pre `donnees` doit être un pointeur valide. `index` doit être compris
 *  entre 0 et 2 inclus.
 * @post Aucune.
 * 
 * @return Un pointeur vers le bouton GTK correspondant. Retourne `NULL`
 *  si `donnees` est NULL ou si `index` est invalide.
 */
GtkWidget* get_bouton(const donnees_jeu *donnees, int index);

/**
 * @brief Récupère le bouton "Recommencer".
 * 
 * @param donnees Un pointeur constant vers la structure contenant les
 *  données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Aucune.
 * 
 * @return Un pointeur vers le bouton "Recommencer". Retourne `NULL` si
 *  `donnees` est NULL.
 */
GtkWidget* get_recommencer(const donnees_jeu *donnees);

/**
 * @brief Vérifie si un coffre est ouvert.
 * 
 * @param donnees Un pointeur constant vers la structure contenant les 
 * données du jeu.
 * @param index L'indice du coffre (0, 1 ou 2).
 * 
 * @pre `donnees` doit être un pointeur valide. `index` doit être compris entre
 *  0 et 2 inclus.
 * @post Aucune.
 * 
 * @return `TRUE` si le coffre est ouvert, `FALSE` sinon. Retourne `FALSE` si
 *  `donnees` est NULL ou si `index` est invalide.
 */
gboolean get_coffre_ouvert(const donnees_jeu *donnees, int index);

/**
 * @brief Récupère le label affichant les victoires et défaites.
 * 
 * @param donnees Un pointeur constant vers la structure contenant les données
 *  du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Aucune.
 * 
 * @return Un pointeur vers le label GTK correspondant. Retourne `NULL` si
 *  `donnees` est NULL.
 */
GtkWidget* get_label_score(const donnees_jeu *donnees);

/**
 * @brief Récupère le label affichant l'état de la partie.
 * 
 * @param donnees Un pointeur constant vers la structure contenant les données
 *  du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Aucune.
 * 
 * @return Un pointeur vers le label GTK correspondant. Retourne `NULL` si
 *  `donnees` est NULL.
 */
GtkWidget* get_label_etat_partie(const donnees_jeu *donnees);

// Setters

/**
 * @brief Définit le nombre de victoires.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param victoires Le nombre de victoires à définir.
 * 
 * @pre `donnees` doit être un pointeur valide. `victoires` doit être >= 0.
 * @post Le nombre de victoires est mis à jour dans `donnees`.
 */
void set_victoires(donnees_jeu *donnees, int victoires);

/**
 * @brief Définit le nombre de défaites.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param defaites Le nombre de défaites à définir.
 * 
 * @pre `donnees` doit être un pointeur valide. `defaites` doit être >= 0.
 * @post Le nombre de défaites est mis à jour dans `donnees`.
 */
void set_defaites(donnees_jeu *donnees, int defaites);

/**
 * @brief Définit l'indice du coffre contenant le trésor.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param tresor_bon L'indice du coffre contenant le trésor (0, 1 ou 2).
 * 
 * @pre `donnees` doit être un pointeur valide. `tresor_bon` doit être compris
 *  entre 0 et 2 inclus.
 * @post L'indice du coffre contenant le trésor est mis à jour dans `donnees`.
 */
void set_tresor_bon(donnees_jeu *donnees, int tresor_bon);

/**
 * @brief Définit l'état de la partie.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param etat L'état de la partie (`TRUE` pour en cours, `FALSE` pour terminée).
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post L'état de la partie est mis à jour dans `donnees`.
 */
void set_etat_partie(donnees_jeu *donnees, gboolean etat);

/**
 * @brief Définit un bouton spécifique.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param index L'indice du bouton (0, 1 ou 2).
 * @param bouton Un pointeur vers le bouton GTK à définir.
 * 
 * @pre `donnees` doit être un pointeur valide. `index` doit être compris entre
 *  0 et 2 inclus. `bouton` doit être un pointeur valide.
 * @post Le bouton est enregistré dans `donnees` à l'indice spécifié.
 */
void set_bouton(donnees_jeu *donnees, int index, GtkWidget *bouton);

/**
 * @brief Définit le bouton "Recommencer".
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param recommencer Un pointeur vers le bouton GTK "Recommencer".
 * 
 * @pre `donnees` et `recommencer` doivent être des pointeurs valides.
 * @post Le bouton "Recommencer" est enregistré dans `donnees`.
 */
void set_recommencer(donnees_jeu *donnees, GtkWidget *recommencer);

/**
 * @brief Définit l'état d'un coffre (ouvert ou fermé).
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param index L'indice du coffre (0, 1 ou 2).
 * @param etat L'état du coffre (`TRUE` pour ouvert, `FALSE` pour fermé).
 * 
 * @pre `donnees` doit être un pointeur valide. `index` doit être compris entre
 *  0 et 2 inclus.
 * @post L'état du coffre est mis à jour dans `donnees`.
 */
void set_coffre_ouvert(donnees_jeu *donnees, int index, gboolean etat);

/**
 * @brief Définit le label affichant les victoires et défaites.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param label Un pointeur vers le label GTK à définir.
 * 
 * @pre `donnees` et `label` doivent être des pointeurs valides.
 * @post Le label est enregistré dans `donnees`.
 */
void set_label_score(donnees_jeu *donnees, GtkWidget *label);

/**
 * @brief Définit le label affichant l'état de la partie.
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * @param label Un pointeur vers le label GTK à définir.
 * 
 * @pre `donnees` et `label` doivent être des pointeurs valides.
 * @post Le label est enregistré dans `donnees`.
 */
void set_label_etat_partie(donnees_jeu *donnees, GtkWidget *label);

// Gestionnaires d'événements

/**
 * @brief Gère le clic sur un coffre.
 * 
 * @param widget Un pointeur vers le bouton GTK qui a été cliqué.
 * @param data Un pointeur vers les données du jeu (de type `donnees_jeu`).
 * 
 * @pre `widget` et `data` doivent être des pointeurs valides.
 * @post Met à jour l'état du jeu en fonction du coffre cliqué.
 */
void gerer_clic_coffre(GtkWidget *widget, gpointer data);

/**
 * @brief Réinitialise la partie lorsque le bouton "Recommencer" est cliqué.
 * 
 * @param widget Un pointeur vers le bouton GTK "Recommencer".
 * @param data Un pointeur vers les données du jeu (de type `donnees_jeu`).
 * 
 * @pre `widget` et `data` doivent être des pointeurs valides.
 * @post Réinitialise les données du jeu et met à jour l'interface utilisateur.
 */
void recommencer_partie(GtkWidget *widget, gpointer data);

/**
 * @brief Gère l'état de la partie (en cours ou terminée).
 * 
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * 
 * @pre `donnees` doit être un pointeur valide.
 * @post Met à jour l'état des widgets en fonction de l'état de la partie.
 */
void gerer_etat_partie(donnees_jeu *donnees);

// Fonctions auxiliaires

/**
 * @brief Charge une image et l'associe à un bouton GTK.
 * 
 * @param chemin_image Le chemin vers le fichier image à charger.
 * 
 * @pre `chemin_image` doit être un pointeur valide vers une chaîne de caractères.
 * @post Crée un bouton GTK avec l'image spécifiée.
 * 
 * @return Un pointeur vers le bouton GTK créé. Retourne `NULL` en cas d'erreur.
 */
GtkWidget *charge_image_bouton(const char *chemin_image);

/**
 * @brief Charge une nouvelle image dans un bouton existant.
 * 
 * @param bouton Un pointeur vers le bouton GTK où l'image sera chargée.
 * @param chemin_image Le chemin vers le fichier image à charger.
 * 
 * @pre `bouton` et `chemin_image` doivent être des pointeurs valides.
 * @post Met à jour l'image affichée dans le bouton spécifié.
 */
void charger_nouvelle_image(GtkWidget *bouton, const char *chemin_image);

/**
 * @brief Met à jour le label affichant les victoires et défaites.
 * 
 * @param label Un pointeur vers le label GTK à mettre à jour.
 * @param donnees Un pointeur vers la structure contenant les données du jeu.
 * 
 * @pre `label` et `donnees` doivent être des pointeurs valides.
 * @post Met à jour le texte du label avec les victoires et défaites actuelles.
 */
void maj_v_d(GtkWidget *label, donnees_jeu *donnees);


#endif // TRESOR_H