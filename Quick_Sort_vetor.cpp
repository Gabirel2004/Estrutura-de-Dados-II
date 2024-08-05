#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Partition(int array[],int left, int right){
    int pivo = array[right];
    int i = left - 1;
    for(int j = left; j < right; j++){
        if(array[j] <= pivo){
            i = i + 1;
            int aux = array[i];
            array[i] = array[j];
            array[j] = aux; 
        }
    }
    int aux = array[i + 1];
    array[i + 1] = array[right];
    array[right] = aux;
    return i + 1;
}

void Quick_Sort(int array[],int left, int right ){
    if(left <= right){
        int controle = Partition(array,left,right);
        Quick_Sort(array,left,controle - 1);
        Quick_Sort(array,controle + 1,right);
    }
}

int main(){
    int n;
    srand(time(NULL));
    printf("Digite o tamanho do seu vetor: ");
    scanf("%d",&n);

    int vetor[n];
    for(int i = 0;i < n; i++){
        vetor[i] = rand() % 10 + 1;
    }
    printf("Vetor: ");
    for(int i = 0; i < n; i++){
        printf(" [%d]",vetor[i]);
    }
    Quick_Sort(vetor,0,n-1);

    printf("Vetor: ");
    for(int i = 0; i < n; i++){
        printf(" [%d]",vetor[i]);
    }

    return 0;
}