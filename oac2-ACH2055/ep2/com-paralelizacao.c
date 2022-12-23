#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

typedef struct {
  float *array;
  size_t usedSize;
  size_t maxSize;
} Array;

//sorting functions
void troca(float* a, float* b);
void bubble_sort(Array* a);
int partition(Array* a, int start, int end);
void quicksort(Array* a, int start, int end);

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

    // //sorting debug
    printf("PATH: %s \n", filePath);
    // printf("Array properties: \n");
    // printf("- arrayOrder.array: ");
    // print_array(&arrayOrder);
    // printf("- arrayOrder.usedSize: %i\n", arrayOrder.usedSize);
    // printf("- arrayOrder.maxSize: %i\n", arrayOrder.maxSize);
    
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
      #pragma omp parallel
        {
          #pragma omp single nowait
          quicksort(&arrayOrder, 0, arrayOrder.usedSize - 1);
        }
    }
    //time elapsed counter
    end = clock();
    timeTaken = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nTime elapsed in seconds: %.15f\n", timeTaken);
    // //sorting debug
    // printf("\n\n- arrayOrder.array (sorting %i): ", sortingOption);
    // print_array(&arrayOrder);

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

//cria região paralela
void bubble_sort(Array* a) {
  int k, i;
  for(k = 0; k < a->usedSize; k++) {
    if ( k % 2 == 0) {
      #pragma omp parallel for
      for ( i = 0; i < a->usedSize/2; i++)
        if (a->array[ 2 * i ] > a->array[ 2 * i + 1 ])
          troca(&a->array[ 2 * i ], &a->array[ 2 * i + 1 ]);
    } else {
      #pragma omp parallel for
      for ( i = 0; i < a->usedSize/2 - 1; i++)
        if (a->array[ 2 * i + 1 ] > a->array[ 2 * i + 2 ])
          troca(&a->array[ 2 * i + 1 ], &a->array[ 2 * i + 2 ]);
    }
  }
}

int partition(Array* a, int left, int right) {
	int pivot = a->array[right]; // pivot
	int i = (left - 1); // Index of smaller element
	for (int j = left; j <= right- 1; j++) {
		if (a->array[j] <= pivot) {
			i++; // increment index of smaller element
			troca(&a->array[i], &a->array[j]);
		}
	}
	troca(&a->array[i + 1], &a->array[right]);
  
	return (i + 1);
}

void quicksort(Array* a, int left, int right) {
	if (left < right)
	{
		int pi = partition(a, left, right);
		#pragma omp task firstprivate(a,left,pi)
		{
			quicksort(a,left, pi - 1);
		}
		#pragma omp task firstprivate(a,right,pi)
		{
			quicksort(a, pi + 1, right);
		}
	}
}