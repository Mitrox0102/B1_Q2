#ifndef TRESOR_H
#define TRESOR_H

#include <gtk/gtk.h>

// Type opaque
typedef struct donnees_jeu_t donnees_jeu;

// Fonctions de base
donnees_jeu* creer_donnees_jeu(void);
GtkWidget *creer_fenetre(void);
void detruire_donnees_jeu(donnees_jeu *donnees);

// Getters
int get_victoires(const donnees_jeu *donnees);
int get_defaites(const donnees_jeu *donnees);
int get_tresor_bon(const donnees_jeu *donnees);
gboolean get_etat_partie(const donnees_jeu *donnees);
GtkWidget* get_bouton(const donnees_jeu *donnees, int index);
GtkWidget* get_recommencer(const donnees_jeu *donnees);
gboolean get_coffre_ouvert(const donnees_jeu *donnees, int index);
GtkWidget* get_label_score(const donnees_jeu *donnees);
GtkWidget* get_label_etat_partie(const donnees_jeu *donnees);

// Setters
void set_victoires(donnees_jeu *donnees, int victoires);
void set_defaites(donnees_jeu *donnees, int defaites);
void set_tresor_bon(donnees_jeu *donnees, int tresor_bon);
void set_etat_partie(donnees_jeu *donnees, gboolean etat);
void set_bouton(donnees_jeu *donnees, int index, GtkWidget *bouton);
void set_recommencer(donnees_jeu *donnees, GtkWidget *recommencer);
void set_coffre_ouvert(donnees_jeu *donnees, int index, gboolean etat);
void set_label_score(donnees_jeu *donnees, GtkWidget *label);
void set_label_etat_partie(donnees_jeu *donnees, GtkWidget *label);

// Gestionnaires d'événements
void gerer_clic_coffre(GtkWidget *widget, gpointer data);
void recommencer_partie(GtkWidget *widget, gpointer data);
void gerer_etat_partie(donnees_jeu *donnees);

// Fonctions auxiliaires
GtkWidget *charge_image_bouton(const char *chemin_image);
void charger_nouvelle_image(GtkWidget *bouton, const char *chemin_image);
void maj_v_d(GtkWidget *label, donnees_jeu *donnees);


#endif // TRESOR_H