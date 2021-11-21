#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
typedef short Bool;

void troca(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void print_array(int* array, int size) {
  int i;
  for(i = 0; i < size; i++)
    printf("%i ", array[i]);
  printf("\n");
}

int partition(int *array, int inicio, int fim)
{
  int pivot = array[fim - 1];
  int i = -1;
  int j;

  for (j = inicio; j < fim - 1; j++)
    if (array[j] <= pivot)
      troca(&array[++i], &array[j]);
  troca(&array[i + 1], &array[j]);

  return i + 1;
}

void quicksort(int* array, int size) {
  int q;
  if (size > 0) {
    q = partition(array, 0, size);

    quicksort(array, q);
    quicksort(&array[q+1], size - (q + 1));
  }
}

int selecao2(int *array, int i, int inicio, int fim)
{
  int q = partition(array, inicio, fim);
  if (inicio - fim == 0)
  {
    return array[inicio - 1]; // TESTAR COM 0 E 1
  }

  if (i < q)
  {
    return selecao2(array, i, inicio, q - 1);
  }
  else if (i > q)
  {
    return selecao2(array, i - (q + 1), q + 1, fim);
  }
  else
  {
    return array[q - 1];
  }
}

int selecao1(int* array, int i, int size) {
  quicksort(array, size);
  return array[i-1];
}


int main() {
  int i;
  float time_spent1 = 0.0;
  float time_spent2 = 0.0;
  float time_spent3 = 0.0;
  float time_spent4 = 0.0;
  int* array1;
  int* array2;
  int* array3;

  int size = 50000;
  int primeiro = 0;
  int ultimo = size-1;
  int iesimo = 4;

  array1 = malloc(sizeof(int)*size);
  array2 = malloc(sizeof(int)*size);
  array3 = malloc(sizeof(int)*size);

  srand(time(NULL));

  for(i = 0; i < size; i++) array1[i] = rand();
  for(i = 0; i < size; i++) {
    array2[i] = array1[i];
    array3[i] = array1[i];
  }

  printf("\nTamanho das arrays: %i\n", size);
  // printf("\nArray1 (original): ");
  // print_array(array1, size);
  // printf("Array2 (original): ");
  // print_array(array2, size);
  // printf("Array3 (original): ");
  // print_array(array3, size);
  printf("\n");


  printf("--- Recebendo array ordenada\n");
  quicksort(array1, size);
  // printf("Array1 (pós ordenação): ");
  // print_array(array1, size);
  // printf("\n");

  clock_t start1 = clock();
  int r1 = selecao1(array1, iesimo, size);
  clock_t pause1 = clock();
  printf("Resultado selecao1 para i=%i na array1 (ordenada): %i", iesimo, r1);
  time_spent1 += (float) (pause1 - start1) / CLOCKS_PER_SEC;
  printf("\nTempo decorrido: %.10f", time_spent1);
  
  printf("\n");
  
  clock_t start2 = clock();
  int r2 = selecao2(array1, iesimo, primeiro, ultimo);
  clock_t pause2 = clock();
  printf("Resultado selecao2 para i=%i na array1 (ordenada): %i", iesimo, r2);
  time_spent2 += (float) (pause2 - start2) / CLOCKS_PER_SEC;
  printf("\nTempo decorrido: %.10f", time_spent2);
  printf("\n");


  printf("\n--- Recebendo arrays não ordenadas\n");
  printf("\n");
  
  clock_t start3 = clock();
  int r3 = selecao1(array2, iesimo, size);
  clock_t pause3 = clock();
  printf("Resultado selecao1 para i=%i na array2: %i", iesimo, r3);
  time_spent3 += (float) (pause3 - start3) / CLOCKS_PER_SEC;
  printf("\nTempo decorrido: %.10f", time_spent3);
  
  printf("\n");
  
  clock_t start4 = clock();
  int r4 = selecao2(array3, iesimo, primeiro, ultimo);
  clock_t pause4 = clock();
  printf("Resultado selecao2 para i=%i na array3: %i", iesimo, r4);
  time_spent4 += (float) (pause4 - start4) / CLOCKS_PER_SEC;
  printf("\nTempo decorrido: %.10f", time_spent4);
  printf("\n");

  return 0;
}

