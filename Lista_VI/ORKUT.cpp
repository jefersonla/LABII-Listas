#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <set>

/* Constantes do algoritmo */
#define MAX_NUM_VERTICES 300
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
#define max(var1, var2)     (var1 > var2 ? var1 : var2)

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
    int tempo_s;
    int tempo_f;
    struct VerticeStruct *anterior;
} Vertice;

/* Estrutura do grafo - arestas e vertices */
int saida[MAX_NUM_VERTICES];
int dependecia[MAX_NUM_VERTICES];
list<int> grafo[MAX_NUM_VERTICES];
Vertice vertices[MAX_NUM_VERTICES];

/* Tempo Global */
int tempo;

/* Variaveis do programa */
int N, M;

/* Mapeamento dos vertices com string */
map<string, int> nome_vertices;
map<int, string> id_vertices;

/* Verifica a existência de dependecia */
#define nao_tem_dependecia(var) (dependecia[var] == 0)

/* Ordena tarefas */
int OrdenacaoTopologica(){
    /* Criamos uma fila de prioridades */
    set<int> Q;

    /* Items ordenados */
    int qtd_itens_ordenados = 0;

    /* Enfileiramos todos os valores que não tem precedência */
    for(int i = 1; i <= N; i++){
        if(nao_tem_dependecia(i)){
            Q.insert(i);
        }
    }

    /* Enquanto a fila não estiver vazia */
    while(!Q.empty()){
        Vertice *u = &vertices[*(Q.begin())];
        Q.erase(Q.begin());

        #ifdef DEBUG
        cout << u->num <<  " ";
        #endif

        /* Para cada vértice adjacente a u */
        for_each(it, grafo[u->num]){
            Vertice *v = &vertices[*it];

            dependecia[v->num] -= 1;
            if(nao_tem_dependecia(v->num)){
                Q.insert(v->num);
            }
        }
        
        /* Após modificarmos a precedência dos nós adjacentes e empilharmos os que não tinham dependencia */
        saida[qtd_itens_ordenados] = u->num;
        qtd_itens_ordenados += 1;
    }

    return qtd_itens_ordenados;
}

int main(){
    int z = 1;


    do{
        /* Lê as entradas */
        cin >> N;

        /* Se condição de parada da aplicação for atingida */
        if(N == 0)
            break;

        /* Inicalização do grafo */
        nome_vertices.clear();
        id_vertices.clear();
        tempo = 0;
        for(int i = 1; i <= N; i++){
            /* Vertices */
            vertices[i].cor = BRANCO;
            vertices[i].num = i;
            vertices[i].anterior = NULL;

            /* Dependencias */
            dependecia[i] = 0;

            /* Resposta */
            saida[i] = 0;

            /* Valor de cada vertice */
            /* Inicializa a chave se a mesma for nova na tabela de simbolos */
            string amigo;
            cin >> amigo;
            nome_vertices[amigo] = i;
            id_vertices[i] = amigo;

            #ifdef DEBUG
            cout << ">>> " << amigo << " ID " << nome_vertices[amigo] << endl;
            #endif

            /* Arestas */
            grafo[i].clear();
        }

        /* Lê as arestas */
        for(int i = 0; i < N; i++){
            string amigo;
            int n_amigos;

            /* Pega o nome de cada amigo e a lista de amigos desse amigo */
            cin >> amigo;
            cin >> n_amigos;

            /* Associa o valor da string a um numero inteiro qualquer */
            int id_amigo = nome_vertices[amigo];
            
            #ifdef DEBUG
            cout << "amigo = " << amigo << endl;
            cout << "id_amigo = " << id_amigo << " id_preador = " << id_predador << endl;
            #endif

            /* Como "ser amigo" é direcional */
            for(int j = 0; j < n_amigos; j++){
                string amigo_do_amigo;
                cin >> amigo_do_amigo;
                int id_amigo_do_amigo = nome_vertices[amigo_do_amigo];
                grafo[id_amigo_do_amigo].push_back(id_amigo);
                dependecia[id_amigo] += 1;
            }
        }

        /* Tenta ordenar as tarefas */
        int qtd_tarefas_ordenadas = OrdenacaoTopologica();

        if(z > 1){
            cout << '\n';
        }

        cout << "Teste " << z << '\n';

        /* Se a qtd de amigos ordenadas for igual ao total de nós imprimiremos a sequencia */
        if(qtd_tarefas_ordenadas == N){
            for(int i = 0; i < N; i++){
                if(i > 0){
                    cout << ' ';
                }
                cout << id_vertices[saida[i]];
            }
        }
        else{
            /* Caso contrário imprimimos que não é possível */
            cout << "impossivel";
        }
        cout << '\n';

        z += 1;

    }while(true);

    return 0;
}
