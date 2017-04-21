#include <iostream>
#include <list>
#include <queue>
#include <map>

// Essa eu ja tinha feito semestre passado também

/* Constantes do algoritmo */
#define MAX_NUM_VERTICES 6002
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
list<int> grafo[MAX_NUM_VERTICES];
Vertice vertices[MAX_NUM_VERTICES];

/* Tempo Global */
int tempo;

/* Variaveis do programa */
int C, R;

/* Mapeamento dos vertices com string */
map<string, int> nome_vertices;

void printaVazio(int qtd){
    for(int i = 0; i < qtd; i++){
        cout << " ";
    }
}

/* Visita os nós adjacentes, utilizando busca em largura */
int BFS(Vertice *s){
    /* Começa a consulta do primeiro valor */
    //Vertice *s = &vertices[1];

    /* Inicializamos o nó em questão */
    s->cor = CINZA;
    s->d = 0;
    s->anterior = NULL;

    /* Tamanho do ciclo */
    int tamanho_ciclo = 1;

    /* Criamos uma fila de prioridades */
    queue<int> Q;

    /* Enfileiramos o primeiro valor */
    Q.push(s->num);

    /* Enquanto a fila não estiver vazia */
    while(!Q.empty()){
        Vertice *u = &vertices[Q.front()];
        Q.pop();

        #ifdef DEBUG
        cout << u->num <<  " ";
        #endif

        /* Para cada vértice adjacente a u */
        for_each(it, grafo[u->num]){
            Vertice *v = &vertices[*it];

            /* Se o vertice não tiiver sido visitado, marca ele como visitado, enfileira e modifica */
            if(v->cor == BRANCO){
                /* Setamos os valores do vértice adjacente */
                v->anterior = u;
                v->cor = CINZA;
                v->d = u->d + 1;
                
                /* Empilhamos o número do vértice adjacente atual */
                Q.push(v->num);

                /* Incrementamos em 1 o tamanho do ciclo */
                tamanho_ciclo += 1;
            }
        }
        
        /* Finaliza a consulta */
        u->cor = PRETO;
    }

    
    #ifdef DEBUG
    cout << endl;
    #endif

    return tamanho_ciclo;
}

/* Visita os nós adjancentes, utilizando busca em profundidade */
int DFS_visit(Vertice *u, int grau){
    /* Atualiza o valor do tempo e indica que está sendo visitado */
    tempo += 1;
    u->tempo_s = tempo;
    u->cor = CINZA;

    /* Quantidade de nos */
    int quantidade_ciclos = 1;

    #ifdef DEBUG
    printaVazio(grau);
    cout << " -- Inicio -- " << endl;
    #endif

    /* Para cada vértice adjacente a u */
    for_each(it, grafo[u->num]){
        Vertice *v = &vertices[*it];

        /* Caso ele seja branco */
        if(v->cor == BRANCO){
            v->anterior = u;
            quantidade_ciclos += DFS_visit(v, grau + 3);
            
            #ifdef DEBUG
            printaVazio(grau);
            cout << " -- Encontrado Ciclo -- > X = " << quantidade_ciclos << endl;
            #endif
        }
    }

    #ifdef DEBUG
    printaVazio(grau);
    cout << " > " << quantidade_ciclos << endl;
    printaVazio(grau);
    cout << " -- Fim -- " << endl;
    #endif

    /* Finaliza a busca em profundidade do nó atual */
    u->cor = PRETO;
    tempo += 1;
    u->tempo_f = tempo;

    /* Retorna o contador de ciclo */
    return quantidade_ciclos;
}

int main(){

    do{
        /* Lê as entradas */
        cin >> C;
        cin >> R;

        /* Se condição de parada da aplicação for atingida */
        if(C == 0)
            break;

        /* Inicalização do grafo */
        nome_vertices.clear();
        tempo = 0;
        for(int i = 1; i <= C; i++){
            /* Vertices */
            vertices[i].cor = BRANCO;
            vertices[i].num = i;
            vertices[i].anterior = NULL;

            /* Valor de cada vertice */
            /* Inicializa a chave se a mesma for nova na tabela de simbolos */
            string alimento_ou_preador;
            cin >> alimento_ou_preador;
            //nome_vertices.insert(make_pair(alimento_ou_preador, i));
            nome_vertices[alimento_ou_preador] = i;

            #ifdef DEBUG
            cout << ">>> " << alimento_ou_preador << " ID " << nome_vertices[alimento_ou_preador] << endl;
            #endif

            /* Arestas */
            grafo[i].clear();
        }

        /* Lê as arestas */
        for(int i = 0; i < R; i++){
            string alimento, preador;

            /* Pega o nome de cada alimento e seu respectivo predador */
            cin >> alimento;
            cin >> preador;

            /* Associa o valor da string a um numero inteiro qualquer */
            int id_alimento = nome_vertices[alimento];
            int id_predador = nome_vertices[preador];

            #ifdef DEBUG
            cout << "alimento = " << alimento << " preador = " << preador << endl;
            cout << "id_alimento = " << id_alimento << " id_preador = " << id_predador << endl;
            #endif

            /* Como alimento e preador estão na mesma cadeia, temos tanto a ida como a volta */
            grafo[id_predador].push_back(id_alimento);
            grafo[id_alimento].push_back(id_predador);
        }

        /* Maior cadeia alimentar */
        int maior_ciclo = 0;

        /* Executa uma DFS */
        /* Iremos contar o tamanho de cada ciclo e armazenar o valor do ciclo maior */
        for(int i = 1; i <= C; i++){
            if(vertices[i].cor == BRANCO){
                //int qtd_ciclos_atual = DFS_visit(&vertices[i], 0);
                int qtd_ciclos_atual = BFS(&vertices[i]);
                maior_ciclo = max(maior_ciclo, qtd_ciclos_atual);
            }
        }

        /* Imprime o maior ciclo */
        cout << maior_ciclo << endl;

    }while(C != 0);

    return 0;
}
