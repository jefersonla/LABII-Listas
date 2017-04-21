#include <iostream>
#include <queue>
#include <list>
#include <limits>
#include <set>

#define MAX_NUM_VERTICES 101
#define BRANCO 0
#define CINZA  1
#define PRETO  2

/* For each */
#define for_each(member,container)  for(typeof(container.begin())   member  = container.begin(); \
                                                                    member != container.end();   \
                                                                    member ++ )

/* better find */
#define not_found_in(var)   var.end()

/* Max value between two vars */
#define max_2(var1, var2)     (var1 > var2 ? var1 : var2)
#define min_2(var1, var2)     (var1 < var2 ? var1 : var2)

/* Verifica a existência */
#define is_none(var)        (var == NULL)
#define is_not_none(var)    (var != NULL)

/* Valor infinito */
#define INFINITY_VALUE std::numeric_limits<int>::max()
            
/* Indice nulo */
#define NULO -1

// APENAS PARA PROPOSITOS DE DEBUG
//#define DEBUG

using namespace std;

typedef struct VerticeStruct{
    int num;
    int cor;
    struct VerticeStruct *anterior;
} Vertice;

/* Estrutura do grafo - arestas e vertices */
int grafo[MAX_NUM_VERTICES][MAX_NUM_VERTICES];
Vertice vertices[MAX_NUM_VERTICES];

/* Matrizes do Floyd Warshall */
int dist[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
int custo[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
int parente[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
int pai[MAX_NUM_VERTICES] = { 0 };

/* Variaveis do programa */
int N, M;

/* Floyd Warshall */
void FloydWarshall(){
    /* Executa o algoritmo de Floyd Warshall e computa as distancias */
    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if( dist[i][k] != INFINITY_VALUE &&
                    dist[k][j] != INFINITY_VALUE &&
                    (dist[i][k] + dist[k][j] < dist[i][j])){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parente[i][j] = k;
                }
            }
        }
    }

    #ifdef DEBUG
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if (dist[i][j] == INFINITY_VALUE){
                printf("%7s", "INF");
            }
            else{
                printf ("%7d", dist[i][j]);
            }
        }
        cout << '\n';
    }
    cout << '\n';
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if (parente[i][j] == NULO){
                printf("%7s", "NIL");
            }
            else{
                printf ("%7d", parente[i][j]);
            }
        }
        cout << '\n';
    }
    cout << '\n';
    #endif
}

struct compare
{
    bool operator ()(const pair<pair<int, int>, int>&i, const pair<pair<int, int>, int>&j){
        return i.second <= j.second;
    };
};


struct compare2
{
    bool operator ()(const pair<pair<int, int>, int>&i, const pair<pair<int, int>, int>&j){
        if(i.first.first != j.first.first)
            return (i.first.first < j.first.first);
        return (i.first.second < j.first.second);
    };
};

/* Distância de u a v */
#define w(u, v) (dist[u][v])

/* Define a união dos parentes */
#define union(u, v) pai[u] = pai[v]

/* Procura o parente de um dado vértice */
int find_set(int v){
    if(v != pai[v])
        pai[v] = find_set(pai[v]);
    return pai[v];
}

/* Arvore geradora minima do Kruskal */
set<pair<pair<int,int>,int>, compare2> A;

int Kruskal(){
    /* Pair de cordenadas e custo modelo: <<u,v>, custo>, e ordenamos o mesmo pelo custo */
    set<pair<pair<int,int>,int>, compare> Q;

    /* Insere no set a lista de pares e custo */
    for(int u = 1; u <= N; u++){
        for(int v = 1; v <= N; v++){
            if(grafo[u][v] != 0){
                Q.insert(make_pair(make_pair(u, v), w(u,v)));
#ifdef DEBUG
                cout << "u -- " << u << " | v -- " << v << " | w -- " << w(u,v) << endl;
#endif                
            }
        }
    }

#ifdef DEBUG
    /* Imprime todos os nós - deve estar ordenado pelo peso */
    cout << "Todas arestas" << endl;
    for_each(it, Q){
        int u = it->first.first;
        int v = it->first.second;
        int w = it->second;
        cout << "u " << u << " v " << v << " w " << w << endl;   
    }
#endif

    /* While n of nodes is different of 0 */
    int n_nodes = 0;
    int soma = 0;
    for_each(it, Q){
        /* Pega os pares u e v da lista */
        int u = it->first.first;
        int v = it->first.second;

        /* Executa o find_set para os nós u e v */
        int find_set_u = find_set(u);
        int find_set_v = find_set(v);
        
        /* Se o pai de u for diferente do pai de v */
        if(find_set_u != find_set_v){
            /* Inserimos os valores de u, v e w ordenado */
            int u_aux = it->first.first;
            int v_aux = it->first.second;
            int w_aux = it->second;

            /* Verificamos se u < v */
            if(u_aux < v_aux){
                A.insert(make_pair(make_pair(u_aux, v_aux), w_aux));
            }
            else{
                A.insert(make_pair(make_pair(v_aux, u_aux), w_aux));
            }

            /* Adiciona o custo final e une os elementos */
            soma += it->second;
            union(find_set_u, find_set_v);
        }

        /* Se já temos nossa arvore geradora minima paramos a execução */
        if(A.size() == (N - 1)){
            break;
        }
    }

#ifdef DEBUG
    /* Imprime todos os nós da nossa arvore geradora minima */
    cout << "Arvore geradora minima" << endl;
    for_each(it, A){
        int u = it->first.first;
        int v = it->first.second;
        int w = it->second;
        cout << "u " << u << " v " << v << " w " << w << endl;   
    }
#endif

    return soma;
}

int main(){
    int U, V, C;
    int z = 1;

    do{
        /* Lê as entradas */
        cin >> N;
        cin >> M;

        if(N == 0 && M == 0)
            break;

        /* Inicalização do grafo */
        A.clear();
        for(int i = 1; i <= N; i++){
            /* Vertices */
            vertices[i].cor = BRANCO;
            vertices[i].anterior = NULL;
            vertices[i].num = i;

            /* Arestas & Distâncias & Caminho */
            for(int j = 1; j <= N; j++){
                dist[i][j] = INFINITY_VALUE;
                grafo[i][j] = 0;
                parente[i][j] = NULO;
            }

            /* Distâncias & Parentes na Diagonal */
            dist[i][i] = 0;
            parente[i][i] = i;
            pai[i] = i;
        }

        /* Lê as arestas */
        for(int i = 0; i < M; i++){
            /* Pega os valores de A e B*/
            cin >> U;
            cin >> V;
            cin >> C;

            /* Como temos um grafo não direcionado os dois caminhos são válidos */
            grafo[U][V] += 1;
            grafo[V][U] += 1;

            /* Custo de U a V */
            dist[U][V] = C;
            dist[V][U] = C;

            /* Menor caminho de U a V */
            parente[U][V] = U;
            parente[V][U] = V;
        }

        if(z > 1){
            cout << endl;
        }

        /* Iremos construir uma arvore geradora minima usando Kruskal, e
           retornar o custo do menor caminho entre todos os nós */
        int retorno = Kruskal();

        cout << "Teste " << z << endl;
        for_each(it, A){
            int u = it->first.first;
            int v = it->first.second;
            if(u < v){
                cout << u << " " << v << endl;   
            }
            else{
                cout << v << " " << u << endl;   
            }
        }
        
        /* Incrementamos o numero de testes executados */
        z += 1;
    } while(true);

    return 0;
}
