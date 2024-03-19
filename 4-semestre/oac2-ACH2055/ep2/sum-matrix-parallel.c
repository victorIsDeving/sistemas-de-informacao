/*
Program to sum to matrix into a third
Using pararallelization
*/

#include <stdio.h>
#include <omp.h>

int main () {
    float A[ 2048 ];
    float B[ 2048 ];
    float C[ 2048 ];
    int i;
    for ( i = 0; i < 2048; i++)
    {
        A[i]=2;
        B[i]=3;
    }

    //parallelize sum
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        int i;
        #pragma omp for
        for( i = 0; i < 2048; i++) {
            printf("A thread %d somou a posicao %d\n", id, i);
            C[ i ] = A[ i ] + B[ i ];
        }
    }

    //writing result
    for(i=0;i<2048;i++) {
        printf("C[ %d ] = %f\n", i, C[ i ]);
    }

    return 0;
}