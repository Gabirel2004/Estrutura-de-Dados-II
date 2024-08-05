#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Merge(int array[],int left,int middle, int right){

    int i, j, k;
    int tam1 = middle - left + 1;
    int tam2 = right - middle;

    int L[tam1], R[tam2];

    for(i = 0; i < tam1; i++){
        L[i] = array[left + i];
    }
    for(j = 0; j < tam2; j++){
        R[j] = array[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < tam1 && j < tam2){
        if(L[i] <= R[j]){
            array[k] = L[i];
            i++;
        }else{
            array[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < tam1){
        array[k] = L[i];
        i++;
        k++;
    }
    
    while (j < tam2)
    {
        array[k] = R[j];
        j++;
        k++;
    }    
}

void Merge_Sort(int array[],int left,int right ){
    if(left < right){
        int middle = (left + right)/2;
        Merge_Sort(array,left,middle);
        Merge_Sort(array,middle + 1, right);

        Merge(array,left,middle,right);
    }
}

int main()
{
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
    Merge_Sort(vetor,0,n-1);

    printf("\n\nVetor Ordenado: ");
    for(int i = 0; i < n; i++){
        printf(" [%d]",vetor[i]);
    }

    return 0;
}