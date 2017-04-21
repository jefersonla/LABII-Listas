#include <iostream>
#include <queue>
#include <list>
#include <limits>
#include <set>
#include <cmath>
#include <cstdio>

#define MAX_NUM_VERTICES 1001
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

/* Estrutura do grafo - arestas e vertices */
int grafo[MAX_NUM_VERTICES][MAX_NUM_VERTICES];
pair<long double, long double> vertices[MAX_NUM_VERTICES];

/* Matrizes do Floyd Warshall */
long double dist[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
int parente[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
int pai[MAX_NUM_VERTICES] = { 0 };

/* Variaveis do programa */
int N, M;

struct compare
{
    bool operator ()(const pair<pair<int, int>, int>&i, const pair<pair<int, int>, int>&j){
        return i.second <= j.second;
    };
};

/* Distância de u a v */
#define w(u, v) (dist[u][v])

/* Define a união dos parentes */
#define union(u, v) pai[u] = pai[v]

/* Retorna o valor máximo do set */
#define max_value_set(XX) XX.rbegin()->second

/* Procura o parente de um dado vértice */
int find_set(int v){
    if(v != pai[v])
        pai[v] = find_set(pai[v]);
    return pai[v];
}

/* Arvore geradora minima do Kruskal */
set<pair<pair<int,int>,long double>, compare> A;

long double Kruskal(){
    /* Pair de cordenadas e custo modelo: <<u,v>, custo>, e ordenamos o mesmo pelo custo */
    set<pair<pair<int,int>,long double>, compare> Q;

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
    long double soma = 0;
    for_each(it, Q){
        /* Pega os pares u e v da lista */
        int u = it->first.first;
        int v = it->first.second;

        /* Executa o find_set para os nós u e v */
        int find_set_u = find_set(u);
        int find_set_v = find_set(v);
        
        /* Se o pai de u for diferente do pai de v */
        if(find_set_u != find_set_v){
            A.insert(*it);
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
    long double x, y;
    int z = 1;

    while(true){
        cin >> N;

        if(N == 0)
            break;

        /* Inicalização do grafo */
        A.clear();
        for(int i = 1; i <= N; i++){
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
        for(int i = 1; i <= N; i++){
            /* Pega os valores de A e B*/
            cin >> x;
            cin >> y;

            vertices[i] = make_pair(x, y);
        }

        for(int u = 1; u <= N; u++){
            for(int v = 1; v <= N; v++){
                /* Como temos um grafo não direcionado os dois caminhos são válidos */
                grafo[u][v] += 1;
                grafo[v][u] += 1;

                /* Cordenadas de u */
                long double xu = vertices[u].first;
                long double yu = vertices[u].second;

                /* Coordenadas de v */
                long double xv = vertices[v].first;
                long double yv = vertices[v].second;

                /* Custo de u a v atual for maior que o custo novo substitui */
                long double w_u_v = sqrt(pow(xu-xv, 2) + pow(yu-yv, 2));
                dist[u][v] = w_u_v;
                dist[v][u] = w_u_v;

                /* Menor caminho de u a v */
                parente[u][v] = u;
                parente[v][u] = v;
            }
        }

        /* Iremos construir uma arvore geradora minima usando Kruskal, e
           retornar o custo do menor caminho entre todos os nós */
        long double retorno = Kruskal();

        /* Não estamos interessado no custo total mas sim no menor valor que garante que haja um caminho
           direto ou indireto entre todos os nós. Se só existe um nó então retornamos 0, caso exista mais
           que um retornamos o valor máximo da nossa Arvore Geradora Minima no caso o set de A */
        if(N == 1){
            printf("%.4f\n", 0.0);
        }
        else{
            printf("%.4Lf\n", max_value_set(A));
        }
    }

    return 0;
}
