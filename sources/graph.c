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
#include "../headers/binmanager.h"
#include "../headers/registers.h"
#include "../headers/graph.h"
#include "../headers/linkedlist.h"
#include "../headers/sort.h"

typedef struct estruturaAux {
    int distancia;
    char *antecessor;
} estruturaAux;

enum COLOR {
    WHITE,
    GRAY,
    BLACK
};

int compareStrVoid(void *str1, void *str2) {
    char *STR1 = str1;
    char *STR2 = str2;
    return strcmp(STR1, STR2);
}

int vertexCompareVoid(void *v1, void *v2) {
    vertex *V1 = v1;
    vertex *V2 = v2;
    return vertexCompare(*V1, *V2);
}

int vertexCompare(vertex v1, vertex v2) {
    return strcmp(v1.nomeEstacao, v2.nomeEstacao);
}

int adjVertexCompareVoid(void *v1, void *v2) {

    adjacentVertex *V1 = v1;
    adjacentVertex *V2 = v2;
    return adjVertexCompare(*V1, *V2);
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

    if (indexV == -1) { // V??rtice de origem n??o encontrado.

        vertex *v = createVertex(verticeOrigem);
        adjacentVertex *adjV = createAdjcentVertex(verticeDestino, distancia);
        addStringLinkedList(&adjV->nomesLinhas, (void*) nomeLinha);
        insertAdjVertex(v, adjV);
        insertVertex(g, v);

    } else { // V??rtice de origem encontrado.

        vertex *v = g->vertices[indexV];

        int indexAdjV = hasAdjVertex(*v, verticeDestino);

        if (indexAdjV == -1) { // N??o existe aresta entre os v??rtices passados.

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
 * Imprime o grafo conforme especifica????o do trabalho.
 * @param g grafo a ser mostrado na tela.
 */
void printGraph(graph g) {
    for (int i = 0; i < g.size; i++) {
        printVertex(*g.vertices[i]);
        if (i < g.size - 1) printf("\n");
    }
}

/**
 * Imprime um v??rtice conforme especifica????o do trabalho.
 * @param v v??rtice a ser mostrado na tela.
 */
void printVertex(vertex v) {
    if (v.verticesAdjacentes.size == 0) printf("%s", v.nomeEstacao);
    else {
        printf("%s", v.nomeEstacao);
        node *n = v.verticesAdjacentes.head;
        for (int i = 0; i < v.verticesAdjacentes.size; i++) {
            printf(" ");
            adjacentVertex *adjV = n->data;
            printAdjVertex(*adjV);
            n = n->next;
        }
    }
}

/**
 * Imprime um v??rtice adjacente conforme a especifica????o do trabalho.
 * @param adjV v??rtice adjcente a ser mostrado na tela.
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
 * Insere um novo v??rtice no grafo.
 * OBS: N??o verifica se o v??rtice j?? se encontra no grafo ou n??o.
 * @param g grafo onde o v??rtice ser?? inserido.
 * @param v v??rtice a ser inserido.
 */
void insertVertex(graph *g, vertex *v) {
    g->vertices[g->size] = v;
    g->size++;
    sortArray((void**) g->vertices, g->size, vertexCompareVoid);
}

/**
 * Insere um v??rtice adjacente ?? lista de v??rtices adjacentes de um determinado v??rtice.
 * OBS: N??o verifica se o v??rtice adjacente j?? est?? presente na lista ou n??o.
 * @param v v??rtice onde ser?? inserido o v??rtice adjacente.
 * @param adjV v??rtice adjcente a ser inserido.
 */
void insertAdjVertex(vertex *v, adjacentVertex *adjV) {
    addElementLinkedList(&v->verticesAdjacentes, (void*) adjV);
    sortLinkedList(&v->verticesAdjacentes, adjVertexCompareVoid);
}

/**
 * Adiciona a uma lista de nome de linhas de um novo elemento.
 * OBS: N??o verifica se o nome da linha j?? est?? presente na lista ou n??o.
 * @param adjV v??rtice onde a nova linha ser?? adicionada.
 * @param nomeLinha nome da linha a ser adicionada.
 */
void updateNomesLinhas(adjacentVertex *adjV, char *nomeLinha) {
    addStringLinkedList(&adjV->nomesLinhas, nomeLinha);
    sortLinkedList(&adjV->nomesLinhas, compareStrVoid);
}

/**
 * Cria um grafo a partir do arquivo bin??rio passado.
 * @param filename nome do arquivo bin??rio de dados.
 * @param directedGraph diretriz para grafo ser direcional ou n??o.
 * @return retorna um ponteiro para um grafo caso tudo ocorra devidamente.
 * Retorna NULL caso ocorra alguma falha.
 */
graph* createGraphFromBIN(char *filename, int directedGraph) {

    FILE *f = fopen(filename, "rb");

    if (f == NULL) return NULL;

    HeaderRegister hr;
    readHeaderRegisterBIN(f, &hr);

    graph *g = malloc(sizeof(graph));
    createGraph(g, hr.nroEstacoes);

    DataRegister dr, dr_search, dr_return;

    while (!feof(f)) {

        if (readDataRegisterBIN(f, &dr) == NOT_REMOVED) {

            setEmptyDataRegister(&dr_search);
            dr_search.codEstacao = dr.codProxEstacao;

            if (findDataRegisterBIN(f, &dr_search, &dr_return) == REGISTER_FOUND) {
                insertEdge(g, dr.nomeEstacao, dr_return.nomeEstacao,
                           dr.distProxEstacao, dr.nomeLinha, directedGraph);
            } else if(hasVertex(*g, dr.nomeEstacao) == -1) {
                vertex *v = createVertex(dr.nomeEstacao);
                insertVertex(g, v);
            }

            dr_search.codEstacao = dr.codEstIntegra;

            if (findDataRegisterBIN(f, &dr_search, &dr_return) == REGISTER_FOUND) {
                if (strcmp(dr.nomeEstacao, dr_return.nomeEstacao) != 0) {
                    insertEdge(g, dr.nomeEstacao, dr_return.nomeEstacao,
                               0, "Integracao", directedGraph);
                }
            }
        }
    }

    return g;
}


int dijkstraAlgorithm(graph g, char *nomeOrigem, char *nomeDestino, linkedlist *caminho, int *distanciaTotal) {

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

    if (D[index].antecessor == NULL) return PATH_NOT_FOUND;

    *distanciaTotal = D[index].distancia;

    while (strcmp(nomeOrigem, g.vertices[index]->nomeEstacao) != 0) {
        addElementFirstLinkedList(caminho, g.vertices[index]->nomeEstacao);
        index = hasVertex(g, D[index].antecessor);
    }

    addElementFirstLinkedList(caminho, g.vertices[hasVertex(g, nomeOrigem)]->nomeEstacao);

    return SUCCESS;
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

    dfsRecursion(g, vOrigem, vDestino, vertices, est);

    while (est[iDestino].antecessor != NULL) {

        addElementFirstLinkedList(caminho, g.vertices[iDestino]->nomeEstacao);
        int aux = iDestino;
        iDestino = hasVertex(g, est[iDestino].antecessor);
        *distanciaTotal += est[aux].distancia;
        est[aux].antecessor = NULL;
        est[aux].distancia = -1;
    }

    addElementFirstLinkedList(caminho, g.vertices[iOrigem]->nomeEstacao);
}


typedef struct { // v??rtice
    char *nome;
    enum COLOR cor;
}V;

typedef struct { // aresta
    V *v1;
    V *v2;
    int distancia;
}A;

void printAresta(A a) {
    printf(" %s | %s | %d \n", a.v1->nome, a.v2->nome, a.distancia);
}

int compareAresta(A a1, A a2) {
    if (a1.distancia == a2.distancia) {
        if (strcmp(a1.v1->nome, a2.v1->nome) == 0) {
            return strcmp(a1.v2->nome, a2.v2->nome);
        } else return strcmp(a1.v1->nome, a2.v1->nome);
    } else return a1.distancia - a2.distancia;
}

int compareArestaVoid(void *a1, void *a2) {
    A *aresta1 = a1;
    A *aresta2 = a2;
    return compareAresta(*aresta1, *aresta2);
}

void printDFSRecursion(graph g, char *nomeOrigem, enum COLOR *vertices) {

    int index = hasVertex(g, nomeOrigem);
    vertices[index] = GRAY;

    vertex *v = g.vertices[index];
    iterator iter;
    createIterator(v->verticesAdjacentes, &iter);

    while (hasNextNode(&iter) == TRUE) {

        node *n = getNextNode(&iter);
        adjacentVertex *adjV = n->data;

        int indexAdj = hasVertex(g, adjV->nomeProxEstacao);

        if (vertices[indexAdj] == WHITE) {
            vertices[indexAdj] = GRAY;
            printf("%s, %s, %d\n", nomeOrigem, adjV->nomeProxEstacao, adjV->distancia);
            printDFSRecursion(g, adjV->nomeProxEstacao, vertices);
        }
    }

    vertices[index] = BLACK;
}

void printDFS(graph g, char *nomeOrigem) {

    enum COLOR *vertices = malloc(sizeof(enum COLOR) * g.size);
    for (int i = 0; i < g.size; i++) vertices[i] = WHITE;

    printDFSRecursion(g, nomeOrigem, vertices);
}

void primAlgorithm(graph g, char *nomeOrigem, graph *mst) {

    createGraph(mst, g.size);

    V vertices[g.size];

    linkedlist arestas;
    createLinkedList(&arestas);

    for (int i = 0; i < g.size; i++) { // cria????o dos v??rtices
        vertex *vertex1 = g.vertices[i];
        vertices[i].nome = vertex1->nomeEstacao;
        vertices[i].cor = WHITE;
    }

    for (int i = 0; i < g.size; i++) { // cria????o das arestas

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
            sortLinkedList(&arestas, compareArestaVoid);
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

            if (v1->cor == WHITE && v2->cor == WHITE) continue;

            insertEdge(mst, v1->nome, v2->nome, aresta->distancia, NULL, FALSE);
            v1->cor = BLACK;
            v2->cor = BLACK;

            removeNodeLinkedList(&arestas, n);
            percorridos++;

            break;
        }
    }
}

int comparePaths(void *path1, void *path2) {

    linkedlist *p1 = path1;
    linkedlist *p2 = path2;

    if (p1->size > p2->size) return 1;
    else if (p1->size < p2->size) return -1;

    iterator i1, i2;
    createIterator(*p1, &i1);
    createIterator(*p2, &i2);

    while (hasNextNode(&i1) == TRUE) {

        node *n1 = getNextNode(&i1);
        node *n2 = getNextNode(&i2);

        VD *vd1 = n1->data;
        VD *vd2 = n2->data;

        int ret = strcmp(vd1->nomeVertice, vd2->nomeVertice);
        if (ret > 0) return 1;
        else if (ret < 0) return -1;
    }

    return 0;
}

void findAllPathsRecursion(graph g, char *nomeOrigem, char *nomeDestino, int *isVisited, linkedlist *caminho, linkedlist *caminhos) {

    if (strcmp(nomeOrigem, nomeDestino) == 0) {
        linkedlist *l = malloc(sizeof(linkedlist));
        copyLinkedList(l, caminho);
        addElementLinkedList(caminhos, (void*) l);
        return;
    }

    int index = hasVertex(g, nomeOrigem);
    isVisited[index] = TRUE;

    vertex *vOrigem = g.vertices[index];

    iterator iter;
    createIterator(vOrigem->verticesAdjacentes, &iter);

    while (hasNextNode(&iter) == TRUE) {

        node *n = getNextNode(&iter);
        adjacentVertex *adjV = n->data;
        int indexAdj = hasVertex(g, adjV->nomeProxEstacao);

        if (isVisited[indexAdj] == FALSE) {

            VD *vd = malloc(sizeof(VD));
            vd->nomeVertice = adjV->nomeProxEstacao;
            vd->distancia = adjV->distancia;

            node *nAdd = addElementLinkedList(caminho, (void*) vd);
            findAllPathsRecursion(g, vd->nomeVertice, nomeDestino, isVisited, caminho, caminhos);
            removeNodeLinkedList(caminho, nAdd);
        }
    }

    isVisited[index] = FALSE;
}

void findAllPaths(graph g, char *nomeOrigem, char *nomeDestino, linkedlist *caminhos) {

    int isVisited[g.size];
    for (int i = 0; i < g.size; i++) isVisited[i] = FALSE;

    linkedlist caminho;
    createLinkedList(&caminho);

    VD *vdOrigem = malloc(sizeof(VD));
    vdOrigem->nomeVertice = nomeOrigem;
    vdOrigem->distancia = 0;

    addElementLinkedList(&caminho, (void*) vdOrigem);

    findAllPathsRecursion(g, nomeOrigem, nomeDestino, isVisited, &caminho, caminhos);
}

