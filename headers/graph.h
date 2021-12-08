/**
 * Trabalho 02 - Estrutura de Dados III
 *
 * Integrantes do grupo:
 *
 * Leonardo Hannas de Carvalho Santos  NUSP: 11800480
 * Lucas Carvalho Freiberger Stapf     NUSP: 11800559
 */

#ifndef GRAFO_H
#define GRAFO_H

#include "constantes.h"
#include "linkedlist.h"


typedef struct adjacentVertex {
    char nomeProxEstacao[STR_MAX_SIZE];
    int distancia;
    linkedlist nomesLinhas;
} adjacentVertex;

typedef struct vertex {
    char nomeEstacao[STR_MAX_SIZE];
    linkedlist verticesAdjacentes;
} vertex;


typedef struct graph {
    int size;
    vertex *vertices;
} graph;

int vertexCompare(vertex v1, vertex v2);
int adjVertexCompare(adjacentVertex v1, adjacentVertex v2);

int hasVertex(graph g, vertex v);
int hasAdjVertex(vertex v, adjacentVertex adjV);

int criarGrafo(graph *g, int tamanho);
int inserirAresta(graph *g, char *verticeOrigem, char* verticeDestino, int distancia, char *nomeLinha);



#endif