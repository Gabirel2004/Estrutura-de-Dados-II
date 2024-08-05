#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No{
    int conteudo;
    struct No *prox;
}no;

void Insert_Inicio(no **hend, int size){
    for(int i = 0; i < size; i++){
        no *novo = (no*)malloc(sizeof(no));
        if(novo){
            novo->conteudo = rand() % 10 + 1;
            novo->prox = *hend;
            *hend = novo;
        }else{
            printf("Erro de alocação de memoria!!");
        }
    }
}

void Troca(no *a, no *b) {
    int temp = a->conteudo;
    a->conteudo = b->conteudo;
    b->conteudo = temp;
}

void Shell_Sort(no **hend,int n){
    int gap = n/2;
    while (gap > 0){

        int i = 0;
        int j = gap + i;

        while(i < gap){
            j = gap + i;
            no *aux = *hend;
            no *temp = *hend;            
            for(int k = 0; k < j && aux != NULL; k++){
                aux = aux->prox;
            }
            for(int v = 0; v < i; v++){
                temp = temp->prox;
            }
            while (aux != NULL){
                if(temp->conteudo > aux->conteudo){
                    Troca(temp,aux);
                }
                temp = temp->prox;
                aux = aux->prox;
            }
            i++;
        } 
        gap /= 2;
    }
}

void Print(no *hend){
    no *aux = hend;
    printf("Lista: ");
    while (aux != NULL)
    {
        printf("%d->",aux->conteudo);
        aux = aux->prox;
    }
    printf("NULL\n\n");
    
}

int main(){
    srand (time(NULL));
    int n;
    no *hend = NULL;
    printf("Digite o tamanho do seu vetor: ");
    scanf("%d",&n);

    printf("\nVetor: ");
    Insert_Inicio(&hend,n);
    Print(hend);

    printf("\nVetor ordenado: ");
    Shell_Sort(&hend,n);
    Print(hend);

    return 0;
}