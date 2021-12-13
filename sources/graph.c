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
#include <limits.h>
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

        vertex *v = createVertex(verticeOrigem);
        adjacentVertex *adjV = createAdjcentVertex(verticeDestino, distancia);
        addStringLinkedList(&adjV->nomesLinhas, (void*) nomeLinha);
        insertAdjVertex(v, adjV);
        insertVertex(g, v);

    } else { // Vértice de origem encontrado.

        vertex *v = g->vertices[indexV];

        int indexAdjV = hasAdjVertex(*v, verticeDestino);

        if (indexAdjV == -1) { // Não existe aresta entre os vértices passados.

            adjacentVertex *adjV = createAdjcentVertex(verticeDestino, distancia);
            addStringLinkedList(&adjV->nomesLinhas, (void*) nomeLinha);
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
}

/**
 * Imprime o grafo conforme especificação do trabalho.
 * @param g grafo a ser mostrado na tela.
 */
void printGraph(graph g) {
    for (int i = 0; i < g.size; i++) {
        printVertex(*g.vertices[i]);
        printf("\n");
    }
}

/**
 * Imprime um vértice conforme especificação do trabalho.
 * @param v vértice a ser mostrado na tela.
 */
void printVertex(vertex v) {
    printf("%s ", v.nomeEstacao);
    node *n = v.verticesAdjacentes.head;
    for (int i = 0; i < v.verticesAdjacentes.size; i++) {
        adjacentVertex *adjV = n->data;
        printAdjVertex(*adjV);
        n = n->next;
    }
}

/**
 * Imprime um vértice adjacente conforme a especificação do trabalho.
 * @param adjV vértice adjcente a ser mostrado na tela.
 */
void printAdjVertex(adjacentVertex adjV) {
    printf("%s %d ", adjV.nomeProxEstacao, adjV.distancia);
    printStringLinkedList(adjV.nomesLinhas);
}


vertex *createVertex(char *nomeEstacao) {
    vertex *v = malloc(sizeof(vertex));
    strcpy(v->nomeEstacao, nomeEstacao);
    createLinkedList(&v->verticesAdjacentes);
    return v;
}

adjacentVertex *createAdjcentVertex(char *nomeEstacao, int distancia) {
    adjacentVertex *adjV = malloc(sizeof(adjacentVertex));
    strcpy(adjV->nomeProxEstacao, nomeEstacao);
    adjV->distancia = distancia;
    createLinkedList(&adjV->nomesLinhas);
    return adjV;
}

/**
 * Insere um novo vértice no grafo.
 * OBS: Não verifica se o vértice já se encontra no grafo ou não.
 * @param g grafo onde o vértice será inserido.
 * @param v vértice a ser inserido.
 */
void insertVertex(graph *g, vertex *v) {
    g->vertices[g->size] = v;
    g->size++;
    sortArray((void**) g->vertices, g->size, vertexCompare);
}

/**
 * Insere um vértice adjacente à lista de vértices adjacentes de um determinado vértice.
 * OBS: Não verifica se o vértice adjacente já está presente na lista ou não.
 * @param v vértice onde será inserido o vértice adjacente.
 * @param adjV vértice adjcente a ser inserido.
 */
void insertAdjVertex(vertex *v, adjacentVertex *adjV) {
    addElementLinkedList(&v->verticesAdjacentes, (void*) adjV);
    sortLinkedList(&v->verticesAdjacentes, adjVertexCompare);
}

/**
 * Adiciona a uma lista de nome de linhas de um novo elemento.
 * OBS: Não verifica se o nome da linha já está presente na lista ou não.
 * @param adjV vértice onde a nova linha será adicionada.
 * @param nomeLinha nome da linha a ser adicionada.
 */
void updateNomesLinhas(adjacentVertex *adjV, char *nomeLinha) {
    addStringLinkedList(&adjV->nomesLinhas, nomeLinha);
    sortLinkedList(&adjV->nomesLinhas, strcmp);
}

void dijkstraAlgorithm(graph g, char *nomeEstacao) {

    vertex **S = malloc(sizeof(vertex*) * g.size);
    int sizeOfS = 0;
    vertex **V = malloc(sizeof(vertex*) * g.size);
    int sizeOfV = g.size;

    int *D = malloc(sizeof(int) * g.size);

    for (int i = 0; i < g.size; i++) {
        D[i] = INT_MAX / 2; // distancia "infinita"
        V[i] = g.vertices[i];
    }

    int index = hasVertex(g, nomeOrigem);
    S[index] = g.vertices[index];
    D[index] = 0;
    sizeOfS = 1;

    while (sizeOfS < g.size) {

        linkedlist adjList = S[index]->verticesAdjacentes;
    }
}

