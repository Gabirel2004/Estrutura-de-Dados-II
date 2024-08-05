#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No{
    int posicao;
    int num;
    struct No *prox;
}no;

typedef struct{
    no *cabeca = NULL;
    int quant = 0;
}Lista;

void cria_lista(Lista *lista){
    lista->cabeca = NULL;
    lista->quant = 0;
}

void Insert_Inicio(Lista *lista, int tamanho){
    int posicao = tamanho - 1;
    for(int i = 0; i < tamanho; i++){
        no *novo = (no*)malloc(sizeof(no));
        if(novo){
            novo->num = rand() % 10 + 1;
            novo->prox = lista->cabeca;
            novo->posicao = posicao--;
            lista->cabeca = novo;
            lista->quant++;
        } else {
            printf("Erro de alocação de memoria!!");
        }
    }
}
//Metodo que faz a troca
void Troca(no *a, no *b){
    if(a->num == b->num){return;}

    no *aux_prox_a = a->prox;
    no *aux_prox_b = a->prox->prox;

    a->prox = aux_prox_b;
    b->prox = aux_prox_a;
}

no *Busca(Lista *lista, int posicao) {
    no *aux = lista->cabeca;
    while (aux != NULL) {
        if (aux->posicao == posicao) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}


void Max_Heap(Lista *lista,int i){
    no *aux_i = Busca(lista,i);

    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    
    no *aux_l = Busca(lista,l);
    no *aux_Maior = Busca(lista,i);
    //Verifica se o valor a esquerda e maior que o da raiz
    if(l < lista->quant && aux_l->num > aux_Maior->num){
        aux_Maior = aux_l;
    }
    no *aux_r = Busca(lista,r);
    if(aux_Maior != aux_i){ aux_Maior = Busca(lista,i);}
    //verifica se o valor a direita e maiot que a raiz
    if(r < lista->quant && aux_r->num > aux_Maior->num){
        aux_Maior = aux_r;
    }

    if(aux_Maior != aux_i){
        //Faz a troca
        Troca(aux_i,aux_Maior);
        Max_Heap(lista,aux_Maior->posicao);
    }
}
//Construir a Heap
void Builb_Heap(Lista *lista){
    //Índice do último nó não-folha
    int strat = (lista->quant/2) - 1;

    for(int i = strat; i >= 0; i--){
        Max_Heap(lista, i);
    }
}

// void Heap_Sort(int array[], int n){
//     Builb_Heap(array,n);
//     for(int i = n - 1; i >=0; i--){
//         Troca(&array[0],&array[i]);
//         Max_Heap(),n,0);
//     }
// }

void Print(Lista *lista){
    no *atual = lista->cabeca;
    
    printf("Lista: ");
    while (atual != NULL){
        printf("idx = %d -> %d ,",atual->posicao,atual->num);
        atual = atual->prox;
    }  
    printf("NULL"); 
}

int main(){
    int n;
    srand(time(NULL));
    printf("Digite o tamanho da lista: ");
    scanf("%d", &n);
    Lista lista;

    Insert_Inicio(&lista,n);
    Builb_Heap(&lista);
    Print(&lista);
    
    return 0;
}