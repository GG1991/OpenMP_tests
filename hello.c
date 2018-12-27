
#include <stdio.h>
#include <omp.h>

int main(void)
{

  int n = 4;

#pragma omp parallel num_threads(n)
  {
    int ID = omp_get_thread_num();
    printf("hello(%d)", ID);
    printf(" world(%d)\n", ID);
  }

  return 0;
}
