#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Shell_Sort(int array[],int n){
    for(int gap = n/2; gap > 0; gap/=2){
        for(int i = gap; i < n; i++){
            int temp = array[i];
            int j;

            for(j = i; j>=gap && array[j] < array[j - gap]; j-=gap){
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

int main(){
    srand (time(NULL));
    int n;
    printf("Digite o tamanho do seu vetor: ");
    scanf("%d",&n);

    int array[n];
    printf("\nVetor: ");
    for(int i = 0;i < n; i++){
        array[i] = rand() % 10 + 1;
        printf("[%d] ",array[i]);
    }

    printf("\nVetor ordenado: ");
    Shell_Sort(array,n);
    for(int i = 0; i < n; i++){
        printf("[%d] ",array[i]);
    }
    return 0;
}