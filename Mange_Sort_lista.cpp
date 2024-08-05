#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No{
    int data;
    struct No* next;
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

void find_meddle(no *hend,no **font,no **back){
    no *slow = hend;
    no *fast = hend->next;
    while(fast != NULL){
        fast = fast->next;
        if(fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *font = hend;
    *back = slow->next;
    
    slow->next = NULL;
}

no *Mange(no *left,no *right){
    if(left == NULL){
        return right;
    }
    if(right == NULL){
        return left;
    }
    no *resut = NULL;
    if(left->data <= right->data){
        resut = left;
        resut->next = Mange(left->next,right);
    }else{
        resut = right;
        resut->next = Mange(left,right->next);
    }
    return resut;
}


void Mange_Sort(no **hend){
    no *hend_ref = *hend;
    no *front;
    no *back;
    if(hend_ref == NULL || hend_ref->next == NULL){
        return;
    }
    find_meddle(hend_ref,&front,&back);
    Mange_Sort(&front);
    Mange_Sort(&back);

    *hend = Mange(front,back);
}

int main() {
    int n;
    srand(time(NULL));
    printf("Digite o tamanho da lista: ");
    scanf("%d", &n);
    no *hend = NULL;

    Insert_Inicio(&hend,n);

    Print(hend);

    Mange_Sort(&hend);

    Print(hend);
    
    return 0;
}
