#include <stdio.h>

#include "prefixe_suffixe.h"

#define N1 9
#define N2 10
#define N3 9

int main(){

  int T1[N1] = {1,4,2,4,5,1,4,2,4};
  int T2[N2] = {1,2,3,2,1,1,2,3,2,1};
  int T3[N3] = {3,2,3,2,1,2,3,2,1};
  int T4[N1] = {1,1,1,1,1,1,1,1,1};

  printf("Longueur plus long préfixe/suffixe de T1: %u\n", prefixe_suffixe(T1, N1));
  printf("Longueur plus long préfixe/suffixe de T2: %u\n", prefixe_suffixe(T2, N2));
  printf("Longueur plus long préfixe/suffixe de T3: %u\n", prefixe_suffixe(T3, N3));
  printf("Longueur plus long préfixe/suffixe de T4: %u\n", prefixe_suffixe(T4, N1));
}
