#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int vetor[], int tam)
{
    int i, j, aux;
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}
void selectionSort(int vetor[], int tam)
{
    int i, j, aux, menor;
    for (i = 0; i < tam; i++)
    {
        menor = i;
        for (j = i + 1; j < tam; j++)
        {
            if (vetor[j] < vetor[menor])
            {
                menor = j;
            }
        }
        if (i != menor)
        {
            aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
        }
    }
}


void insertionSort(int vetor[], int tam)
{
    int i, j, aux;
    for (i = 1; i < tam; i++) {
        aux = vetor[i];
        for (j = i - 1; j >= 0 && vetor[j] > aux; j--) {
            vetor[j + 1] = vetor[j]; 
        }
        vetor[j + 1] = aux;
    }
}
int main()
{
    int tam, i, op;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);
    int vetor[tam];
    srand(time(NULL));
    for (i = 0; i < tam; i++)
    {
        vetor[i] = rand() % 10 + 1;
    }
    printf("\nVetor gerado: ");
    for (i = 0; i < tam; i++)
    {
        printf("%d ", vetor[i]);
    }
    do
    {
        printf("\n\nEscolha o metodo de ordenação:\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Sair\n");
        printf("Opção: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            bubbleSort(vetor, tam);
            printf("\nVetor ordenado com Bubble Sort: ");
            for (i = 0; i < tam; i++)
            {
                printf("%d ", vetor[i]);
            }
            break;
        case 2:
            selectionSort(vetor, tam);
            printf("\nVetor ordenado com Selection Sort: ");
            for (i = 0; i < tam; i++)
            {
                printf("%d ", vetor[i]);
            }
            break;
        case 3:
            insertionSort(vetor, tam);
            printf("\nVetor ordenado com Insertion Sort: ");
            for (i = 0; i < tam; i++)
            {
                printf("%d ", vetor[i]);
            }
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }

    } while (op != 4);
    return 0;
}