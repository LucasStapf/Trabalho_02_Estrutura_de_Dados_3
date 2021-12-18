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

typedef struct estruturaAux {
    int distancia;
    char *antecessor;
} estruturaAux;

enum COLOR {
    WHITE,
    GRAY,
    BLACK
};

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

int insertEdge(graph *g, char *verticeOrigem, char *verticeDestino, int distancia, char *nomeLinha, int directedGraph) {

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

    if (directedGraph == FALSE) insertEdge(g, verticeDestino, verticeOrigem, distancia, nomeLinha, TRUE);
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

void dijkstraAlgorithm(graph g, char *nomeOrigem, char *nomeDestino, linkedlist *caminho, int *distanciaTotal) {

    vertex **S = malloc(sizeof(vertex*) * g.size);
    int sizeOfS = 0;
    vertex **V = malloc(sizeof(vertex*) * g.size);
    int sizeOfV = g.size;


    estruturaAux *D = malloc(sizeof(estruturaAux) * g.size);

    for (int i = 0; i < g.size; i++) {
        D[i].distancia = INT_MAX / 2; // distancia "infinita"
        D[i].antecessor = NULL;
        V[i] = g.vertices[i];
    }


    int index = hasVertex(g, nomeOrigem);
    S[index] = g.vertices[index];
    sizeOfS++;
    D[index].distancia = 0;
    D[index].antecessor = NULL;

    while (sizeOfS < g.size - 1) {

        linkedlist adjList = V[index]->verticesAdjacentes;
        iterator iter;
        createIterator(adjList, &iter);

        while (hasNextNode(&iter) == TRUE) {
            node *n = getNextNode(&iter);
            adjacentVertex *adjV = n->data;
            int indexAux = hasVertex(g, adjV->nomeProxEstacao);
            if (adjV->distancia + D[index].distancia < D[indexAux].distancia) {
                D[indexAux].distancia = adjV->distancia + D[index].distancia;
                D[indexAux].antecessor = V[index]->nomeEstacao;
            }
        }

        int dMin = INT_MAX;
        int indexAux = -1;

        V[index] = NULL;
        sizeOfV--;

        for (int j = 0; j < g.size; j++) {
            if (D[j].distancia < dMin && V[j] != NULL) {
                dMin = D[j].distancia;
                indexAux = j;
            }
        }

        S[index] = g.vertices[index];
        sizeOfS++;

        index = indexAux;

    }

    createLinkedList(caminho);
    index = hasVertex(g, nomeDestino);
    *distanciaTotal = D[index].distancia;

    while (strcmp(nomeOrigem, g.vertices[index]->nomeEstacao) != 0) {
        addElementFirstLinkedList(caminho, g.vertices[index]->nomeEstacao);
        index = hasVertex(g, D[index].antecessor);
    }

    addElementFirstLinkedList(caminho, g.vertices[hasVertex(g, nomeOrigem)]->nomeEstacao);
}

int dfsRecursion(graph g, vertex *vOrigem, vertex *vDestino, enum COLOR *vertices, estruturaAux *est) {

    int i = hasVertex(g, vOrigem->nomeEstacao);
    vertices[i] = GRAY;

    iterator iter;
    createIterator(vOrigem->verticesAdjacentes, &iter);

    while(hasNextNode(&iter) == TRUE) {

        node *nAux = getNextNode(&iter);
        adjacentVertex *adjVAux = nAux->data;
        int indexAux = hasVertex(g, adjVAux->nomeProxEstacao);

        if (vDestino != NULL && vertexCompare(*vDestino, *g.vertices[indexAux]) == TRUE) {

            est[indexAux].distancia = adjVAux->distancia;
            est[indexAux].antecessor = vOrigem->nomeEstacao;
            return TRUE;

        } else if (vertices[indexAux] == WHITE) {

            est[indexAux].distancia = adjVAux->distancia;
            est[indexAux].antecessor = vOrigem->nomeEstacao;
            if(dfsRecursion(g, g.vertices[indexAux], vDestino, vertices, est) == TRUE) return TRUE;
        }
    }

    vertices[i] = BLACK;
    return FALSE;
}

void dfsAlgorithm(graph g, char *nomeOrigem, char *nomeDestino, linkedlist *caminho, int *distanciaTotal) {

    createLinkedList(caminho);
    *distanciaTotal = 0;

    enum COLOR *vertices = malloc(sizeof(enum COLOR) * g.size);
    estruturaAux *est = malloc(sizeof(estruturaAux) * g.size);

    for (int i = 0; i < g.size; i++) {
        vertices[i] = WHITE;
        est[i].antecessor = NULL;
        est[i].distancia = -1;
    }

    int iOrigem = hasVertex(g, nomeOrigem);
    vertex *vOrigem = g.vertices[iOrigem];

    int iDestino = hasVertex(g, nomeDestino);
    vertex *vDestino = g.vertices[iDestino];

//    node *n = getNodeLinkedList(vOrigem.verticesAdjacentes, 0);
//    adjacentVertex *adjV = n->data;
//
//    int iAux = hasVertex(g, adjV->nomeProxEstacao);
//    vertex vAux = *g.vertices[iAux];

    dfsRecursion(g, vOrigem, vDestino, vertices, est);

    while (est[iDestino].antecessor != NULL) {

        addElementFirstLinkedList(caminho, g.vertices[iDestino]->nomeEstacao);
        int aux = iDestino;
        iDestino = hasVertex(g, est[iDestino].antecessor);
        est[aux].antecessor = NULL;
        est[aux].distancia = -1;
    }

    addElementFirstLinkedList(caminho, g.vertices[iOrigem]->nomeEstacao);
}


typedef struct { // vértice
    char *nome;
    enum COLOR cor;
}V;

typedef struct { // aresta
    V *v1;
    V *v2;
    int distancia;
}A;

/**
 * Compara duas arestas
 * @param a1
 * @param a2
 * @return
 */
int compareAresta(A a1, A a2) {
    if (a1.distancia == a2.distancia) {
        if (strcmp(a1.v1->nome, a2.v1->nome) == 0) {
            return strcmp(a1.v2->nome, a2.v2->nome);
        } else return strcmp(a1.v1->nome, a2.v1->nome);
    } else return a1.distancia - a2.distancia;
}

void printDFS(graph g, char *nomeOrigem) {

    int index = hasVertex(g, nomeOrigem);

    iterator iter;
    createIterator(g.vertices[index]->verticesAdjacentes, &iter);

    printf("%s, ", nomeOrigem);

    while (hasNextNode(&iter) == TRUE) {
        node *n = getNextNode(&iter);
        adjacentVertex *adjV = n->data;
        printf("%s, %d\n", adjV->nomeProxEstacao, adjV->distancia);
        printDFS(g, adjV->nomeProxEstacao);
    }
}

void primAlgorithm(graph g, char *nomeOrigem, graph *mst) {

    createGraph(mst, g.size);

    V vertices[g.size];

    linkedlist arestas;
    createLinkedList(&arestas);

    for(int i = 0; i < g.size; i++) { // criação dos vértices
        vertex *vertex1 = g.vertices[i];
        vertices[i].nome = vertex1->nomeEstacao;
        vertices[i].cor = WHITE;
    }

    for(int i = 0; i < g.size; i++) { // criação das arestas

        vertex *vertex1 = g.vertices[i];
        linkedlist adjV = vertex1->verticesAdjacentes;

        iterator iter;
        createIterator(adjV, &iter);
        while (hasNextNode(&iter) == TRUE) {

            node *n = getNextNode(&iter);
            adjacentVertex *adjacentVertex1 = n->data;

            int index = hasVertex(g, adjacentVertex1->nomeProxEstacao);

            A *aresta = malloc(sizeof(A));
            aresta->v1 = &vertices[i];
            aresta->v2 = &vertices[index];
            aresta->distancia = adjacentVertex1->distancia;

            addElementLinkedList(&arestas, aresta);
            sortLinkedList(&arestas, compareAresta);
        }
    }


    int indexAtual = hasVertex(g, nomeOrigem);
    vertices[indexAtual].cor = BLACK;
    int percorridos = 1;

    while (percorridos < g.size) {

        iterator iter;
        createIterator(arestas, &iter);

        while (hasNextNode(&iter) == TRUE) {

            node *n = getNextNode(&iter);
            A *aresta = n->data;

            V *v1 = aresta->v1;
            V *v2 = aresta->v2;

            if (v1->cor == BLACK && v2->cor == BLACK) {
                removeNodeLinkedList(&arestas, n);
                continue;
            }

            insertEdge(mst, v1->nome, v2->nome, aresta->distancia, NULL, FALSE);
            v1->cor = BLACK;
            v2->cor = BLACK;

            removeNodeLinkedList(&arestas, n);
            percorridos++;
        }
    }
}

