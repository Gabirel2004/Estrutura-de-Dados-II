#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int conteudo;
    struct No *prox;
} no;

no *Meddle(no *hend, no *last){
    if(hend == NULL){
        return NULL;
    }
    no *slow = hend;
    no *fast = hend->prox;

    while (fast != last && fast->prox != last) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    return slow;
}

bool Busca_Binaria(no *hend, int valor){
    if(hend == NULL){
        return false;
    }
    no *strat = hend;
    no *last= NULL;
    do{
        no *meddle = Meddle(strat,last);

        if(meddle == NULL){
            return false;
        }
        if(meddle->conteudo == valor){
            return true;
        }else if(meddle->conteudo < valor){
            strat = meddle->prox;
        }else{
            last = meddle;
        }
    }while(last == NULL || last != strat);
    return false;
}

void Insert_Sort(no **hend) {
    no *next = (no*)malloc(sizeof(no));
    if (next != NULL) {
        printf("Digite o valor a ser inserido na lista: ");
        scanf("%d", &next->conteudo);

        if (*hend == NULL || (*hend)->conteudo > next->conteudo) {
            next->prox = *hend;
            *hend = next;
        } else {
            no *aux = *hend;
            while (aux->prox != NULL && aux->prox->conteudo < next->conteudo) {
                aux = aux->prox;
            }
            next->prox = aux->prox;
            aux->prox = next;
        }
    } else {
        printf("Erro de alocacao de memoria!!!\n");
    }
}

void Print(no *hend) {
    no *aux = hend;
    printf("Lista: ");
    while (aux != NULL) {
        printf("%d->",aux->conteudo);
        aux = aux->prox;
    }
    printf("NULL\n\n");
}

int main() {
    no *hend = NULL;
    int op, valor;
    do {
        printf("0 - Sair\n");
        printf("1 - Inserir valor\n");
        printf("2 - Imprimir dados\n");
        printf("3 - Busca Binaria\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                Insert_Sort(&hend);
                break;
            case 2:
                Print(hend);
                break;
            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                if (Busca_Binaria(hend, valor))
                    printf("Valor encontrado!\n");
                else
                    printf("Valor nao encontrado!\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("\nEscolha uma opcao valida!\n");
                break;
        }

    } while (op != 0);

    return 0;
}
