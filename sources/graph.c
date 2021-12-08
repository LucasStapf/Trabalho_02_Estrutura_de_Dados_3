/**
 * Trabalho 02 - Estrutura de Dados III
 *
 * Integrantes do grupo:
 *
 * Leonardo Hannas de Carvalho Santos  NUSP: 11800480
 * Lucas Carvalho Freiberger Stapf     NUSP: 11800559
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "linkedlist.h"

int vertexCompare(vertex v1, vertex v2) {
    return strcmp(v1.nomeEstacao, v2.nomeEstacao);
}

int adjVertexCompare(adjacentVertex v1, adjacentVertex v2) {
    return strcmp(v1.nomeProxEstacao, v2.nomeProxEstacao);
}

int hasVertex(graph g, vertex v) {
    for (int i = 0; i < g.size; i++) {
        if (strlen(g.vertices[i].nomeEstacao) == 0) return FALSE;
        if (vertexCompare(g.vertices[i], v)) return TRUE;
    }
    return FALSE;
}

int hasAdjVertex(vertex v, adjacentVertex adjV) {

}

int criarGrafo(graph *g, int tamanho) {

    g->vertices = malloc(sizeof(vertex) * tamanho);
    if (g->vertices == NULL) return ERROR;
    g->size = tamanho;

    for (int i = 0; i < tamanho; i++) g->vertices[i].nomeEstacao[0] = '\0';

    return SUCCESS;
}

int inserirAresta(graph *g, char *verticeOrigem, char *verticeDestino, int distancia, char *nomeLinha) {

}

