#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <iostream>


#define THREADS 8

/* the function called for each thread */
void worker(int n) {
  /* get our thread id */
  int id = omp_get_thread_num( );

  #pragma omp ordered
  printf("--- Thread [%d] Iteration [%d] ---\n", id, n);
}

int main ( ) {
  int i;

    #pragma PHOENIX_VAR {partest} {i}

    #pragma PHOENIX_START partest

  #pragma PHOENIX_PARLOOP partest i%50 == 2
  #pragma omp parallel for num_threads(THREADS) ordered
  for (i = 0; i < 25; i++) {
     worker(i);
  }
  return 0;
}