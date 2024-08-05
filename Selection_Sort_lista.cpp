#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NO{
    int data;
    struct NO *next;
}no;

void Insert_Inicio(no **hend, int size){
    for(int i = 0; i < size; i++){
        no *novo = (no*)malloc(sizeof(no));
        if(novo){
            novo->data = rand() % 10 + 1;
            novo->next = *hend;
            *hend = novo;
        }else{
            printf("Erro de alocação de memoria!!");
        }
    }
}

void Print(no *hend){
    no *aux = hend;
    printf("Lista: ");
    while (aux != NULL)
    {
        printf("%d->",aux->data);
        aux = aux->next;
    }
    printf("NULL\n\n");
    
}

void Troca(no *a, no *b){
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void Selection_Sort(no **hend) {
    no *prim = *hend;
    while (prim != NULL) {
        no *menor = prim;
        no *aux = prim->next;
        while (aux != NULL) {
            if (aux->data < menor->data) {
                menor = aux;
            }
            aux = aux->next;
        }

        Troca(prim, menor);
        prim = prim->next;
    }
}


int main(){
    srand(time(NULL));
    int tam;
    no *hend = NULL;
    printf("Digite o tamanho da sua lista: ");
    scanf("%d",&tam);

    Insert_Inicio(&hend,tam);
    printf("Lista: ");
    Print(hend);

    Selection_Sort(&hend);
    printf("Lista ordenada: ");
    Print(hend);
    return 0;
}


//VERSAO C COM LISTA DUPLAMENTE ENCADEADA
void Bubble_Nome(Lista *lista) {
    if (lista->qtd_Arquivos <= 1)
        return;

    int trocado;
    Arquivo *atual;
    Arquivo *ultimo = NULL;

    do {
        trocado = 0;
        atual = lista->Head;

        while (atual->prox != ultimo) {
            if (strcmp(atual->nome, atual->prox->nome) > 0) {
                Arquivo *temp = atual->prox;
                atual->prox = temp->prox;
                temp->prox = atual;
                if (atual->ant != NULL)
                    atual->ant->prox = temp;
                if (temp->prox != NULL)
                    temp->prox->ant = atual;
                if (atual == lista->Head)
                    lista->Head = temp;
                if (temp == lista->Tail)
                    lista->Tail = atual;
                trocado = 1;
            }
            atual = atual->prox;
        }
        ultimo = atual;
    } while (trocado);
}

