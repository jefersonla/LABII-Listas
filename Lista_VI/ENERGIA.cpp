#include <iostream>
#include <cstdlib>
#include <list>

#define MAX_VERTICES 101

#define BRANCO 0
#define CINZA  1
#define PRETO  2

using namespace std;

typedef struct VerticeStruct{
    int cor;
    int tempo_d;
    int tempo_f;
    int num;
    struct VerticeStruct *pai;
} Vertice;

/* Tempo Global */
int tempo = 0;

/* Numero de Vertices */
int E;

/* Numero de visitas */
int comp_conexa;

/* Grafo & Vertices */

/* Matriz de Adjacência */
int grafo[MAX_VERTICES][MAX_VERTICES] = {{ 0 }};

/* Vertices */
Vertice vertices[MAX_VERTICES];

void DFS_VISIT(Vertice *u){
    int i;
    Vertice *v;  

    /* Atualiza os valores do tempo e do vertice */
    tempo += 1;
    u->tempo_d = tempo;
    u->cor = CINZA;

    /* Para cada vertice adjacente ao vertice atual */
    for(i = 1; i <= E; i++){
        /* Pula para o próxima adjacência possivel */
        if(grafo[u->num][i] == 0)
            continue;

        /* Vertice adjacente */
        v = &vertices[i];

        /* Se o vertice ainda não tiver sido visitado */
        if(v->cor == BRANCO){
            v->pai = u;
            DFS_VISIT(v);
        }
    }

    /* Finaliza a busca em profundidade */
    u->cor = PRETO;
    tempo += 1;
    u->tempo_f = tempo;
}

int main(){
    int i, j, k;
    int L, v1, v2;
    int test_num = 1;

    /* Executa enquanto E e L forem diferentes de 0 */
    do{
        /* Recupera E e L */
        cin >> E;
        cin >> L;

        /* Para a execução se E e L são iguais a 0*/
        if( E == 0 && L == 0 )
            break;

        /* Inicializa a matriz de adjacência e os vertices*/
        for(i = 1; i <= E; i++){
            for(j = 1; j <= E; j++){
                /* Matriz de adjacência */
                grafo[i][j] = 0;
            }
            
            /* Vertices */
            vertices[i].cor = BRANCO;
            vertices[i].pai = NULL;
            vertices[i].num = i;
        }

        /* Constrói a matriz de adjacências */
        for(i = 0; i < L; i++){
            /* Pega o vertice */
            cin >> v1;
            cin >> v2;

            /* Adiciona uma adjacência entre os dois vértices */
            grafo[v1][v2] += 1;
            grafo[v2][v1] += 1;
        }

        /* Executa uma busca em profundidade */
        /* Inicializa o tempo */
        tempo = 0;

        /* Inicializa as componentes conexas */
        comp_conexa = 0;

        /* Para cada vertice se o vertice ainda não tiver sido visitado executa uma busca em profundidade */
        for(int i = 1; i <= E; i++){
            if(vertices[i].cor == BRANCO){
                DFS_VISIT(&vertices[i]);
                comp_conexa += 1;
            }
        }

        /* Se este não for o primeiro teste imprima uma quebra de linha */
        if(test_num > 1){
            cout << endl;
        }

        /* Imprime o numero do teste */
        cout << "Teste " << test_num << endl;

        /* Se o número de visitas for igual ao número de vértices, temos ao menos um caminho entre todos eles */
        if(comp_conexa == 1){
            cout << "normal" << endl;
        }
        else {
            cout << "falha" << endl;
        }

        /* Incrementa o numero de execuções */
        test_num += 1;
    } while(E != 0 && L != 0);

    return EXIT_SUCCESS;
}
