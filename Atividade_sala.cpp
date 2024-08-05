#include <stdio.h>

#define MAX 100

typedef struct{
    int numeros[MAX];
    int quant = 0;
}Heap_struct;

Heap_struct heap;

void Troca(int a, int b){
    int temp = heap.numeros[a];
    heap.numeros[a] = heap.numeros[b];
    heap.numeros[b] = temp;
}

int Quem_eo_pai(int i){return (i - 1) / 2;}

int filho_l(int i){
    int indx = 2 * i + 1;
    if(indx >= heap.quant){
        return -1;
    }
    return indx;
}

int filho_r(int i){ 
    int indx = 2 * i + 2;
    if(indx >= heap.quant){
        return -1;
    }
    return indx;
}

void Ordenar_pai(int i){
    if(i == 0){printf("Vc esta na raiz\n"); return;}
    
    int indx_pai = Quem_eo_pai(i);

    int filho = heap.numeros[i];
    int pai = heap.numeros[indx_pai];

    if (filho <= pai) {
        printf("Parar pq o filho é menor que pai\n");
        return;
    }
    else{
        Troca(i,indx_pai);
        Ordenar_pai(indx_pai);
    }
}

void Ordenar_filhos(int i){
    int indx_filho1 = filho_l(i);
    if(indx_filho1 > 0){
        if(heap.numeros[i] < heap.numeros[indx_filho1]){
            Troca(i,indx_filho1);
            Ordenar_filhos(indx_filho1);
        }
    }
}

void inserir_heap(int num){
    if(heap.quant >= MAX){return;}

    heap.numeros[heap.quant] = num;
    heap.quant++;

    Ordenar_pai(heap.quant - 1);
}

int remover_heap(){
    if(heap.quant == 0){return -1;}

    int remover = heap.numeros[0];
    heap.quant--;
    Troca(0,heap.quant);

    return remover;
}

void printHeap() {
  printf("Quantidade: %d | ", heap.quant);
  for (int i = 0; i < heap.quant; i++) {
    printf("%d - ", heap.numeros[i]);
  }
  printf("fim\n");
}



int main(){
    inserir_heap(5);
    inserir_heap(3);
    inserir_heap(7);
    inserir_heap(8);
    inserir_heap(2);
    inserir_heap(10);

    printHeap();

    return 0;
}