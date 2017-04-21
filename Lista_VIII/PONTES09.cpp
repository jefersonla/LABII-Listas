#include <bits/stdc++.h>

#define INFINITY_VALUE std::numeric_limits<int>::max()
#define MAX_NUM_VERTICES 1002
#define UNDEFINED_VERTICE -1

/* Distância de u a v */
#define distancia(u,v) v

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

#define NAO_VISITADO 0
#define VISITANDO 1
#define VISITADO 2

Vertice vertices[MAX_NUM_VERTICES];
vector<pair<int, int> > grafo[MAX_NUM_VERTICES];
vector<int> menor_caminho;

int N, M, L = 0;

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
		for(int vi = 0; vi < grafo[u->num].size(); vi++){
			/* Vertice V */
			int v = grafo[u->num][vi].first; 
			int v_peso = grafo[u->num][vi].second;

			/* Some a distancia de u com a distancia de u a v
			como temos que a distância é fixa, ela é igual a 1 */
			int alternativa = u->distancia + v_peso;
			/* Se o novo caminho for o melhor caminho armazene ele */
			if (alternativa < vertices[v].distancia){
				vertices[v].distancia = alternativa;
				vertices[v].anterior = u->num;
				Q.push(make_pair(vertices[v].distancia, vertices[v].num));	
			}
		}
	}
}

int main(){

	cin >> N >> M;

	for(int i = 0; i <= N + 1; i++){
		grafo[i].clear();
		vertices[i].num = i;
		vertices[i].distancia = INFINITY_VALUE;
		vertices[i].anterior = UNDEFINED_VERTICE;
	}

	for(int i = 0; i < M; i++){
		int S, T, B;

		cin >> S >> T >> B;

		grafo[S].push_back(make_pair(T, B));
		grafo[T].push_back(make_pair(S, B));
	}

	/* Destino a ser alcançado */
	int destino = N + 1;

	vertices[0].distancia = 0;

	dijkstra();

	cout << vertices[destino].distancia << endl;

	return 0;
}