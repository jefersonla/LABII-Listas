#include <bits/stdc++.h>
using namespace std;

/* Constantes do algoritmo */
#define MAX_NUM_VERTICES 120
#define BRANCO 0
#define CINZA  1
#define PRETO  2

/* For each */
#define for_each(member,container)  for(typeof(container.begin())   member  = container.begin(); \
                                                                    member != container.end();   \
                                                                    member ++ )


/* Verifica a existência */
#define is_none(var)        (var == NULL)
#define is_not_none(var)    (var != NULL)

/* Valor infinito */
#define INFINITY_VALUE 9999999
            
/* Indice nulo */
#define NULO -1

/* Ativar apenas durante o DEBUG */
//#define DEBUG

typedef struct VerticeStruct{
    int num;
    int cor;
    int d;
    int tempo_s;
    int tempo_f;
    struct VerticeStruct *anterior;
} Vertice;

int N, M;

#define MAX_NUM_VERTICES 120

int distk[MAX_NUM_VERTICES][MAX_NUM_VERTICES][MAX_NUM_VERTICES];

/* Floyd Warshall */
void FloydWarshall(){
    /* Executa o algoritmo de Floyd Warshall e computa as distancias */
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                distk[i][j][k] = min(distk[i - 1][j][k], distk[i - 1][j][i - 1] + distk[i - 1][i - 1][k]);
            }
        }
    }
}

int main(){
	
	int inst = 1;

	while(true){

		/* Le os valores */
		if(scanf("%d %d", &N, &M) == EOF){
			break;
		}

		/* Inicializa os valores da distancia */
		for(int i = 0; i <= N; i++){
			for(int j = 0; j <= N; j++){
				for(int k = 0; k <= N; k++){
					if(j == k){
						distk[i][j][k] = 0;
					}
					else{
						distk[i][j][k] = INFINITY_VALUE;
					}
				}
			}
		}

		/* Le as arestas */
		for(int i = 0; i < M; i++){
			int u, v, w;
			cin >> u >> v >> w;
			distk[0][u - 1][v - 1] = min(distk[0][u - 1][v - 1], w);
		}

		/* Executa Floyd Warshal modificado para salvar as instancias k */
		FloydWarshall();

		int n_testes;
		cin >> n_testes;

		cout << "Instancia "<< inst << endl;

		/* Executa os testes */
		for(int i = 0; i < n_testes; i++){
			int u, v, t;
			cin >> u >> v >> t;
			if(distk[t][u - 1][v - 1] == INFINITY_VALUE){
				cout << "-1" << endl;
			}
			else{
				cout << distk[t][u - 1][v - 1] << endl;
			}
		}
		cout << endl;

		inst++;
	}

	return 0;
}