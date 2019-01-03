
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <omp.h>

#define NVEC 10000
#define VECSIZE 10000

int main(void)
{

  int i, j;
  double time;
  double **vec_1, **vec_2, **vec_3, *sums;

  vec_1 = malloc(NVEC * sizeof(double*));
  vec_2 = malloc(NVEC * sizeof(double*));
  vec_3 = malloc(NVEC * sizeof(double*));
  for (i = 0; i < NVEC; ++i) {
	  vec_1[i] = malloc(VECSIZE * sizeof(double));
	  vec_2[i] = malloc(VECSIZE * sizeof(double));
	  vec_3[i] = malloc(VECSIZE * sizeof(double));
	  for (j = 0; j < VECSIZE; ++j) {
		  vec_1[i][j] = 1;
		  vec_2[i][j] = 2;
	  }
  }

  time = omp_get_wtime();

#pragma omp parallel for private (j)
  for (i = 0; i < NVEC; ++i) {
	  double *vec_1_ptr = vec_1[i];
	  double *vec_2_ptr = vec_2[i];
	  double *vec_3_ptr = vec_3[i];
	  for (j = 0; j < VECSIZE; ++j) {
		  vec_3_ptr[j] = vec_1_ptr[j] + vec_2_ptr[j];
	  }
  }

  time = omp_get_wtime() - time;

  for (i = 0; i < NVEC; ++i) {
	  for (j = 0; j < VECSIZE; ++j) {
		  assert(fabs(vec_3[i][j] - 3.0) < 1.0e-10);
	  }
  }

  printf("time = %lf\n", time);
  return 0;
}
