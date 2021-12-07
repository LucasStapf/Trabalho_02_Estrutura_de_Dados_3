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


typedef struct verticeAdjcente {
    char nomeProxEstacao[STR_MAX_SIZE];
    int distancia;
    linkedlist nomesLinhas;
} verticeAdjcente;

typedef struct vertice {
    char nomeEstacao[STR_MAX_SIZE];
    linkedlist verticesAdjacentes;
} vertice;


typedef struct grafo {
    int tamanho;
    vertice *vertices;
} grafo;


int criarGrafo(grafo *g, int tamanho);
int inserirAresta(grafo *g, char *verticeOrigem, char* verticeDestino, int distancia, char *nomeLinha);



#endif