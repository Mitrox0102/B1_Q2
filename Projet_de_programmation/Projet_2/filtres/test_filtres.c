/**
 * @file test_filtres.c
 *
 * @brief Ce fichier contient les définitions de types et
 * les fonctions de test de filtres d'images PNM.
 *
 * @author: Ouazouz Sami S2404629
 * @date: 23/03/2025
 * @projet: INFO0030 Projet 2
 */


#include <stdio.h>
#include <stdlib.h>
#include <pnm.h>
#include "seatest.h"
#include "filtres.h"

void setup(void);
void td(void);
void test_fixture_filtres(void);
void all_tests(void);

//Fichier de test pour tous les tests
static PNM *test = NULL;

//On initialise notre image avant chaque test
void setup(void){
   test = NULL;
}

//On réinitialise notre image après chaque test
void td(void){
   if(test){
      detruire_pnm(test);
      test = NULL;
   }
}

//Test du filtre retournement pour des PNM au format PBM
static void test_filtre_retournement_type_0(){
   //Création d'une image au format PBM en 2x2
   test = creer_pnm(0, 2, 2, 1);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels
   set_pixel(test, 0, 0);
   set_pixel(test, 1, 1);
   set_pixel(test, 2, 1);
   set_pixel(test, 3, 0);

   //Application du filtre
   filtre_retournement(&test);
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(0,get_pixel(test, 0));
   assert_int_equal(1, get_pixel(test, 1));
   assert_int_equal(1,get_pixel(test, 2));
   assert_int_equal(0, get_pixel(test, 3));
}

//Test du filtre retournement pour des PNM au format PGM
static void test_filtre_retournement_type_1(){
   //Création d'une image au format PGM en 2x2
   test = creer_pnm(1, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels
   set_pixel(test, 0, 0);
   set_pixel(test, 1, 64);
   set_pixel(test, 2, 128);
   set_pixel(test, 3, 200);

   //Application du filtre
   filtre_retournement(&test);
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(200,get_pixel(test, 0));
   assert_int_equal(128, get_pixel(test, 1));
   assert_int_equal(64,get_pixel(test, 2));
   assert_int_equal(0, get_pixel(test, 3));
}

//Test du filtre retournement pour des PNM au format PPM
static void test_filtre_retournement_type_2(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels;
   //Pixel orange
   set_pixel(test, 0, 255);
   set_pixel(test, 1, 128);
   set_pixel(test, 2, 0);

   //pixel rose
   set_pixel(test, 3, 255);
   set_pixel(test, 4, 60);
   set_pixel(test, 5, 255);
   
   //Pixel cyan
   set_pixel(test, 6, 60);
   set_pixel(test, 7, 255);
   set_pixel(test, 8, 255);

   //1 pixel blanc
   set_pixel(test, 9, 255);
   set_pixel(test, 10, 255);
   set_pixel(test, 11, 255);

   //Application du filtre
   filtre_retournement(&test);
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   // Pixel blanc
   assert_int_equal(255, get_pixel(test, 0));
   assert_int_equal(255, get_pixel(test, 1));
   assert_int_equal(255, get_pixel(test, 2));

   // Pixel cyan
   assert_int_equal(60, get_pixel(test, 3));
   assert_int_equal(255, get_pixel(test, 4));
   assert_int_equal(255, get_pixel(test, 5));

   // Pixel rose
   assert_int_equal(255, get_pixel(test, 6));
   assert_int_equal(60, get_pixel(test, 7));
   assert_int_equal(255, get_pixel(test, 8));

   // Pixel orange
   assert_int_equal(255, get_pixel(test, 9));
   assert_int_equal(128, get_pixel(test, 10));
   assert_int_equal(0, get_pixel(test, 11));
}

//Test du filtre gris pour des PNM avec la méthode 1
static void test_filtre_gris_methode_1(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels
   set_pixel(test, 0, 255);   //1er pixel rouge
   set_pixel(test, 1, 0);
   set_pixel(test, 2, 0);

   set_pixel(test, 3, 0);     //2eme pixel vert
   set_pixel(test, 4, 255);
   set_pixel(test, 5, 0);

   set_pixel(test, 6, 0);     //3eme pixel bleu
   set_pixel(test, 7, 0);
   set_pixel(test, 8, 255);

   set_pixel(test, 9, 128);   //4eme pixel gris
   set_pixel(test, 10, 128);
   set_pixel(test, 11, 128);

   //Application du filtre
   filtre_gris(&test, '1');
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(85, get_pixel(test, 0));
   assert_int_equal(85, get_pixel(test, 1));
   assert_int_equal(85, get_pixel(test, 2));
   assert_int_equal(128, get_pixel(test, 3));
}

//Test du filtre gris pour des PNM avec la méthode 2
static void test_filtre_gris_methode_2(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels
   set_pixel(test, 0, 255);   //1er pixel rouge
   set_pixel(test, 1, 0);
   set_pixel(test, 2, 0);

   set_pixel(test, 3, 0);     //2eme pixel vert
   set_pixel(test, 4, 255);
   set_pixel(test, 5, 0);

   set_pixel(test, 6, 0);     //3eme pixel bleu
   set_pixel(test, 7, 0);
   set_pixel(test, 8, 255);

   set_pixel(test, 9, 128);   //4eme pixel gris
   set_pixel(test, 10, 128);
   set_pixel(test, 11, 128);

   //Application du filtre
   filtre_gris(&test, '2');
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(76, get_pixel(test, 0));
   assert_int_equal(150, get_pixel(test, 1));
   assert_int_equal(29, get_pixel(test, 2));
   assert_int_equal(128, get_pixel(test, 3));
}

//Test du filtre négatif pour des PNM
static void test_filtre_négatif(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels;
   //Pixel orange
   set_pixel(test, 0, 255);
   set_pixel(test, 1, 128);
   set_pixel(test, 2, 0);

   //pixel rose
   set_pixel(test, 3, 255);
   set_pixel(test, 4, 60);
   set_pixel(test, 5, 255);

   //Pixel cyan
   set_pixel(test, 6, 60);
   set_pixel(test, 7, 255);
   set_pixel(test, 8, 255);

   //pixel gris
   set_pixel(test, 9, 128);
   set_pixel(test, 10, 128);
   set_pixel(test, 11, 128);

   //Application du filtre
   filtre_negatif(&test);
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(0,get_pixel(test, 0));
   assert_int_equal(127,get_pixel(test, 1));
   assert_int_equal(255,get_pixel(test, 2));

   assert_int_equal(0,get_pixel(test, 3));
   assert_int_equal(195,get_pixel(test, 4));
   assert_int_equal(0,get_pixel(test, 5));

   assert_int_equal(195,get_pixel(test, 6));
   assert_int_equal(0,get_pixel(test, 7));
   assert_int_equal(0,get_pixel(test, 8));

   assert_int_equal(127, get_pixel(test, 9));
   assert_int_equal(127, get_pixel(test, 10));
   assert_int_equal(127, get_pixel(test, 11));
}

//Test du filtre monochrome rouge pour des PNM
static void test_filtre_monochrome_r(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels;
   //Pixel orange
   set_pixel(test, 0, 255);
   set_pixel(test, 1, 128);
   set_pixel(test, 2, 0);

   //pixel rose
   set_pixel(test, 3, 255);
   set_pixel(test, 4, 60);
   set_pixel(test, 5, 255);

   //Pixel cyan
   set_pixel(test, 6, 60);
   set_pixel(test, 7, 255);
   set_pixel(test, 8, 255);

   //pixel gris
   set_pixel(test, 9, 128);
   set_pixel(test, 10, 128);
   set_pixel(test, 11, 128);

   //Application du filtre
   filtre_monochrome(&test, 'r');
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(255,get_pixel(test, 0));
   assert_int_equal(0,get_pixel(test, 1));
   assert_int_equal(0,get_pixel(test, 2));

   assert_int_equal(255,get_pixel(test, 3));
   assert_int_equal(0,get_pixel(test, 4));
   assert_int_equal(0,get_pixel(test, 5));

   assert_int_equal(60,get_pixel(test, 6));
   assert_int_equal(0,get_pixel(test, 7));
   assert_int_equal(0,get_pixel(test, 8));

   assert_int_equal(128, get_pixel(test, 9));
   assert_int_equal(0, get_pixel(test, 10));
   assert_int_equal(0, get_pixel(test, 11));
}

//Test du filtre monochrome vert pour des PNM
static void test_filtre_monochrome_v(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels;
   //Pixel orange
   set_pixel(test, 0, 255);
   set_pixel(test, 1, 128);
   set_pixel(test, 2, 0);

   //pixel rose
   set_pixel(test, 3, 255);
   set_pixel(test, 4, 60);
   set_pixel(test, 5, 255);

   //Pixel cyan
   set_pixel(test, 6, 60);
   set_pixel(test, 7, 255);
   set_pixel(test, 8, 255);

   //pixel gris
   set_pixel(test, 9, 128);
   set_pixel(test, 10, 128);
   set_pixel(test, 11, 128);

   //Application du filtre
   filtre_monochrome(&test, 'v');
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(0,get_pixel(test, 0));
   assert_int_equal(128,get_pixel(test, 1));
   assert_int_equal(0,get_pixel(test, 2));

   assert_int_equal(0,get_pixel(test, 3));
   assert_int_equal(60,get_pixel(test, 4));
   assert_int_equal(0,get_pixel(test, 5));

   assert_int_equal(0,get_pixel(test, 6));
   assert_int_equal(255,get_pixel(test, 7));
   assert_int_equal(0,get_pixel(test, 8));

   assert_int_equal(0, get_pixel(test, 9));
   assert_int_equal(128, get_pixel(test, 10));
   assert_int_equal(0, get_pixel(test, 11));
}

//Test du filtre monochrome bleu pour des PNM
static void test_filtre_monochrome_b(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels;
   //Pixel orange
   set_pixel(test, 0, 255);
   set_pixel(test, 1, 128);
   set_pixel(test, 2, 0);

   //pixel rose
   set_pixel(test, 3, 255);
   set_pixel(test, 4, 60);
   set_pixel(test, 5, 255);

   //Pixel cyan
   set_pixel(test, 6, 60);
   set_pixel(test, 7, 255);
   set_pixel(test, 8, 255);

   //pixel gris
   set_pixel(test, 9, 128);
   set_pixel(test, 10, 128);
   set_pixel(test, 11, 128);

   //Application du filtre
   filtre_monochrome(&test, 'b');
   assert_true(test != NULL);

   //Vérification des valeurs en sortie
   assert_int_equal(0,get_pixel(test, 0));
   assert_int_equal(0,get_pixel(test, 1));
   assert_int_equal(0,get_pixel(test, 2));

   assert_int_equal(0,get_pixel(test, 3));
   assert_int_equal(0,get_pixel(test, 4));
   assert_int_equal(255,get_pixel(test, 5));

   assert_int_equal(0,get_pixel(test, 6));
   assert_int_equal(0,get_pixel(test, 7));
   assert_int_equal(255,get_pixel(test, 8));

   assert_int_equal(0, get_pixel(test, 9));
   assert_int_equal(0, get_pixel(test, 10));
   assert_int_equal(128, get_pixel(test, 11));
}

//Test du filtre Noir et blanc pour des PNM au format PGM (Méthode 1)
static void test_filtre_nb_PGM(){
   //Création d'une image au format PGM en 2x2
   test = creer_pnm(1, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels

   set_pixel(test, 0, 255);
   set_pixel(test, 1, 115);
   set_pixel(test, 2, 0);
   set_pixel(test, 3, 64);


   //Application du filtre
   filtre_nb(&test, 115);
   assert_true(test != NULL);

   //Vérification des valeurs en sortie

   assert_int_equal(0,get_pixel(test, 0));
   assert_int_equal(0,get_pixel(test, 1));
   assert_int_equal(1,get_pixel(test, 2));
   assert_int_equal(1,get_pixel(test, 3));
}

//Test du filtre Noir et blanc pour des PNM au format PPM (Méthode 1)
static void test_filtre_nb_PPM(){
   //Création d'une image au format PPM en 2x2
   test = creer_pnm(2, 2, 2, 255);
   if(!test){
      fprintf(stderr,"Image invalide\n");
      return;
   }

   //Initialisation des pixels

   set_pixel(test, 0, 255);
   set_pixel(test, 1, 115);
   set_pixel(test, 2, 0);

   set_pixel(test, 3, 64);
   set_pixel(test, 4, 30);
   set_pixel(test, 5, 2);

   set_pixel(test, 6, 115);
   set_pixel(test, 7, 115);
   set_pixel(test, 8, 115);

   set_pixel(test, 9, 15);
   set_pixel(test, 10, 203);
   set_pixel(test, 11, 0);


   //Application du filtre
   filtre_nb(&test, 115);
   assert_true(test != NULL);

   //Vérification des valeurs en sortie

   assert_int_equal(0,get_pixel(test, 0));
   assert_int_equal(1,get_pixel(test, 1));
   assert_int_equal(0,get_pixel(test, 2));
   assert_int_equal(0,get_pixel(test, 3));
}

static void test_load_PGM(){
   //Test de chargement d'une image PGM
   PNM *image = NULL;
   
   //Test avec un fichier inexistant
   assert_int_equal(-2, load_pnm(&image, "miaou.pgm"));
   assert_true(image == NULL);

   //Test avec un fichier PGM valide
   assert_int_equal(0, load_pnm(&image, "./test_1.pgm"));
   assert_true(image != NULL);
   
   //Vérification du type
   assert_int_equal(1, get_type(image));
   
   //Vérification des dimensions
   assert_int_equal(2, get_largeur(image));
   assert_int_equal(2, get_longueur(image));

   //Vérifiaction de la valeur max
   assert_int_equal(255, get_valeurMax(image));
   
   //Vérification des valeurs en sortie
   assert_int_equal(255, get_pixel(image, 0));
   assert_int_equal(32, get_pixel(image, 1));
   assert_int_equal(159, get_pixel(image, 2));
   assert_int_equal(2, get_pixel(image, 3));
}

static void test_load_PPM(){
   //Test de chargement d'une image PPM
   PNM *image = NULL;
   
   //Test avec un fichier inexistant
   assert_int_equal(-2, load_pnm(&image, "miaou.ppm"));
   assert_true(image == NULL);

   //Test avec un fichier PGM valide
   assert_int_equal(0, load_pnm(&image, "./test_2.ppm"));
   assert_true(image != NULL);
   
   //Vérification du type
   assert_int_equal(2, get_type(image));
   
   //Vérification des dimensions
   assert_int_equal(2, get_largeur(image));
   assert_int_equal(2, get_longueur(image));

   //Vérifiaction de la valeur max
   assert_int_equal(255, get_valeurMax(image));
   
   //Vérification des valeurs en sortie
   assert_int_equal(255, get_pixel(image, 0));
   assert_int_equal(29, get_pixel(image, 1));
   assert_int_equal(34, get_pixel(image, 2));

   assert_int_equal(1, get_pixel(image, 3));
   assert_int_equal(255, get_pixel(image, 4));
   assert_int_equal(40, get_pixel(image, 5));

   assert_int_equal(0, get_pixel(image, 6));
   assert_int_equal(34, get_pixel(image, 7));
   assert_int_equal(255, get_pixel(image, 8));

   assert_int_equal(0, get_pixel(image, 9));
   assert_int_equal(0, get_pixel(image, 10));
   assert_int_equal(0, get_pixel(image, 11));
}

static void test_write_PGM(){
   // Création d'une image PGM test
   test = creer_pnm(P2, 2, 2, 255);
   assert_true(test != NULL);
   
   // Initialisation avec des valeurs de test
   set_pixel(test, 0, 0);
   set_pixel(test, 1, 85);
   set_pixel(test, 2, 170);
   set_pixel(test, 3, 255);
   
   // Test d'écriture
   assert_int_equal(0, write_pnm(test, "test_output.pgm"));
   
   // Vérification que le fichier existe
   FILE *f = fopen("test_output.pgm", "r");
   assert_true(f != NULL);
   fclose(f);
   
   // Rechargement et vérification
   PNM *image_lue = NULL;
   assert_int_equal(0, load_pnm(&image_lue, "test_output.pgm"));
   assert_true(image_lue != NULL);
   
   // Vérification des pixels
   assert_int_equal(0, get_pixel(image_lue, 0));
   assert_int_equal(85, get_pixel(image_lue, 1));
   assert_int_equal(170, get_pixel(image_lue, 2));
   assert_int_equal(255, get_pixel(image_lue, 3));
   
   // Nettoyage
   detruire_pnm(image_lue);
   remove("test_output.pgm");
}

static void test_write_PPM(){
   // Création d'une image PPM test
   test = creer_pnm(P3, 2, 2, 255);
   assert_true(test != NULL);
   
   // Initialisation avec des couleurs de test
   // Rouge
   set_pixel(test, 0, 255);
   set_pixel(test, 1, 0);
   set_pixel(test, 2, 0);
   
   // Vert
   set_pixel(test, 3, 0);
   set_pixel(test, 4, 255);
   set_pixel(test, 5, 0);
   
   // Bleu
   set_pixel(test, 6, 0);
   set_pixel(test, 7, 0);
   set_pixel(test, 8, 255);
   
   // Blanc
   set_pixel(test, 9, 255);
   set_pixel(test, 10, 255);
   set_pixel(test, 11, 255);
   
   // Test d'écriture
   assert_int_equal(0, write_pnm(test, "test_output.ppm"));
   
   // Vérification que le fichier existe
   FILE *f = fopen("test_output.ppm", "r");
   assert_true(f != NULL);
   fclose(f);
   
   // Rechargement et vérification
   PNM *image_lue = NULL;
   assert_int_equal(0, load_pnm(&image_lue, "test_output.ppm"));
   assert_true(image_lue != NULL);
   
   // Vérification des pixels
   for(int i = 0; i < 12; i++) {
      assert_int_equal(get_pixel(test, i), get_pixel(image_lue, i));
   }
   
   // Nettoyage
   detruire_pnm(image_lue);
   remove("test_output.ppm");
}

//Fixture de test pour les filtres
void test_fixture_filtres() {

   test_fixture_start();

   fixture_setup(setup);
   fixture_teardown(td);

   run_test(test_filtre_retournement_type_0);
   run_test(test_filtre_retournement_type_1);
   run_test(test_filtre_retournement_type_2);

   run_test(test_filtre_gris_methode_1);
   run_test(test_filtre_gris_methode_2);

   run_test(test_filtre_négatif);

   run_test(test_filtre_monochrome_r);
   run_test(test_filtre_monochrome_v);
   run_test(test_filtre_monochrome_b);

   run_test(test_filtre_nb_PGM);
   run_test(test_filtre_nb_PPM);

   run_test(test_load_PGM);
   run_test(test_load_PPM);

   run_test(test_write_PGM);
   run_test(test_write_PPM);


   test_fixture_end();
}

void all_tests(void){
   test_fixture_filtres();
}

int main(){
   return run_tests(all_tests);
}