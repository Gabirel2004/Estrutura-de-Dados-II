#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Raiz{
    int valor;
    struct Raiz *esquerda;
    struct Raiz *direita;
}no;

no *Criar_no(){
    no *novo = (no*)malloc(sizeof(no));
    novo->valor = rand() % 100;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

void Incluir_no(no *raiz,no *novo){
    if(raiz->valor > novo->valor){
        if(raiz->esquerda == NULL){
            raiz->esquerda = novo;
            return;
        }
        Incluir_no(raiz->esquerda,novo);
    }else{
        if(raiz->direita == NULL){
            raiz->direita = novo;
            return;
        }
        Incluir_no(raiz->direita,novo);
    }
}

void Criar_raiz(no **raiz){
    if(*raiz == NULL){
        *raiz = Criar_no();
        return;
    }
    no *novo = Criar_no();
    Incluir_no(*raiz,novo);
}

no *Busca_no(no *raiz,int valor){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->valor == valor){
        return raiz;
    }else if(raiz->valor > valor){
        return Busca_no(raiz->esquerda,valor);
    }else{
        return Busca_no(raiz->direita,valor);
    }
}

bool E_folha(no *raiz){return raiz->esquerda == NULL && raiz->direita == NULL;}

bool Um_filho(no *raiz){
    if(raiz->esquerda != NULL && raiz->direita == NULL){return true;}
    if(raiz->direita != NULL && raiz->esquerda == NULL){return true;}
    return false;
}

no *Maior(no *raiz){
    if(raiz == NULL){return NULL;}
    if(raiz->direita == NULL){return raiz;}
    return Maior(raiz->direita);
}

no *Menor(no *raiz){
    if(raiz == NULL){return NULL;}
    if(raiz->esquerda == NULL){return raiz;}
    return Menor(raiz->esquerda);
}

no *Remover_no(no *raiz,int valor){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->valor == valor){
        if(E_folha(raiz) == true){
            raiz = NULL;
            free(raiz);
            return NULL;
        }else if(Um_filho(raiz) == true){
            no *remover = NULL;
            if(raiz->esquerda != NULL){
                remover = raiz->esquerda;
            }else{
                remover = raiz->direita;
            }
            free(raiz);
            return remover ;
        }else{
            no *substituir = Maior(raiz->esquerda);
            Remover_no(raiz,substituir->valor);
            substituir->esquerda = raiz->esquerda;
            substituir->direita = raiz->direita;
            raiz->esquerda = NULL;
            raiz->direita = NULL;
            free(raiz);
            raiz = substituir;
            return raiz;
        }
    }else{
        if(raiz->valor > valor){
            raiz->esquerda = Remover_no(raiz->esquerda,valor);
        }else{
            raiz->direita = Remover_no(raiz->direita,valor);
        }
        return raiz;
    }
    return NULL;
}

int Altura_Arvore(no *raiz){
    if(raiz == NULL || (raiz->esquerda == NULL && raiz->direita == NULL)){return 0;}
    else{
        int esquerda = 1 + Altura_Arvore(raiz->esquerda);
        int direita = 1 + Altura_Arvore(raiz->direita);
        
        if(esquerda > direita){return esquerda;}
        else{return direita;}
    }
    
}

void Imprimir(no *raiz){
    if(raiz == NULL){
        return;
    }
    Imprimir(raiz->esquerda);
    printf("%d->", raiz->valor);
    Imprimir(raiz->direita);
}

int main(){
    srand(time(NULL));
    no *raiz = NULL;
    int op,valor;
    do{
        printf("\n\tMENU\t\n");
        printf("1 - Inserir valor\n2 - Imprimir valores\n3 - Buscar valor\n4 - Remover valor\n0 - sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d",&op);
        switch (op){
        case 1:
            Criar_raiz(&raiz);
            break;
        case 2:
            if(raiz != NULL)printf("\nSua arvore em ordem crecente: ");
            Imprimir(raiz);
            break;
        case 3:
            printf("\nDigite o valor que vc esta buscando: ");
            scanf("%d",&valor);
            if(Busca_no(raiz,valor) != NULL){
                printf("\nO valor %d esta presente na sua arvore!!\n",valor);
            }else{
                printf("\nO valor nao foi encontrado na sua arvore!!");
            }
            break;
        case 4:
            printf("\nDigite o valor que vc quer remover: ");
            scanf("%d",&valor);
            raiz = Remover_no(raiz, valor);
            break;    
        case 0:
            printf("\nSaindo...");
            break;
        default:
            printf("\nEscolha uma opcao valida!!\n");
            break;
        }
    }while(op != 0);
    return 0;
}