#include <stdio.h>
#include <stdlib.h>

int** soma3 (int** m1,int** m2,int** m3, int lin, int col) {
    int** mSoma = (int**) malloc(sizeof(int*)*lin);
    mSoma[0] = (int*) malloc(sizeof(int)*col);
    mSoma[1] = (int*) malloc(sizeof(int)*col);
    mSoma[0][0] = 0;
    mSoma[0][1] = 0;
    mSoma[0][2] = 0;
    mSoma[1][0] = 0;
    mSoma[1][1] = 0;
    mSoma[1][2] = 0;

    for (int i = 0; i < col; i++ ) {
        mSoma[0][i] += m1[0][i];
        mSoma[1][i] += m1[1][i];
    }

    for (int i = 0; i < col; i++ ) {
        mSoma[0][i] += m2[0][i];
        mSoma[1][i] += m2[1][i];
    }

    for (int i = 0; i < col; i++ ) {
        mSoma[0][i] += m3[0][i];
        mSoma[1][i] += m3[1][i];
    }

    printf("\nMatriz Soma\n");
    printf("|    %i  |    %i  |    %i  |\n", mSoma[0][0], mSoma[0][1], mSoma[0][2]);
    printf("|   %i  |   %i  |   %i  |\n", mSoma[1][0], mSoma[1][1], mSoma[1][2]);

    return 0;
}

int main() {

    int linhas = 2;
    int colunas = 3;

    int** m1 = (int**) malloc(sizeof(int*)*2);
    m1[0] = (int*) malloc(sizeof(int)*3);
    m1[1] = (int*) malloc(sizeof(int)*3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;
    printf("\nm1\n");
    printf("| %i | %i | %i |\n", m1[0][0], m1[0][1], m1[0][2]);
    printf("| %i | %i | %i |\n", m1[1][0], m1[1][1], m1[1][2]);

    int** m2 = (int**) malloc(sizeof(int*)*2);
    m2[0] = (int*) malloc(sizeof(int)*3);
    m2[1] = (int*) malloc(sizeof(int)*3);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[1][0] = 4;
    m2[1][1] = 5;
    m2[1][2] = 6;
    printf("\nm2\n");
    printf("| %i | %i | %i |\n", m2[0][0], m2[0][1], m2[0][2]);
    printf("| %i | %i | %i |\n", m2[1][0], m2[1][1], m2[1][2]);

    int** m3 = (int**) malloc(sizeof(int*)*2);
    m3[0] = (int*) malloc(sizeof(int)*3);
    m3[1] = (int*) malloc(sizeof(int)*3);
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[0][2] = 3;
    m3[1][0] = 4;
    m3[1][1] = 5;
    m3[1][2] = 6;
    printf("\nm3\n");
    printf("| %i | %i | %i |\n", m3[0][0], m3[0][1], m3[0][2]);
    printf("| %i | %i | %i |\n", m3[1][0], m3[1][1], m3[1][2]);

    soma3(m1, m2, m3, linhas, colunas);

    return 0;
}