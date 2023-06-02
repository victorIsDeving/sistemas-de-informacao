#include <stdio.h>
#define bool int
#define false 0
#define true 1

// Variável para controle da quantidade de índices
#define V 10

typedef struct {
    int NroUSP; // chave primária
    int curso;
    int estado;
    int idade;
    bool valido; // para exclusão lógica
} REGISTRO;

//estrutura controle da tabela de índices primários
typedef struct {
    int chave;
    int end;
} TABELA;

// function to swap elements
void swap(TABELA *a, TABELA *b) {
    TABELA t = *a;
    *a = *b;
    *b = t;
}

// function to find the partition position
int partition(TABELA array[], int low, int high) {
    // select the rightmost element as pivot
    int pivot = array[high].chave;

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j].chave <= pivot) {
            
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;
            
            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(TABELA array[], int low, int high) {
    if (low < high) {
        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}


// Função auxiliar para adicionar um elemento na 
// tabela de índices primários
bool inserirIndice(TABELA tabela[], int chave, int end) {
    tabela[end].chave = chave;
    tabela[end].end = end;

    return true;
}

// Function to print array elements
void printArray(TABELA array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%i(%i)  ", array[i].chave, array[i].end);
    }
    printf("\n");
}

void printFile(FILE* f) {
        REGISTRO r;
        int i = 1;
        while (fread(&r, sizeof(REGISTRO), 1, f) == 1) {
            printf (
                "   Registro %i:\n"
                "       NrUsp: %i\n"
                "       Curso: %i\n"
                "       Estad: %i\n"
                "       Idade: %i\n"
                "       Valid: %i\n", 
                i, r.NroUSP, r.curso, r.estado, r.idade, r.valido);
            i++;
        }
}
