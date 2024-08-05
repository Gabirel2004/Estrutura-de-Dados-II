#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));
  int tamanho;
  printf("Digite o tamanho do seu vetor:");
  scanf("%d",&tamanho);
  
  int array[tamanho];
  
  for(int i=0;i<tamanho;i++){
    array[i] = rand() % 10 + 1;
  }

  for(int i=0;i<tamanho;i++){
    printf("Vetor [ %d ] = %d\n",i,array[i]);
  }

  for(int i=0;i<tamanho;i++){
    for(int j=1;j<tamanho;j++){
      if(array[j - 1] > array[j]){
        int aux = array[j];
        array[j] = array[j - 1];
        array[j - 1] = aux;
      }
    }
  }
  printf("\n");
  for(int i=0;i<tamanho;i++){
    printf("Vetor ordenado [ %d ] = %d\n",i,array[i]);
  }
  return 0;
}