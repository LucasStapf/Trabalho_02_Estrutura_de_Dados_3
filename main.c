
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "headers/constantes.h"
#include "headers/linkedlist.h"
#include "headers/sort.h"
#include "graph.h"

int main() {

    graph g;
    createGraph(&g, 5);
    insertEdge(&g, "Luz", "Bras", 100, "azul");
    insertEdge(&g, "Luz", "Se", 130, "amarela");
    insertEdge(&g, "Luz", "Bras", 100, "amarela");

    printf("Tamanho do grafo: %d\n", g.size);
    printGraph(g);
}
















