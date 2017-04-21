#include <iostream>
#include <cstdio>
#include <limits>

/* Constantes do algoritmo */
#define MAX_NUM_VERTICES 120
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

/* Ativar apenas durante o DEBUG */
//#define DEBUG

using namespace std;

typedef struct VerticeStruct{
    int num;
    int cor;
    int d;
    int tempo_s;
    int tempo_f;
    struct VerticeStruct *anterior;
} Vertice;

/* Estrutura do grafo - arestas e vertices */
int grafo[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
int dist[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
int parente[MAX_NUM_VERTICES][MAX_NUM_VERTICES] = {{ 0 }};
Vertice vertices[MAX_NUM_VERTICES];

/* Tempo Global */
int tempo;

/* Variaveis do programa */
int N;

/* Floyd Warshall */
int FloydWarshall(){
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

    /* Inicia a menor distância entre todos os nós como sendo o infinito */
    int menor_distancia = INFINITY_VALUE;
    int vertice_menor_distancia = 1;

    for(int u = 1; u <= N; u++){
        int distancia = 0;
        for(int v = 1; v <= N; v++){
            distancia = max_2(distancia, dist[u][v]);
        }
        if(distancia < menor_distancia){
            menor_distancia = distancia;
            vertice_menor_distancia = u;
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

    return vertice_menor_distancia;
}


int main(){
    int z = 1;

    /* CIN Improvements */
    //ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    do{
        /* Lê as entradas */
        cin >> N;

        /* Se condição de parada da aplicação for atingida */
        if(N == 0)
            break;

        /* Inicalização do grafo */
        tempo = 0;
        for(int i = 1; i <= N; i++){
            /* Vertices */
            vertices[i].cor = BRANCO;
            vertices[i].num = i;
            vertices[i].anterior = NULL;

            /* Arestas & Distâncias & Caminho */
            for(int j = 1; j <= N; j++){
                grafo[i][j] = 0;
                dist[i][j] = INFINITY_VALUE;
                parente[i][j] = NULO;
            }
            
            /* Distâncias Diagonal */
            dist[i][i] = 0;
            parente[i][i] = i;
       }

        for(int i = 1; i < N; i++){
            /* Inicialização das arestas informadas pelo usuario*/
            int x;
            int y;

            cin >> x;
            cin >> y;

            /* Aqui temos um grafo não direcionado com custo igual para os dois lados*/
            grafo[x][y] += 1;
            grafo[y][x] += 1;
            dist[x][y] = 1;
            dist[y][x] = 1;
            parente[x][y] = x;
            parente[y][x] = y;
        }

        /* Executa o algoritm de Floyd Warshall e retorna o nó de "centro" */
        int resultado = 1;
        if(N > 1){
            resultado = FloydWarshall();
        }

        /* Imprime uma linha em branco entre os testes*/
        if(z > 1){
            cout << '\n';
        }

        /* Imprime o resultado obtido */
        cout << "Teste " << z << '\n';
        cout << resultado << '\n';

        /* Incrementa o número do teste */
        z += 1;
    }while(N != 0);

    return 0;
}
