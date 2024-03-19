#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  float *array;
  size_t usedSize;
  size_t maxSize;
} Array;

//sorting functions
void troca(float* a, float* b);
void bubble_sort(Array* a);
int partition(float* array, int size);
void quicksort(float* array, int size);

//support functions
void initArray(Array *a, size_t initialMaxSize);
void print_array(Array* a);
void insertArray(Array *a, float element);


int main( void ) {
    char filePath[1000] = 
      "C:\\sistemas-informacao\\oac2-ACH2055\\ep1\\dados-para-teste\\dados_1000000.txt";
    int sortingOption = 2;
    char buffer[10];
    FILE * filePointer;
    Array arrayOriginal, arrayOrder;
    initArray(&arrayOriginal, 10);
    initArray(&arrayOrder, 10);
    float value;

    // printf("\nEnter file path: \n");
    // scanf("%s", filePath);
    // printf("\nEnter sorting option: \n 1 - BubbleSort\n 2 - Quicksort");
    // scanf("%d", sortingOption);

    filePointer = fopen(filePath, "r");
    //verify opening error
    if ( filePointer == NULL ) {
      perror("Error opening file");
      return 1;
    }
    //read file content line by line
    while (fgets(buffer, 10, filePointer) != NULL) {
        value = atof(buffer); //converts to float value
        insertArray(&arrayOrder, value); //adds to array to order
        insertArray(&arrayOriginal, value); //adds to array for copy of original
    }
    //close file, good practice
    fclose(filePointer);

    // path confirmation
    printf("PATH: %s \n", filePath);
    
    //time elapsed counter
    clock_t begin, end;
    double timeTaken;
    begin = clock();
    //sorting part
    if (sortingOption == 1) {
      printf("\nSorting with Bubble Sort...");  
      bubble_sort(&arrayOrder);
    } else {
      printf("\nSorting with Quick Sort...");  
      quicksort(arrayOrder.array, arrayOrder.usedSize);
    }
    //time elapsed counter
    end = clock();
    timeTaken = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nTime elapsed in seconds: %.15f\n", timeTaken);

    // //Writing to file
    // filePointer = fopen(filePath, "w");
    // //verify opening error
    // if ( filePointer == NULL ) {
    //   perror("Error opening file");
    //   return 1;
    // }
    // //add content to file, overwriting previous content
    // int i;
    // for ( i = 0; i < arrayOriginal.usedSize; i++) {
    //   fprintf(filePointer, "%f\n", arrayOriginal.array[i]);
    // }
    // fprintf(filePointer, "\n\n");
    // for ( i = 0; i < arrayOrder.usedSize; i++) {
    //   fprintf(filePointer, "%f\n", arrayOrder.array[i]);
    // }
    // //close file, good practice
    // fclose(filePointer);

    return 0;
}

void initArray(Array *a, size_t initialMaxSize) {
  a->array = malloc(initialMaxSize * sizeof(float));
  a->usedSize = 0;
  a->maxSize = initialMaxSize;
}

void insertArray(Array *a, float element) { 
  if (a->usedSize == a->maxSize) {
    a->maxSize *= 10; //grows array size as necessary
    a->array = realloc(a->array, a->maxSize * sizeof(float));
  }
  a->array[a->usedSize++] = element;
}

void print_array(Array* a) {
  int i;
  for(i = 0; i < a->usedSize; i++) {
      printf("\n  %f ", a->array[i]);
  }
  printf("\n");
}

void troca(float* x, float* y) {
  float tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

void bubble_sort(Array* a) {
  int i, j;
  for(i = 0; i < a->usedSize; i++)
    for (j = a->usedSize; j > i+1; j--)
      if (a->array[j-1] < a->array[j-2])
        troca(&a->array[j-1], &a->array[j-2]);
}

int partition(float* array, int size) {
  float pivot = array[size-1];
  int i = -1;
  int j;

  for (j = 0; j < size-1; j++) {
    if(array[j] <= pivot) {
      troca(&array[++i], &array[j]);
    }
  }
  troca(&array[i+1], &array[j]);

  return i + 1;
}

void quicksort(float* array, int size) {
  int q;
  if (size > 0) {
    q = partition(array, size);
    quicksort(array, q);
    quicksort(&array[q+1], size - (q + 1));
  }
}