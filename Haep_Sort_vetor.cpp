#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Metodo que faz a troca
void Troca(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Mini_Heap(int array[], int n, int i){
    int menor = i;

    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    
    //Verifica se o valor a esquerda e menor que o da raiz
    if(l <= n && array[l] < array[menor]){
        menor = l;
    }
    //verifica se o valor a direita e maiot que a raiz
    if(r <= n && array[r] < array[menor]){
        menor = r;
    }

    if(menor != i){
        //Faz a troca
        Troca(&array[i],&array[menor]);
        Mini_Heap(array,n,menor);
    }
}

void Max_Heap(int array[], int n, int i){
    int maior = i;

    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    
    //Verifica se o valor a esquerda e maior que o da raiz
    if(l < n && array[l] > array[maior]){
        maior = l;
    }
    //verifica se o valor a direita e maiot que a raiz
    if(r < n && array[r] > array[maior]){
        maior = r;
    }

    if(maior != i){
        //Faz a troca
        Troca(&array[i],&array[maior]);
        Max_Heap(array,n,maior);
    }
}
//Construir a Heap
void Builb_Heap(int array[], int n){
    //Índice do último nó não-folha
    int strat = (n/2) - 1;

    for(int i = strat; i >= 0; i--){
        Mini_Heap(array, n, i);
    }
}

void Heap_Sort(int array[], int n){
    Builb_Heap(array,n);
    for(int i = n - 1; i >=0; i--){
        Troca(&array[0],&array[i]);
        Mini_Heap(array,n,0);
    }
}

void printHeap(int array[], int n){
    for (int i = 0; i < n; ++i)
        printf("%d ",array[i]);
    printf("\n\n");
}

int main(){
    srand (time(NULL));
    int n;
    printf("Digite o tamanho do seu vetor: ");
    scanf("%d",&n);

    int array[n];
    printf("\nVetor nao ordenado: ");
    for(int i = 0; i < n; i++){
        array[i] = rand() % 10 + 1;
    }
    printHeap(array,n);

    Heap_Sort(array,n);
    printf("Vetor ordenado: ");
    printHeap(array,n);

    return 0;
}