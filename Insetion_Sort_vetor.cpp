#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No{
    int valor;
    No *prox;
}no;

void Insertion_Sort(no **hend, int tamanho){
    for(int i = 0; i < tamanho; i++){
        no *novo = (no*)malloc(sizeof(no));
        if(novo != NULL){
            novo->valor = rand() % 10 + 1;
            if(*hend == NULL || novo->valor < (*hend)->valor){
                
            }else{

            }
        }else{
            printf("Erro de alocacao de memoria!!\n");
        }
    }
}

void Insertion_Sort(int array[], int tam) {
    int i, j, aux;
    for (i = 1; i < tam; i++) {
        aux = array[i];
        for (j = i - 1; j >= 0 && array[j] > aux; j--) {
            array[j + 1] = array[j]; 
        }
        array[j + 1] = aux;
    }
}

int main(void){
    srand(time(NULL));

    int tamanho;
    no *hend = NULL;

    printf("Digite o tamanho do seu vetor: ");
    scanf("%d", &tamanho);

    int array[tamanho];

    printf("\n\nvetor: ");
    for(int i = 0; i < tamanho; i++){
        array[i] = rand() % 10 + 1;
        printf("%d ",array[i]);
    }

    Insertion_Sort(array,tamanho);

    printf("\n\nVetor Ordenado: ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d] ", array[i]);
    }

    printf("Digite o tamanho da sua lista: ");
    scanf("%d",&tamanho);



    return 0;
}