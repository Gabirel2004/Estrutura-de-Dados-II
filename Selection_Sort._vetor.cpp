#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int tamanho;
    printf("Digite o tamanho do seu vetor: ");
    scanf("%d", &tamanho);

    int array[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        array[i] = rand() % 10 + 1;
    }
    printf("\n\nVetor");
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d] ", array[i]);
    }


    for (int i = 0; i < tamanho - 1; i++)
    {
        int posi = i;
        for (int j = i + 1; j < tamanho; j++)
        {
            if (array[j] < array[posi])
            {
                posi = j;
            }
        }
        int aux = array[i];
        array[i] = array[posi];
        array[posi] = aux;
    }

    printf("\n\nVertor Ordenado");
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d] ", array[i]);
    }
    return 0;
}