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

// Cria um arquivo .bin com alguns registros
void createBin() {
    REGISTRO r1;
    r1.NroUSP = 11111;
    r1.curso = 0;
    r1.estado = 10;
    r1.idade = 20;
    r1.valido = true;
    REGISTRO r2;
    r2.NroUSP = 33333;
    r2.curso = 0;
    r2.estado = 13;
    r2.idade = 23;
    r2.valido = true;
    REGISTRO r3;
    r3.NroUSP = 22222;
    r3.curso = 1;
    r3.estado = 12;
    r3.idade = 22;
    r3.valido = true;
    REGISTRO r4;
    r4.NroUSP = 44444;
    r4.curso = 2;
    r4.estado = 14;
    r4.idade = 24;
    r4.valido = true;

    /* Create the file */
    FILE *fh = fopen ("origem.bin", "wb");
    if (fh != NULL) {
        fwrite (&r3, sizeof (REGISTRO), 1, fh);
        fwrite (&r2, sizeof (REGISTRO), 1, fh);
        fwrite (&r4, sizeof (REGISTRO), 1, fh);
        fwrite (&r1, sizeof (REGISTRO), 1, fh);
        fclose (fh);
    }
}

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

void printRegistro(REGISTRO* r) {
    printf (
        "   NrUsp: %i\n"
        "   Curso: %i\n"
        "   Estad: %i\n"
        "   Idade: %i\n"
        "   Valid: %i\n", 
        r->NroUSP, r->curso, r->estado, r->idade, r->valido);
}

void printFile(FILE* f) {
        REGISTRO r;
        int i = 1;
        while (fread(&r, sizeof(REGISTRO), 1, f) == 1) {
            printf ("Registro %i:\n", i);
            printRegistro(&r);
            i++;
        }
}

// Função principal de ordenação
int buscarEndereco(TABELA tabela[], int nusp, int size) {
    for (int i = 0; i < V; i++) {
        if (tabela[i].chave == nusp) {
            return i;
        }
    }

    return -1;
}

// Função principal de ordenação
int excluirIndice(TABELA tabela[], int chave, int size) {
    for (int i = 0; i < V; i++) {
        if (tabela[i].chave == chave) {
            tabela[i].chave = -1;
            tabela[i].end = -1;
            return i;
        }
    }

    return -1;
}