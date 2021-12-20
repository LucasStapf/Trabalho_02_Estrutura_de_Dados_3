#include "../headers/commands.h"
#include <stdio.h>
#include "sort.h"

int main() {

    linkedlist caminhos;
    createLinkedList(&caminhos);
    graph *g = createGraphFromBIN("C:\\Users\\lucas\\CLionProjects\\Trabalho_02___Estrutura_de_Dados_3\\binarios\\estacao1.bin", TRUE);
    findAllPaths(*g, "Palmeiras-Barra Funda", "Se", &caminhos);
    iterator iter;
    createIterator(caminhos, &iter);

    while (hasNextNode(&iter) == TRUE) {

        node *n = getNextNode(&iter);
        linkedlist *l = n->data;
        iterator iter2;
        createIterator(*l, &iter2);

        while (hasNextNode(&iter2) == TRUE) {

            node *n2 = getNextNode(&iter2);
            VD *vd = n2->data;
            printf("%s, ", vd->nomeVertice);
        }

        printf("\n\n");
    }

    printf("QNT CAMINHOS: %d\n", caminhos.size);


    sortLinkedList(&caminhos, comparePaths);

    createIterator(caminhos, &iter);

    while (hasNextNode(&iter) == TRUE) {

        node *n = getNextNode(&iter);
        linkedlist *l = n->data;
        iterator iter2;
        createIterator(*l, &iter2);

        while (hasNextNode(&iter2) == TRUE) {

            node *n2 = getNextNode(&iter2);
            VD *vd = n2->data;
            printf("%s, ", vd->nomeVertice);
        }

        printf("\n\n");
    }
//    minimumSpannigTreeCommand("C:\\Users\\lucas\\CLionProjects\\Trabalho_02___Estrutura_de_Dados_3\\binarios\\estacao1.bin", "Bras");
//    cyclicPathCommand("C:\\Users\\lucas\\CLionProjects\\Trabalho_02___Estrutura_de_Dados_3\\binarios\\estacao1.bin", "Luz");
//    shortestPathCommand("C:\\Users\\lucas\\CLionProjects\\Trabalho_02___Estrutura_de_Dados_3\\binarios\\estacao4.bin", "Vila Prudente", "Sao Mateus");
//    createGraphCommand("C:\\Users\\lucas\\CLionProjects\\Trabalho_02___Estrutura_de_Dados_3\\binarios\\estacao1.bin");
//    cmdSelector();
}
















