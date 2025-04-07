/**
 * \file prefixe_suffixe.h
 * \brief Header pour le calcul de la longueur du plus long sous-tableau à la préfixe et suffixe.
 * \author Benoit Donnet, Géraldine Brieven -- Université de Liège (ULiège)
 * \version 0.1
 * \date 26/11/2024
 *
 * Implémente la p-compatibilité entre T1 et T2
 */

 #ifndef __PREFIXE_SUFFIXE__
 #define __PREFIXE_SUFFIXE__

 /*
  * @pre: T != NULL
  * @pre: N >= 0
  * @post: retourne la longueur du plus long préfixe et suffixe commun.
  */
int prefixe_suffixe(int *T, const unsigned int N);

#endif
