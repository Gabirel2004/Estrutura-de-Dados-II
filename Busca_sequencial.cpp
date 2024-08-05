#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Preenche(int array[], int tamanho){
    for(int i = 0; i < tamanho;i++){
        array[i] = rand() % 100;
    }
}

int Busca_Sequencial(int array[], int num, int tamanho){
    for(int i = 0; i < tamanho; i++){
        if(array[i] == num){
            return i + 1;// Retona a possição do valor no arrey
        }
    }
    return tamanho;// Caso nao seja encontrado o valor no arrey
}

int main(){
    srand(time(NULL));
    int tamanhos[] = {15 , 127 ,32767};

    for (int i = 0; i < 3; i++){
        int tamanho = tamanhos[i];
        int array[tamanho];
        Preenche(array,tamanho);

        int numComparacoesTotal = 0;
        int numtestes = 100;
        for(int j = 0; j < numtestes;j++){
            int num = rand() % 100;
            int numComparacoes = Busca_Sequencial(array,num,tamanho);
            numComparacoesTotal += numComparacoes; 
        }
        float media = numComparacoesTotal / numtestes;
        printf("\n\nArry de tamanho %d\n Numero de testes %d\n Media de comparacoes %.2f\n",tamanho,numtestes,media);
    }

    return 0;
}