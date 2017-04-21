#include <bits/stdc++.h>

#define MAX_SIZE_ARRAY 140001

using namespace std;

int N;

int vetor[MAX_SIZE_ARRAY] = { 0 };

int cmpfunc (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}


int binary_serch(int valor){
	int esquerda = 0;
	int direita = N - 1;

	while(esquerda <= direita){
		int meio =  esquerda + (direita - esquerda) / 2;
		if(vetor[meio] == valor){
			return meio;
		}
		else if(vetor[meio] > valor){
			direita = meio - 1;
		}
		else{
			esquerda = meio + 1;
		}
	}

	return -1;
}

int main(){
	scanf("%d", &N);

	for(int i = 0; i < N; i++){
		scanf("%d", &vetor[i]);
	}

	qsort(vetor, N, sizeof(int), cmpfunc);

	while(true){		
		int valor;
		if(scanf("%d", &valor) == EOF) break;

		printf("%s\n", binary_serch(valor) != -1 ? "sim" : "nao");
	}

	return 0;
}