#include <assert.h>
#include <stdlib.h>

#include "prefixe_suffixe.h"


int prefixe_suffixe(int *T, const unsigned N){
  assert(T != NULL && N >= 0);
  int k = N-1;
  int i = 0;

  while (k > 0){
  while(i < k && T[i] == T[N - k +i]){
    i++;
    }
    if (i == k){
        return k;
    }
    else{
        i = 0;
    }
  k--;
  }
  return 0;
}
