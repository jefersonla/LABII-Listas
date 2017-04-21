#include <bits/stdc++.h>

#define MAX_SIZE_ARRAY 100001

using namespace std;

long long N;

long long vetor[MAX_SIZE_ARRAY] = { 0 };

long long binary_serch(long long valor){
	long long esquerda = 0;
	long long direita = N - 1;

	long long meio = 0;

	while(esquerda <= direita){
		meio =  esquerda + (direita - esquerda) / 2;
		if(vetor[meio] == valor){
			break;
		}
		else if(vetor[meio] > valor){
			direita = meio - 1;
		}
		else{
			esquerda = meio + 1;
		}
	}

	if(vetor[meio] == valor){
		for(int i = meio; i >= 0; i--){
			if(i == 0 && vetor[0] == valor){
				return 0;
			}
			else if(i > 0 && vetor[i - 1] != valor){
				return i;
			}
		}
	}

	return -1;
}

int main(){
	long long Q;
	
	scanf("%lld %lld", &N, &Q);

	for(long long i = 0; i < N; i++){
		scanf("%lld", &vetor[i]);
	}

	for(long long i = 0; i < Q; i++){
		long long valor;
		scanf("%lld", &valor);

		printf("%lld\n", binary_serch(valor));
	}

	return 0;
}