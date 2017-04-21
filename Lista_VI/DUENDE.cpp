#include <bits/stdc++.h>

#define INFINITY_VALUE std::numeric_limits<int>::max()
#define MAX_NUM_VERTICES (10 * 10 + 1)
#define UNDEFINED_VERTICE -1

/* Como a distância é fixa entre os nós distancia de u a v é 1 */
#define distancia(u,v) 1

using namespace std;

typedef struct VerticeStruct{
	int num;
	int distancia;
	int anterior;
} Vertice;

/* For each */
#define for_each(member,container) 	for(typeof(container.begin())   member  = container.begin();  \
									                                member != container.end();    \
                                                                    member ++ )

int grafo[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{0}};
int menor_caminho[MAX_NUM_VERTICES];
Vertice vertices[MAX_NUM_VERTICES];

int N, L, M, T;

list<int> saidas;

int mapa[11][11] = {{ 0 }};


void dijkstra(){
	/* Criamos uma fila de prioridades */
	priority_queue<pair<int, int> > Q;

	/* Adicionamos o vértice de origem */
	Q.push(make_pair(0, L));

	/* Enquanto nossa fila não estiver vazia */
	while(!Q.empty()){
		/* Extraimos o menor vertice de nossa fila */
		Vertice *u = &vertices[Q.top().second];
		Q.pop();

		/* Para cada vizinho v de u */
		for(int i = 0; i < T; i++){
			Vertice *v = &vertices[i];
			/* Se o vertice u é vizinho de v */
			if(grafo[u->num][v->num] > 0){
				/* Some a distancia de u com a distancia de u a v
				como temos que a distância é fixa, ela é igual a 1 */
				int alternativa = u->distancia + distancia(u, v);
				/* Se o novo caminho for o melhor caminho armazene ele */
				if (alternativa < v->distancia){
					v->distancia = alternativa;
					v->anterior = u->num;
					Q.push(make_pair(v->distancia, v->num));
				}
			}
		}
	}
}

int main(){

	/* Lê os quatro inteiros */
	cin >> N;
	cin >> M;

	/* Total de vertices */
	T = N * M;

	/* Inicialização dos vertices e arestas */
	saidas.clear();
	for (int i = 0; i < T; i++){
		for (int j = 0; j < T; j++){
			grafo[i][j] = 0;
		}

		vertices[i].num = i;
		vertices[i].distancia = INFINITY_VALUE;
		vertices[i].anterior = UNDEFINED_VERTICE;
	}

	/* Lê todo o mapa */
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			int tipo;
			cin >> tipo;
			mapa[i][j] = tipo;

			if(tipo == 3){
				L = (i * M) + j;
			}
			else if(tipo == 0){
				saidas.push_back((i * M) + j);
			}
		}
	}
	
	/* Constroi o grafo com o mapa recebido */
	for(int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			if(mapa[i][j] != 2){
				int lugar_atual = (i * M) + j;

				if((i + 1) < N && mapa[i + 1][j] != 2){
					grafo[lugar_atual][lugar_atual + M] = 1;
					grafo[lugar_atual + M][lugar_atual] = 1;
				}
				if((j + 1) < M && mapa[i][j + 1] != 2){
					grafo[lugar_atual][lugar_atual + 1] = 1;
					grafo[lugar_atual + 1][lugar_atual] = 1;
				}
			}
		}
	}

	/* Sabemos que L é a cidade aonde estamos logo inicializamos esta distância */
	vertices[L].distancia = 0;

	/* Agora iremos encontrar o melhor caminho de L até todos os nós adjacentes a L */
	dijkstra();

#ifdef DEBUG
	cout << endl;
	for(int i = 0; i < T; i++){
		for(int j = 0; j < T; j++){
			printf("%5d", grafo[i][j]);
		}
		cout << endl;
	}
	cout << endl << endl;

	for(int i = 0; i < T; i++){
		printf("%s%d: %d\n", ((find(saidas.begin(), saidas.end(), i) != saidas.end()) ? "*" : ""), i, vertices[i].distancia);
	}
	cout << endl;
#endif

	/* Após descobrir o melhor caminho a partir de L iremos varrer todos as saídas possíveis
	   e printar a distância para o melhor caminho */
	int menor_caminho = INFINITY_VALUE;
	for_each(it, saidas){
		Vertice *v = &vertices[*it];
		if(v->num != L && v->distancia <= menor_caminho){
			menor_caminho = v->distancia;
		}
	}

	/* Imprime o resultado */
	cout << menor_caminho << endl;

	return 0;
}