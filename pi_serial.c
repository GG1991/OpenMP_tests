
#include <stdio.h>
#include <omp.h>

static long num_steps = 10000000;
double step;

int main(void)
{

  int i;
  double time;
  double x, pi, sum = 0.0;

  time = omp_get_wtime();
  step = 1.0 / (double) num_steps;

  for (i = 0; i < num_steps; ++i) {
    x = (i + .5) * step;
    sum += 4.0 / (1.0 + x * x);
  }

  pi = step * sum;

  time = omp_get_wtime() - time;
  printf("Pi = %lf\ttime = %lf\n", pi, time);
  return 0;
}
