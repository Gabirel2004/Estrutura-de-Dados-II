#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void inset(int valor[], int novo, int *tam){
    int posicao;
    for (posicao = 0; posicao < *tam; posicao++){
        if(valor[posicao] > novo){
            break;
        }
    }
    for(int j = *tam; j > posicao; j--){
        valor[j] = valor[j - 1];
    }
    valor[posicao] = novo;
    (*tam)++;
}
bool Busca_Binaria(int valor[],int busca,int inicio,int fim){
    if (inicio > fim){
        return false;
    }
    int meio = (inicio + fim)/2;
    if(valor[meio] == busca){
        return true;
    }
    else if(valor[meio] < busca){
        inicio = meio + 1;
        return Busca_Binaria(valor,busca,inicio,fim);
    }else{
        fim = meio - 1;
        return Busca_Binaria(valor,busca,inicio,fim);
    }
    return false;
}
int main(){
    int valor[5];
    int tam = 0;
    int inicio = 0;
    int busca;
    bool resutado;
    srand(time(NULL));
    for(int i = 0; i < 5; i++){
        int novo = rand() % 10;
        inset(valor, novo, &tam);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("[%d] ",valor[i]);
    }
    printf("Digite um valor que vc esta procurando: ");
    scanf("%d",&busca);
    resutado = Busca_Binaria(valor,busca,inicio,tam - 1);

    if(resutado == true){
        printf("\n\nElemento encontrado!!!");
    }
    else{
        printf("\n\nElemento nao encontrado!!!");
    }
    return 0;
}