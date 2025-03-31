#include <stdio.h>

int main(int argc, char *argv[]){

   short produit_scalaire(char v1[], char v2[], char n);

   char v1[]={1,2,3};

   char v2[]={1,2,3};

   char n = 2;
   printf("%d", produit_scalaire(v1, v2, n));
   return 0;
}