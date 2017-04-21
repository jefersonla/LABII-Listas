#include <iostream>
#include <list>
#include <queue>
#include <limits>

/* Constantes do algoritmo */
#define MAX_NUM_VERTICES 450
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
#define max_2(var1, var2)   (var1 > var2 ? var1 : var2)

/* Min value between two vars */
#define min_2(var1, var2)   (var1 < var2 ? var1 : var2)

/* Verifica a existência */
#define is_none(var)        (var == NULL)
#define is_not_none(var)    (var != NULL)

/* Valor infinito */
#define INFINITY_VALUE std::numeric_limits<int>::max()

/* Ativar apenas durante o DEBUG */
//#define DEBUG

using namespace std;

typedef struct VerticeStruct{
    int num;
    int cor;
    int d;
    int low;
    int tempo_f;
    bool corte;
    struct VerticeStruct *anterior;
} Vertice;

/* Estrutura do grafo - arestas e vertices */
list<int> grafo[MAX_NUM_VERTICES];
Vertice vertices[MAX_NUM_VERTICES];

/* Tempo Global */
int tempo;

/* Variaveis do programa */
int N, M;

void printaVazio(int qtd){
    for(int i = 0; i < qtd; i++){
        cout << " ";
    }
}

int root;
int root_n;

/* Visita os nós adjancentes, utilizando busca em profundidade */
void DFS_visit(Vertice *u){
    /* Atualiza o valor do tempo e indica que está sendo visitado */
    u->d = tempo;
    u->low = tempo;
    tempo += 1;
    u->cor = CINZA;

    /* Para cada vértice adjacente a u */
    for_each(it, grafo[u->num]){
        Vertice *v = &vertices[*it];

        /* Caso ele seja branco */
        if(v->cor == BRANCO){
            /* Se for nó de raiz */
            if(u->num == root){
                root_n += 1;
            }

            v->anterior = u;
            DFS_visit(v);
            
            /* Verifica se temos uma aresta de corte e indica que são vertices de corte */
            if(v->low >= u->d){
                u->corte = true;
                #ifdef DEBUG
                cout << "ACHOU UM PONTO DE ARTICULACAO " << u->num << endl;
                #endif 
            }

            u->low = min_2(u->low, v->low);
        }
        else if(u->anterior != v){
            u->low = min(u->low, v->d);
        }
    }

    /* Finaliza a busca em profundidade do nó atual */
    u->cor = PRETO;
}

int main(){
    int z = 1;

    do{
        /* Lê as entradas */
        cin >> N;
        cin >> M;

        /* Se condição de parada da aplicação for atingida */
        if(N == 0 && M == 0)
            break;

        /* Inicalização do grafo */
        tempo = 0;
        root = 1;
        root_n = 0;
        for(int i = 1; i <= N; i++){
            /* Vertices */
            vertices[i].cor = BRANCO;
            vertices[i].num = i;
            vertices[i].low = 0;
            vertices[i].d = 0;
            vertices[i].anterior = NULL;
            vertices[i].corte = false;

            /* Arestas */
            grafo[i].clear();
        }

        /* Lê as arestas */
        for(int i = 0; i < M; i++){
            int X;
            int Y;

            cin >> X;
            cin >> Y;

            /* Adicionamos a ida e a volta para o vértice adjacente já que temos um grafo não direcionado */
            grafo[X].push_back(Y);
            grafo[Y].push_back(X);
        }

        /* Executa uma DFS */
        /* Iremos contar o tamanho de cada ciclo e armazenar o valor do ciclo maior */
        for(int i = 1; i <= N; i++){
            if(vertices[i].cor == BRANCO){
                DFS_visit(&vertices[i]);
            }
        }

        /* Para o no raiz ser nó de corte ele precisa ter mais de 1 filho */
        vertices[root].corte = (root_n > 1);

        if(z > 1){
            cout << '\n';
        }

        /* Imprime os vertices de corte */
        cout << "Teste " << z << '\n';
        int k = 0;
        for(int u = 1; u <= N; u++){
            Vertice *v = &vertices[u];

            if(v->corte){
                if(k > 0){
                    cout << ' ';
                }
                k += 1;
                cout << v->num;
            }
        }
        if(k == 0){
            cout << "nenhum";
        }
        cout << '\n';

        /* Contador de número de testes */
        z += 1;

    }while(true);

    return 0;
}
