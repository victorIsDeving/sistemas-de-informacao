#include <stdio.h>

void troca(int* a, int* b);
int partition(int* array, int size);
void quicksort(int* array, int size);
void print_array(int* array, int size);

int main() {
    int arrayOr[] = {3.0, 2.1, 6.7, 8.7, 9.7, 10.7, 4.0, 7.5, 12.5, 15.5};
    int* array = arrayOr;
    int size = 10;

    printf("Array original:\n");
    print_array(array, size);

    printf("Array ordenada:\n");
    quicksort(array, size);

    print_array(array, size);

    return 0;
}

void troca(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int* array, int size) {
  int pivot = array[size-1];
  int i = -1;
  int j;

  for(j = 0; j < size-1; j++)
    if(array[j] <= pivot)
      troca(&array[++i], &array[j]);
  troca(&array[i+1], &array[j]);

  return i + 1;
}

void quicksort(int* array, int size) {
  int q;
  if (size > 0) {
    q = partition(array, size);

    quicksort(array, q);
    quicksort(&array[q+1], size - (q + 1));
  }
}

void print_array(int* array, int size) {
  int i;
  for(i = 0; i < size; i++)
    printf("%i ", array[i]);
  printf("\n");
}