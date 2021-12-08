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
#include "sort.h"

int vertexCompare(vertex v1, vertex v2) {
    return strcmp(v1.nomeEstacao, v2.nomeEstacao);
}

int adjVertexCompare(adjacentVertex v1, adjacentVertex v2) {
    return strcmp(v1.nomeProxEstacao, v2.nomeProxEstacao);
}

int hasVertex(graph g, char *nomeEstacao) {
    for (int i = 0; i < g.size; i++) if (strcmp(g.vertices[i]->nomeEstacao, nomeEstacao) == 0) return i;
    return -1;
}

int hasAdjVertex(vertex v, char *nomeProxEstacao) {
    node *aux = v.verticesAdjacentes.head;
    for (int i = 0; i < v.verticesAdjacentes.size; i++) {
        adjacentVertex *adjAux = aux->data;
        if (strcmp(nomeProxEstacao, adjAux->nomeProxEstacao) == 0) return i;
        else aux = aux->next;
    }
    return -1;
}

int createGraph(graph *g, int maxSize) {

    g->vertices = malloc(sizeof(vertex*) * maxSize);
    if (g->vertices == NULL) return ERROR;
    g->maxSize = maxSize;
    g->size = 0;

    for (int i = 0; i < maxSize; i++) g->vertices[i] = NULL;

    return SUCCESS;
}

int insertEdge(graph *g, char *verticeOrigem, char *verticeDestino, int distancia, char *nomeLinha) {

    if (g == NULL) return ERROR;

    int indexV = hasVertex(*g, verticeOrigem);

    if (indexV == -1) { // Vértice de origem não encontrado.

        vertex *v = malloc(sizeof(vertex));
        strcpy(v->nomeEstacao, verticeOrigem);
        createLinkedList(&v->verticesAdjacentes);

        adjacentVertex *adjV = malloc(sizeof(adjacentVertex));
        strcpy(adjV->nomeProxEstacao, verticeDestino);
        adjV->distancia = distancia;
        createLinkedList(&adjV->nomesLinhas);

        addElementLinkedList(&adjV->nomesLinhas, (void*) nomeLinha);

        insertAdjVertex(v, adjV);
        insertVertex(g, v);

    } else { // Vértice de origem encontrado.

        vertex *v = g->vertices[indexV];

        int indexAdjV = hasAdjVertex(*v, verticeDestino);

        if (indexAdjV == -1) { // Não existe aresta entre os vértices passados.

            adjacentVertex *adjV = malloc(sizeof(adjacentVertex));
            strcpy(adjV->nomeProxEstacao, verticeDestino);
            adjV->distancia = distancia;
            createLinkedList(&adjV->nomesLinhas);

            addElementLinkedList(&adjV->nomesLinhas, (void*) nomeLinha);

            insertAdjVertex(v, adjV);

        } else { // Existe aresta

            vertex *v = g->vertices[indexV];
            node *n = getNodeLinkedList(v->verticesAdjacentes, indexAdjV);
            adjacentVertex  *adjV = (adjacentVertex*) n->data;

            if (hasDataLinkedList(adjV->nomesLinhas, nomeLinha, strcmp) == -1) {
                updateNomesLinhas(adjV, nomeLinha);
            }
        }
    }

//    if (g == NULL) return ERROR;
//
//    int indexV = hasVertex(*g, verticeOrigem);
//
//    if (indexV != -1) { // Já possui o vértice
//
//        int indexAdj = hasAdjVertex(g->vertices[indexV], verticeDestino);
//
//        if (indexAdj != -1) { // Já possui o vértice adj.
//
//            node *n = getNodeLinkedList(g->vertices[indexV].verticesAdjacentes, indexAdj);
//            adjacentVertex *adjVertex = (adjacentVertex*) n->data;
//            if (hasDataLinkedList(adjVertex->nomesLinhas, nomeLinha, strcmp) == -1) {
//                addStringLinkedList(&adjVertex->nomesLinhas, nomeLinha);
//                sortLinkedList(&adjVertex->nomesLinhas, strcmp);
//            }
//        }
//
//    } else { // Não possui a aresta
//
//        int i;
//        for (i = 0; i < g->size; i++) if (g->vertices[i].nomeEstacao[0] == '\0') break;
//
//        strcpy(g->vertices[i].nomeEstacao, verticeOrigem);
//
//        createLinkedList(&g->vertices[i].verticesAdjacentes);
//        adjacentVertex *adjVertex = malloc(sizeof(adjVertex));
//        strcpy(adjVertex->nomeProxEstacao, verticeDestino);
//        adjVertex->distancia = distancia;
//        addElementLinkedList(&g->vertices[i].verticesAdjacentes, adjVertex);
//
//        createLinkedList(&adjVertex->nomesLinhas);
//        addStringLinkedList(&adjVertex->nomesLinhas, nomeLinha);
//
//        sortArray((void**) &g->vertices, g->size, vertexCompare);
//    }
}

void printGraph(graph g) {
    for (int i = 0; i < g.size; i++) {
        printVertex(*g.vertices[i]);
        printf("\n");
    }
}

void printVertex(vertex v) {
    printf("%s ", v.nomeEstacao);
    node *n = v.verticesAdjacentes.head;
    for (int i = 0; i < v.verticesAdjacentes.size; i++) {
        adjacentVertex *adjV = n->data;
        printAdjVertex(*adjV);
        n = n->next;
    }
}

void printAdjVertex(adjacentVertex adjV) {
    printf("%s %d ", adjV.nomeProxEstacao, adjV.distancia);
    printStringLinkedList(adjV.nomesLinhas);
}

void insertVertex(graph *g, vertex *v) {
    g->vertices[g->size] = v;
    g->size++;
}

void insertAdjVertex(vertex *v, adjacentVertex *adjV) {
    addElementLinkedList(&v->verticesAdjacentes, (void*) adjV);
    sortLinkedList(&v->verticesAdjacentes, adjVertexCompare);
}

void updateNomesLinhas(adjacentVertex *adjV, char *nomeLinha) {
    addStringLinkedList(&adjV->nomesLinhas, nomeLinha);
    sortLinkedList(&adjV->nomesLinhas, strcmp);
}

