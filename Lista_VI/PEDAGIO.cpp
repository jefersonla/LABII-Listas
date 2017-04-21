#include <iostream>
#include <queue>
#include <limits>

#define INFINITY_VALUE std::numeric_limits<int>::max()
#define MAX_NUM_VERTICES 51
#define UNDEFINED_VERTICE -1

/* Como a distância é fixa entre os nós distancia de u a v é 1 */
#define distancia(u,v) 1

using namespace std;

typedef struct VerticeStruct{
	int num;
	int distancia;
	int anterior;
} Vertice;

int grafo[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{0}};
int menor_caminho[MAX_NUM_VERTICES];
Vertice vertices[MAX_NUM_VERTICES];

int C, L, E, P;

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
		for(int i = 1; i <= C; i++){
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
	int K = 1;

	do{
		/* Lê os quatro inteiros */
		cin >> C;
		cin >> E;
		cin >> L;
		cin >> P;

		/* Se condição de parada de execução for atingida */
		if((C == 0) && (E == 0) && (L == 0) && (P == 0)){
			break;
		}

		/* Inicialização dos vertices e arestas */
		for (int i = 1; i <= C; i++){
			for (int j = 1; j <= C; j++){
				grafo[i][j] = 0;
			}

			vertices[i].num = i;
			vertices[i].distancia = INFINITY_VALUE;
			vertices[i].anterior = UNDEFINED_VERTICE;
		}

		/* Sabemos que L é a cidade aonde estamos logo inicializamos esta distância */
		vertices[L].distancia = 0;

		/* Lê toda a entrada */
		for(int i = 0; i < E; i++){
			int O, D;
			cin >> O;
			cin >> D;
			grafo[O][D] += 1;
			grafo[D][O] += 1;
		}

		/* Agora iremos encontrar o melhor caminho de L até todos os nós adjacentes a L */
		dijkstra();

		if(K > 1){
			cout << endl;
		}

		cout << "Teste " << K << endl;

		/* Após descobrir o melhor caminho a partir de L iremos varrer todos os vértices
		e printar o menor caminho ou seja o caminho com no máximo P de distância */
		bool primeiro_elemento = true;
		for(int i = 1; i <= C; i++){
			Vertice *v = &vertices[i];
			if(v->num != L && v->distancia <= P){
				if(primeiro_elemento){
					cout << v->num;
					primeiro_elemento = false;
				}
				else{
					cout << " " << v->num;
				}
			}
		}

		/* Quebra a linha do caminho apresentado */
		cout << endl;
		K += 1;

	} while((C != 0) && (E != 0) && (L != 0) && (P != 0));

	return 0;
}