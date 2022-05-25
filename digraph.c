/*******************************************/
/* Aluno: Emanuel Gefferson Maciel Sampaio */
/* CES-11: Algoritmos para grafos          */
/* Turma T3                                */
/*******************************************/

#include "digraph.h"
#include "stack.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge EDGE;

struct edge {
    int index;
    EDGE *next;
};

struct digraph {
    int order;
    EDGE **vertex;
};

DIGRAPH *digraph_read() {
    int ordem, vertice_1, vertice_2;
    scanf("%d", &ordem);
    DIGRAPH *digrafo = digraph_create(ordem);
    while ((scanf("%d %d", &vertice_1, &vertice_2)) != EOF){
        digraph_add_edge(digrafo, vertice_1, vertice_2);
    }

    return digrafo;
}

DIGRAPH *digraph_create(int order) {
    DIGRAPH *digrafo = (DIGRAPH*)malloc(sizeof(DIGRAPH));
    digrafo->order = order;
    digrafo->vertex = (EDGE**)malloc(order*sizeof(EDGE*));

    for(int i=0; i<order; i++){
        digrafo->vertex[i] = NULL;
    }

    return digrafo;
}

void digraph_destroy(DIGRAPH *digraph) {
    if(digraph != NULL){
        EDGE *temp;
        for(int i=0; i<digraph->order; i++){
            for(EDGE *p = digraph->vertex[i]; p != NULL; p = temp){
                temp = p->next;
                free(p);
            }
        }
        free(digraph->vertex);
        free(digraph);
    }
}

static EDGE *digraph_create_edge(int v) {
    EDGE *aresta = (EDGE*)malloc(sizeof(EDGE));
    aresta->index = v;
    aresta->next = NULL;
    return aresta;
}

void digraph_add_edge(DIGRAPH *digraph, int u, int v) {
    EDGE *aresta = digraph_create_edge(v);
    if(digraph->vertex[u] != NULL){
        for(EDGE *p = digraph->vertex[u]; p != NULL; p = p->next){
            if(p->next != NULL){
                if(v>p->index && v<p->next->index){
                    aresta->next = p->next;
                    p->next = aresta;
                }
            }
            else{
                p->next = aresta;
                break;
            }
        }
    }
    else{
         digraph->vertex[u] = aresta;
    }
}

bool digraph_has_edge(const DIGRAPH *digraph, int u, int v) {
    for(EDGE *p = digraph->vertex[u]; p != NULL; p = p->next){
        if(p->index == v){
            return true;
        }
    }

    return false;
}

typedef enum { WHITE, GRAY, BLACK } COLOR;

static bool topological_sort_dfs(const DIGRAPH *digraph, int u, COLOR *color, STACK *stack) {
    if(color[u] == GRAY){
        return false;
    }
    if(color[u] == BLACK){
        return true;
    }
    color[u] = GRAY;
    for(int v=0; v<digraph->order; v++){
        if(digraph_has_edge(digraph, u, v)){
            if(!topological_sort_dfs(digraph, v, color, stack)){
                return false;
            }
        }
    }
    color[u] = BLACK;
    stack_push(stack,u);
    return true;
}

void topological_sort(const DIGRAPH *digraph) {
    STACK *visitados = stack_create();
    COLOR *cor = (COLOR*)malloc(digraph->order*sizeof(COLOR));
    for(int i=0; i<digraph->order; i++){
        cor[i] = WHITE;
    }
    for(int j=0; j<digraph->order; j++){
        if(!topological_sort_dfs(digraph, j, cor, visitados)){
            printf("\n");
            return;
        }
    }
    while(stack_isEmpty(visitados) == false){
        printf("%d ", stack_top(visitados));
        stack_pop(visitados);
    }
    free(cor);
    free(visitados);
}

