#include <stdio.h>
#include <omp.h>

int main () {
    //Imprime a thread principal
    printf("\nHello - Before Parallel Region...\n\n");
    
    // omp_set_num_threads(8);

    //Create parallel region
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        printf("Thread %d of %d\n", id, nt);
    }
    
    printf("\nHello - After Parallel Region...\n\n");
    
    return 0;
}