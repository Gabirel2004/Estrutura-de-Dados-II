#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum Cor { VERMELHO, PRETO };

typedef struct node {
  int num;
  struct node *esq = NULL;
  struct node *dir = NULL;
  struct node *pai = NULL;
  Cor cor = VERMELHO;
} No;

No *buscar_no(No *node, int num);

No *irmao(No *filho);

void no_preto_irmao_preto_Filho_NULL(No **root,No *aRemover);

void no_preto_irmao_preto_Filho_Vermenho(No **root, No *aRemover);

void no_preto_irmao_vermelhor(No **root,No *aRemover);

bool eh_balanceada(No *node);

No *criar_no(int num = 0) {
  No *node = new No;
  if (num == 0) {
    node->num = rand() % 100;
  } else {
    node->num = num;
  }
  return node;
}

int altura(No *node) {
  if (node == NULL) return 0;
  if (node->cor == VERMELHO) {
    return fmax(altura(node->esq), altura(node->dir));
  }
  return 1 + fmax(altura(node->esq), altura(node->dir));
}

bool eh_folha(No *node) { return (node->esq == NULL) && (node->dir == NULL); }

void imprimir(No *node, int tab = 0) {
  if (node == NULL) return;

  imprimir(node->dir, tab + 1);
  for (int i = 0; i < tab; i++) {
    printf("\t");
  }
  char cor = (node->cor == VERMELHO) ? 'V' : 'P';
  printf("%c-%d\n", cor, node->num);

  imprimir(node->esq, tab + 1);
}

bool eh_filho_esq(No *filho) {
  No *pai = filho->pai;
  if (pai == NULL) return false;

  return (pai->esq == filho);
}

No *tio_no(No *node) {
  No *pai = node->pai;
  if (pai == NULL) return NULL;

  No *avo = pai->pai;
  if (avo == NULL) return NULL;

  if (eh_filho_esq(pai))
    return avo->dir;
  else
    return avo->esq;
}

No *maior(No *raiz){
    if(raiz == NULL){return NULL;}
    if(raiz->dir == NULL){return raiz;}
    return maior(raiz->dir);
}

void rotacao_esquerda(No **root, No *node){
    No *aux1 = node->dir;
    No *aux_pai = node->pai;
    // Atualiza a subarvore esquerda
    node->dir = aux1->esq;
    if (node->dir != NULL){
        node->dir->pai = node;
    }
    // Atualiza subárvore direita
    aux1->esq = node;
    node->pai = aux1;
    aux1->pai = aux_pai;
    // Atualiza raiz
    if (aux_pai == NULL){
        *root = aux1;
    } else {
        if (aux_pai->esq == node){
            aux_pai->esq = aux1;
        } else {
            aux_pai->dir = aux1;
        }
    }
}

void rotacao_direita(No **root, No *node){
    No *aux1 = node->esq;
    No *aux_pai = node->pai;
    // Atualiza a subarvore direita
    node->esq = aux1->dir;
    if (node->esq != NULL){
        node->esq->pai = node;
    }
    // Atualiza subárvore esquerda
    aux1->dir = node;
    node->pai = aux1;
    aux1->pai = aux_pai;
    // Atualiza raiz
    if (aux_pai == NULL){
        *root = aux1;
    } else {
        if (aux_pai->esq == node){
            aux_pai->esq = aux1;
        } else {
            aux_pai->dir = aux1;
        }
    }
}

void balanciar(No **raiz, No *filho){
    while ((filho != *raiz) && (filho->cor == VERMELHO) && (filho->pai->cor == VERMELHO)){
        No *pai = filho->pai;
        No *avo = pai->pai;
        
        // Verifica se precisamos corrigir a subárvore esquerda ou direita
        if (pai == avo->esq){
            No *tio = avo->dir;
            // Caso: Tio e Pai igual a vermelho
            if ((tio != NULL) && (tio->cor == VERMELHO)){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                filho = avo;
            } else {
                // Caso: Tio preto e Pai vermelho
                if (pai->dir == filho){
                    // Caso seja necessario rotação dupla
                    rotacao_esquerda(raiz, pai);
                    filho = pai;
                    pai = filho->pai;
                }
                rotacao_direita(raiz, avo);

                Cor aux_cor = pai->cor;
                pai->cor = avo->cor;
                avo->cor = aux_cor;

                filho = pai;
            }
        } else {
            // Corrige subárvore direita
            No *tio = avo->esq;
            // Caso: Tio e Pai igual a vermelho
            if ((tio != NULL) && (tio->cor == VERMELHO)){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                // Atualiza o While
                filho = avo;
            } else {
                // Caso: Tio preto e Pai vermelho
                if (pai->esq == filho){
                    // Caso seja necessario rotação dupla
                    rotacao_direita(raiz, pai);
                    // Atualiza o while;
                    filho = pai;
                    pai = filho->pai;
                }
                rotacao_esquerda(raiz, avo);
                
                Cor aux_cor = pai->cor;
                pai->cor = avo->cor;
                avo->cor = aux_cor;
                // Atualiza o While
                filho = pai;
            }
        }
    }
    (*raiz)->cor = PRETO; // A raiz sempre deve ser preta
}

void remover_no(No **root, int valor){
    if (root == NULL){
        return;
    }
    No *aRemover = *root;
    aRemover = buscar_no(aRemover,valor);
    if (aRemover == NULL){
      return;
    }
    // Tô Removendo um no que não tem filhos
    if (aRemover->esq == NULL && aRemover->dir == NULL){
      // Tô na raiz e ela vai ser removida
      if (aRemover->pai == NULL){
        free(aRemover);
        *root = NULL;
      }else{
        // Remover um no vermelho
        if (eh_folha(aRemover) && aRemover->cor == VERMELHO){
          // Caso o filho a ser removido esteja na esquerda
          if (eh_filho_esq(aRemover) == true){
            free(aRemover);
            aRemover->pai->esq = NULL;
          }else{
            //Caso o filho a ser removido esteja na direita
            free(aRemover);
            aRemover->pai->dir = NULL;
          }
          return;
        }else{//Remover filho preto
          No *irmao_no = irmao(aRemover);
          if (irmao_no == NULL) return;
          // Caso o irmao seja preto e sem filhos
          if (irmao_no->cor == PRETO && aRemover->cor == PRETO){
            
            if (eh_folha(irmao_no) == true){
              no_preto_irmao_preto_Filho_NULL(root,aRemover);
              free(aRemover);
              if (eh_filho_esq(aRemover) == true){
                aRemover->pai->esq = NULL;    
              }else{
                aRemover->pai->dir = NULL;
              }
            }
            // Caso o irmao seja preto e tenha filho vermenlho
            if (aRemover->cor == PRETO && irmao_no->cor == PRETO && ((irmao_no->esq != NULL && irmao_no->esq->cor == VERMELHO ) || (irmao_no->dir != NULL && irmao_no->dir->cor == VERMELHO))){
              no_preto_irmao_preto_Filho_Vermenho(root,aRemover);

            }
          }// Caso o irmao seja vermelho
          else if(aRemover->cor == PRETO && irmao_no->cor == VERMELHO){
              no_preto_irmao_vermelhor(root,aRemover);
          }
        }
      }
    }// Caso o no a ser removido tenha 1 filho

    else if (aRemover->esq == NULL || aRemover->dir == NULL){

      if (aRemover->esq != NULL){
        aRemover->num = aRemover->esq->num;
        free(aRemover->esq);
        aRemover->esq = NULL;
      }else{
        aRemover->num = aRemover->dir->num;
        free(aRemover->dir);
        aRemover->dir = NULL;
      }
    }// Caso o no a ser removido tenha 2 filhos
    else{
      No *substituto = maior(aRemover->esq);

      aRemover->num = substituto->num;
      substituto->pai->esq = substituto->esq;
      free(substituto);
    }
    (*root)->cor = PRETO;
}

void no_preto_irmao_preto_filho_preto_pai_preto_sobrinho_vermelho(No **root,No *aRemover){
  No *pai_aRemover = aRemover->pai;
  No *tio_aRemover = tio_no(aRemover);

  if (eh_filho_esq(tio_aRemover) == true){
    rotacao_direita(root,pai_aRemover->pai);
    if (tio_aRemover->esq != NULL)
      tio_aRemover->esq->cor = PRETO;
  }
  else{
    rotacao_esquerda(root,pai_aRemover->pai);
    if (tio_aRemover->dir != NULL)
      tio_aRemover->dir->cor = PRETO;
  }
}

void no_preto_irmao_preto_filho_preto_pai_preto(No **root,No *aRemover){
  No *pai_aRemover = aRemover->pai;
  No *tio_aRemover = tio_no(aRemover);


  if (tio_aRemover == NULL){return;}
   
  tio_aRemover->cor = VERMELHO;
  if ((tio_aRemover->esq != NULL && tio_aRemover->esq->cor == VERMELHO) || (tio_aRemover->dir != NULL && tio_aRemover->dir->cor == VERMELHO)){
    no_preto_irmao_preto_filho_preto_pai_preto_sobrinho_vermelho(root,aRemover);
  }
  
  pai_aRemover->pai->cor = PRETO;
}

void no_preto_irmao_preto_Filho_NULL(No **root,No *aRemover){
  No *pai_aRemover = aRemover->pai;
  No *irmao_aRemover = irmao(aRemover);

  if (pai_aRemover->cor == PRETO){
    no_preto_irmao_preto_filho_preto_pai_preto(root,aRemover);
  }
  pai_aRemover->cor = PRETO;
  irmao_aRemover->cor = VERMELHO;
}

void no_preto_irmao_preto_Filho_Vermenho(No **root, No *aRemover){
  No *pai_aRemover = aRemover->pai;
  No *irmao_aRemover = irmao(aRemover);

  if (eh_filho_esq(aRemover) == true){
    free(aRemover);
    aRemover->pai->esq = NULL;
  }else{
    free(aRemover);
    aRemover->pai->dir = NULL;
  }

  if (pai_aRemover->esq == NULL){
    rotacao_esquerda(root,pai_aRemover);
    if (pai_aRemover->cor == PRETO)
      irmao_aRemover->dir->cor = PRETO;
  }else{
    printf("jfiji");
    rotacao_direita(root,pai_aRemover);
    if (pai_aRemover->cor == PRETO)
      irmao_aRemover->esq->cor = PRETO;
  } 

}

void no_preto_irmao_vermelhor(No **root, No *aRemover){
  No *pai_aRemover = aRemover->pai;
  No *irmao_aRemover = irmao(aRemover);

  if (eh_filho_esq(aRemover) == true){
    free(aRemover);
    aRemover->pai->esq = NULL;
  }else{
    free(aRemover);
    aRemover->pai->dir = NULL;
  }

  if (pai_aRemover->esq == NULL){
    rotacao_esquerda(root,pai_aRemover);
    irmao_aRemover->cor = PRETO;
    if (pai_aRemover->dir != NULL)
      pai_aRemover->dir->cor = VERMELHO;
  }else{
    rotacao_direita(root,pai_aRemover);
    irmao_aRemover->cor = PRETO;
    if (pai_aRemover->esq != NULL)
      pai_aRemover->esq->cor = VERMELHO;
  } 
}

void inserir_no(No **root, No *node, No *novo) {
    if (node == NULL) {
      printf("Erro\n");
      return;
    }

    if (node->num == novo->num) {
      printf("Numero ja existe\n");
      return;
    }

    if (node->num < novo->num) {
      if (node->dir == NULL) {
        node->dir = novo;
        novo->pai = node;
        balanciar(root,novo);
        return;
      }
      inserir_no(&(*root),node->dir, novo);
    } else {
      if (node->esq == NULL) {
        node->esq = novo;
        novo->pai = node;
        balanciar(root,novo);
        return;
      }
      inserir_no(&(*root),node->esq, novo);
    }
}

void inserir_raiz(No **raiz, No *node) {
  if (*raiz == NULL) {
    *raiz = node;
    (*raiz)->cor = PRETO;
    (*raiz)->pai = NULL;
    return;
  }
  inserir_no(&(*raiz),*raiz, node);
}

No *buscar_no(No *node, int num) {
  if (node == NULL) {
    printf("Numero nao encontrado\n");
    return NULL;
  }

  if (node->num == num) {
    return node;
  }

  if (node->num < num) {
    return buscar_no(node->dir, num);
  } else {
    return buscar_no(node->esq, num);
  }
}

void menu() {
  printf("\nMENU\n");
  printf("1-Inserir\n");
  printf("2-Imprimir Arvore\n");
  printf("3-Altura arvore\n");
  printf("4-Altura de um no\n");
  printf("5-Remover\n");
  printf("6-E balanciada?\n");
  printf("0-Sair\n");
}

No *irmao(No *filho) {
  No *pai = filho->pai;
  if (pai == NULL) return NULL;

  return (pai->esq == filho) ? pai->dir : pai->esq;
}

bool eh_balanceada(No *node) {
  if (node == NULL) return true;

  if (altura(node->esq) != altura(node->dir)) {
    return false;
  } else {
    return (eh_balanceada(node->esq) && eh_balanceada(node->dir));
  }
}

int main() {
  srand(time(NULL));

  No *root = NULL;
  No *node = NULL;
  int num;

  for (int i = 1; i <= 20; i++) {
    node = criar_no(i);
    inserir_raiz(&root, node);
  }

  int opc = 1;

  while (opc != 0) {
    menu();
    printf("Escolha uma opicao: ");
    scanf("%d", &opc);
    switch (opc) {
      case 1:
        // node = criar_no();
        // printf("Inserindo num: %d\n", node->num);
        printf("Digite o valor a ser inserido: ");
        scanf("%d",&num);
        node = criar_no(num);
        inserir_raiz(&root, node);
        break;
      case 2:
        imprimir(root);
        printf("========\n");
        break;
      case 3:
        printf("Altura preta: %d\n", altura(root));
        break;
      case 4:
        printf("Insira o valor do no a ser procurado: ");
        scanf("%d", &num);
        node = buscar_no(root, num);
        (node == NULL) ? printf("No inexistente\n")
                       : printf("Altura do no: %d\n", altura(node));
        break;
      case 5:
        printf("Insira o valor do no a ser removido: ");
        scanf("%d", &num);
        remover_no(&root,num);
        break;
      case 6:
        printf("Balanceada: %d\n", eh_balanceada(root));
        break;
      default:
        printf("Opcao invalida\n");
        break;
    }
  }
  return 0;
}