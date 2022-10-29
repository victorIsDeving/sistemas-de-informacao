#include <stdio.h>

void troca(int* a, int* b);

void print_array(int* array, int size);
void bubble_sort(int* array, int size);

int main() {
    int arrayOr[] = {3.0, 2.1, 6.7, 8.7, 9.7, 10.7, 4.0, 7.5, 12.5, 15.5};
    int* array = arrayOr;
    int size = 10;

    printf("Array original:\n");
    print_array(array, size);

    printf("Array ordenada:\n");
    bubble_sort(array, size);

    print_array(array, size);
    return 0;
}

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

void bubble_sort(int* array, int size) {
  int i, j;
  for(i = 0; i < size; i++)
    for (j = size; j > i+1; j--)
      if (array[j-1] < array[j-2])
        troca(&array[j-1], &array[j-2]);
}