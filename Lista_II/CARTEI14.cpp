#include <bits/stdc++.h>

#define MAX_SIZE_ARRAY 45001

using namespace std;

int N;

int vetor[MAX_SIZE_ARRAY] = { 0 };

int binary_serch(int esquerda, int direita, int valor){
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
	int M;

	scanf("%d %d", &N, &M);

	for(int i = 0; i < N; i++){
		scanf("%d", &vetor[i]);
	}

	int atual = 0;
	int soma = 0;

	for(int i = 0; i < M; i++){
		int valor;
		scanf("%d", &valor);

		int proxima_casa = binary_serch(0, N-1, valor);
		soma += proxima_casa > atual ? (proxima_casa - atual) : (atual - proxima_casa);
		//printf("%d - %d == %d\n", atual, proxima_casa, proxima_casa > atual ? (proxima_casa - atual) : (atual - proxima_casa));
		atual = proxima_casa;
	}

	printf("%d\n", soma);

	return 0;
}