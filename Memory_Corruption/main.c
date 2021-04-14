/* Problem description
To detect memory corruption, we propose to use the ‘canary’ method: each time
memory is allocated, mallocinitialises space before and after with specific
fixed values. When a zone is freed, freechecks that these specific values are
still present. If it is NOT the case, free reports the error.

Write functions my_mallocand my_freeas described. Your functions call the actual
mallocand freeto actually allocate and free the memory */

#include <stdio.h>
#include <stdlib.h>
char S_VALUE = 20;
short N_CELLS = 5;

// Allocates the space in the memory
// size : number of bytes
void *my_malloc(size_t size) {
  int i;
  int total_size = 2 * N_CELLS + size;
  void *a = malloc(total_size);
  for (i = 0; i < N_CELLS; i++)
    *(char *)(a + i) = S_VALUE;
  for (i = total_size - N_CELLS; i < total_size; i++)
    *(char *)(a + i) = S_VALUE;
  return a + N_CELLS;
}

// frees allocated memory
void my_free(void *a) {
  int i = -N_CELLS;
  for (i; i < 0; i++) {
    if (*(char *)(a + i) != S_VALUE) {
      perror("memory corruption\n");
      exit(1);
    }
  }
  int c = 0;

  for (i; *(char *)(a + i) != S_VALUE; i++)
    ;
  for (int j = i; j < N_CELLS + i; j++) {
    if (*(char *)(a + j) == S_VALUE)
      c++;
  }
  if (c != N_CELLS) {
    printf("memory corruption\n");
    exit(1);
  }
}

int main() {
  char *a = (char *)my_malloc(5);

  // No error case
  for (int i = 0; i < 5; i++)
    a[i] = 4;

  // Display the error case
  // for(int i = 0; i < 8; i++) a[i] = 4;

  my_free(a);
}