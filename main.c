#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/constants.h"
#include "headers/linkedlist.h"
#include "headers/sort.h"
#include "graph.h"


int main() {

    graph *g = createGraphFromBIN("C:\\Users\\lucas\\CLionProjects\\Trabalho_02___Estrutura_de_Dados_3\\binarios\\estacao1.bin", FALSE);
//    printGraph(*g);
//    printf("\n\n\n");
    graph mst;
    primAlgorithm(*g, "Bras", &mst);
//    printGraph(mst);
//    printf("\n\n\n");
    printDFS(mst, "Bras");
}
















