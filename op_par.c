#include "stdio.h"
#include "stdlib.h"
#include <omp.h>


int main() {
  int m, n, p, q;
  double sum = 0;
  m = 1000;
  n = p = 1000;
  q = 1000;
  
	double **first = malloc(m * sizeof(double *));
  for(int i = 0; i < m; i++) {
    first[i] = malloc(n * sizeof(double));
  }
  double **second = malloc(p * sizeof(double *));
  for(int i = 0; i < p; i++) {
    second[i] = malloc(q * sizeof(double));
  }
  double **multiply = malloc(m * sizeof(double *));
  for(int i = 0; i < m; i++) {
    multiply[i] = malloc(q * sizeof(double));
  }
  
  srand(time(0));
  for (int i = 0; i < m; i++){
	  for (int j = 0; j < n; j++){
      first[i][j] = (rand() % 255);
      
    }
  }

  for (int i = 0; i < p; i++){
	  for (int j = 0; j < q; j++){
      second[i][j] = (rand() % 255);
    }
  }

  double start_time, run_time;
  start_time = omp_get_wtime();
  #pragma omp parallel for
  for (int c = 0; c < m; c++) {
    for (int d = 0; d < q; d++) {
      for (int k = 0; k < p; k++) {
        sum = sum + first[c][k]*second[k][d];
      }
      multiply[c][d] = sum;
      sum = 0;
    }
  }
  run_time = omp_get_wtime() - start_time;
  printf("Run Time: %f \n", run_time);

  return 0;
}