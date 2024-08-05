#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Raiz{
    int valor;
    struct Raiz *esquerda;
    struct Raiz *direita;
    int altura;
}no;
//Essa função cria um novo nó
no *Criar_no(){
    no *novo = (no*)malloc(sizeof(no));
    printf("Digite o valor a ser inserido: ");
    scanf("%d",&novo->valor);
    //novo->valor = rand() % 100;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 0;
    return novo;
}

int Maior_altura(int altura1,int altura2);
int Altura_no(no *raiz);
no *Balancear(no *raiz);

// Essa função inserier valores na arvore
no *Incluir_no(no *raiz, no *novo){
    // Caso o no esteja vazil rentona o novo
    if(raiz == NULL){
        return novo;
    }
    if(raiz->valor > novo->valor){
        if(raiz->esquerda == NULL){
            raiz->esquerda = novo;
        }else{
            // A raiz vai receber o retono da funçao que e o valor novo 
            raiz->esquerda = Incluir_no(raiz->esquerda, novo);
        }
    }else if(raiz->valor < novo->valor){
        if(raiz->direita == NULL){
            raiz->direita = novo;
        }else{
            raiz->direita = Incluir_no(raiz->direita, novo);
        }
    }
    // Atualizar altura após a inserção
    raiz->altura = Maior_altura(Altura_no(raiz->esquerda), Altura_no(raiz->direita)) + 1;
    // Balancear a árvore após a inserção
    raiz = Balancear(raiz);
    return raiz;
}
// Essa função é um auxilar que inserie valores na arvore
void Criar_raiz(no **raiz){
    // Caso a arvore esteja vazia, será criado uma nova raiz
    if(*raiz == NULL){
        *raiz = Criar_no();
        return;
    }
    // Caso a arvore não esteja vazia
    no *novo = Criar_no();
    *raiz = Incluir_no(*raiz,novo);
}
// Essa função Busca na arvore o valor
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
// Essa função recebe duas alturas e retorna o maior
int Maior_altura(int altura1,int altura2){return (altura1 > altura2)? altura1: altura2;}
// Essa fução retorna o valor da altura do nó da arvore
int Altura_no(no *raiz){
    if(raiz == NULL){return -1;}
    return raiz->altura; 
}
// Essa função retorna o fato de baleanciamento da minha sub-arvore
int Fator_De_balaciamenro(no *raiz){
    if(raiz != NULL){
        return Altura_no(raiz->esquerda) - Altura_no(raiz->direita);
    }
    return 0;
}
// Essa função verifica se o nó e folha ou não
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
    // Caso a raiz seja NULL é retornado NULL
    if(raiz == NULL){
        return NULL;
    }
    // Caso o valor que eu estou procurando seja igual
    if(raiz->valor == valor){
        if(E_folha(raiz) == true){ // Caso 1 o nó é uma folha
            raiz = NULL;
            free(raiz);
            return NULL;
        }else if(Um_filho(raiz) == true){ // Caso 2 o nó tem um unico filho
            no *remover = NULL;
            if(raiz->esquerda != NULL){
                remover = raiz->esquerda;
            }else{
                remover = raiz->direita;
            }
            free(raiz);
            return remover ;
        }else{// Caso 3 o nó tem 2 filhos
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
    }else{// Caso o valor não seja igual tenho que procura onde está o nó a ser removido
        if(raiz->valor > valor){ // caso seja menor vou pra esquerda
            raiz->esquerda = Remover_no(raiz->esquerda,valor);
        }else{ // Caso seja maior vou pra direita
            raiz->direita = Remover_no(raiz->direita,valor);
        }
    }
    // Recalcula a altura do todos os nós entre a raiz e o novo nó inserido
    raiz->altura = Maior_altura(Altura_no(raiz->esquerda),Altura_no(raiz->direita) + 1);
    // Verifica se é necessario rebalanciar a ávore
    raiz = Balancear(raiz);
    return raiz;
}

no *Rotacao_esquerda(no *raiz){
    no *aux1 ,*aux2;// É criado duas variáveis auxiliare
    
    aux1 = raiz->direita; 
    aux2 = aux1->esquerda;

    aux1->esquerda = raiz;
    raiz->direita = aux2;

    raiz->altura = (Maior_altura(Altura_no(raiz->esquerda),Altura_no(raiz->direita)) + 1);
    aux1->altura = (Maior_altura(Altura_no(aux1->esquerda),Altura_no(aux1->direita)) + 1);

    return aux1;
}

no *Rotacao_direita(no *raiz){
    no *aux1 ,*aux2;

    aux1 = raiz->esquerda;
    aux2 = aux1->direita;

    aux1->direita = raiz;
    raiz->esquerda = aux2;

    raiz->altura = (Maior_altura(Altura_no(raiz->esquerda),Altura_no(raiz->direita)) + 1);
    aux1->altura = (Maior_altura(Altura_no(aux1->esquerda),Altura_no(aux1->direita)) + 1);

    return aux1;
}

no *Rotacao_esquerda_direita(no *raiz){
    raiz->esquerda = Rotacao_esquerda(raiz->esquerda);
    return Rotacao_direita(raiz);
}

no *Rotacao_direita_esquerda(no *raiz){
    raiz->direita = Rotacao_direita(raiz->direita);
    return Rotacao_esquerda(raiz);
}

// Essa função realiza o balanceamento da arvore após uma inserção ou remoção
no *Balancear(no *raiz){
    int fb = Fator_De_balaciamenro(raiz);
    // Rotção à esquerda
    if(fb < -1 && Fator_De_balaciamenro(raiz->direita) <= 0){
        raiz = Rotacao_esquerda(raiz);
        printf("esquerda s2imples");
    }
    // Rotação à direita 
    else if(fb > 1 && Fator_De_balaciamenro(raiz->esquerda) >=0){
        raiz = Rotacao_direita(raiz);
        printf("direira simples");
    }
    // Rotação dupla à esquerda
    else if(fb > 1 && Fator_De_balaciamenro(raiz->esquerda) < 0){
        raiz = Rotacao_esquerda_direita(raiz);
        printf("esquerda dupla");
    }
    // Rotação dupla à direita
    else if(fb < -1 && Fator_De_balaciamenro(raiz->direita) > 0){
        raiz = Rotacao_direita_esquerda(raiz);
        printf("direita dupla");
    }
    return raiz;
}

void Imprimir(no *raiz,int nivel){
    if(raiz == NULL){
        return;
    }
    Imprimir(raiz->esquerda, nivel + 1);
    printf("\n\n");

    for(int i = 0; i < nivel; i++){
        printf("\t");
    }

    printf("%d->", raiz->valor);
    Imprimir(raiz->direita, nivel + 1);
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
            Imprimir(raiz,1);
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