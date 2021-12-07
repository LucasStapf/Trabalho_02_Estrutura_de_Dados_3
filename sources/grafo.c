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
#include "../headers/grafo.h"

int criarGrafo(grafo *g, int tamanho) {
    
    g->vertices = malloc(sizeof(vertice) * tamanho);
    if (g->vertices == NULL) return ERROR;
    g->tamanho = tamanho;

    for (int i = 0; i < tamanho; i++) g->vertices[i].nomeEstacao[0] = '\0';
    
    return SUCCESS;
}

int inserirAresta(grafo *g, char *verticeOrigem, char *verticeDestino, int distancia, char *nomeLinha) {

}
