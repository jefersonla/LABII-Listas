#include <iostream>
#include <stack>
#include <list>

#define MAX_NUM_VERTICES 2200
#define BRANCO 0
#define CINZA  1
#define PRETO  2

/* For each */
#define for_each(member,container) 	for(typeof(container.begin())   member  = container.begin();  \
									                                member != container.end();    \
                                                                    member ++ )

// APENAS PARA PROPOSITOS DE DEBUG
//#define DEBUG

using namespace std;

typedef struct VerticeStruct{
    int num;
    int cor;
    int tempo_f;
    int tempo_s; // Ou d
    struct VerticeStruct *anterior;
} Vertice;

list<int> grafo[MAX_NUM_VERTICES];
Vertice vertices[MAX_NUM_VERTICES];

/* Grafo transposto */
list<int> gr[MAX_NUM_VERTICES];

/* Tempo Global */
int tempo;

/* Variaveis do programa */
int N, M;

/* Pilha com a ordem de visitação */
stack<int> Q;

/* Contador de SCC */
int scc_count;

/* Visita os nós adjancentes, utilizando busca em profundidade */
void DFS_visit(Vertice V[MAX_NUM_VERTICES], Vertice *u){
    /* Atualiza o valor do tempo e indica que está sendo visitado */
    tempo += 1;
    u->tempo_s = tempo;
    u->cor = CINZA;

    #ifdef DEBUG
    cout << u->num << " ";
    #endif

    /* Para cada vértice adjacente a u */
    for_each(it, gr[u->num]){
        Vertice *v = &V[*it];

        /* Se o vertice ainda não tiver sido visitado */
        if(v->cor == BRANCO){
            v->anterior = u;
            DFS_visit(V, v);
        }
    }

    /* Finaliza a busca em profundidade do nó atual */
    u->cor = PRETO;
    tempo += 1;
    u->tempo_f = tempo;
}

/* Visita os nós adjancentes, utilizando busca em profundidade */
void DFS_visit_ordem(Vertice *u){
    /* Atualiza o valor do tempo e indica que está sendo visitado */
    tempo += 1;
    u->tempo_s = tempo;
    u->cor = CINZA;

    /* Para cada vértice adjacente a u */
    for_each(it, grafo[u->num]){
        Vertice *v = &vertices[*it];

        /* Se o vertice ainda não tiver sido visitado */
        if(v->cor == BRANCO){
            v->anterior = u;
            DFS_visit_ordem(v);
        }
    }

    /* Finaliza a busca em profundidade do nó atual */
    u->cor = PRETO;
    tempo += 1;
    u->tempo_f = tempo;

    /* Todos os nós que são acessiveis por u serão processados nesse momento */
    Q.push(u->num);
}

/* Computa os SCC ou seja os Strongly Conected Components do grafo global */
void SCC_kosaraju(){
    /* Toda vez que executarmos um DFS teremos que zerar o contador */
    tempo = 0;

    /* Executa uma DFS */
    /* Para cada vertice se o vertice ainda não tiver sido visitado executa uma
    busca em profundidade e computa seu tempo final de execução */
    for(int i = 1; i <= N; i++){
        if(vertices[i].cor == BRANCO){
            DFS_visit_ordem(&vertices[i]);
        }
    }

    /* Cria um grafo transposto ou reverso */
    Vertice V[MAX_NUM_VERTICES];

    /* Inicializamos os vertices V de gr */
    for(int i = 1; i <= N; i++){
        V[i].cor = BRANCO;
        V[i].anterior = NULL;
        V[i].num = i;
    }

    /* Enquanto Q não estiver vazio */
    tempo = 0;
    while(!Q.empty()){
        Vertice *u = &V[Q.top()];
        Q.pop();

        /* Se o vertice não tiver sido visitado ainda */
        if(u->cor == BRANCO){
            DFS_visit(V, u);

            /* Incrementa o numero de SCC */
            scc_count += 1;

            #ifdef DEBUG
            cout << endl;
            #endif
        }
    }
}

int main(){

    do{
        /* Lê as entradas */
        cin >> N;
        cin >> M;

        /* Se condição de parada da aplicação for atingida */
        if(N == 0 && M == 0)
        	break;

        /* Inicalização do grafo */
		scc_count = 0;
        for(int i = 1; i <= N; i++){
            /* Vertices */
            vertices[i].cor = BRANCO;
            vertices[i].anterior = NULL;
            vertices[i].num = i;

            /* Arestas */
			gr[i].clear();
			grafo[i].clear();
        }

        /* Lê as arestas */
        for(int i = 0; i < M; i++){
            int V, W, P;

            cin >> V;
            cin >> W;
            cin >> P;

            /* Se o nó tiver apenas o caminho de ida */
            grafo[V].push_back(W);

            /* Matriz transposta */
            gr[W].push_back(V);

            /* Caso o mesmo tenha também a volta -- grafo direcionado */
            if(P == 2){
                grafo[W].push_back(V);
            	gr[V].push_back(W);
            }
        }

        /* Executamos uma */
        SCC_kosaraju();

        /* Se tivermos apenas uma SCC então nosso grafo é fortemente conectado ou SCC */
        cout << (scc_count == 1 ? "1" : "0") << endl;

    	#ifdef DEBUG
        cout << "SCC = " << scc_count << endl;
        #endif

    }while(N != 0 && M != 0);

    return 0;
}
