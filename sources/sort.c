/**
* Trabalho 02 - Estrutura de Dados III
*
* Integrantes do grupo:
*
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#include <stdio.h>
#include <string.h>
#include "../headers/sort.h"

// bubble otimizado
void sortStringLinkedList(linkedlist *l) {

    if (l == NULL || l->size == 0) return;

    int sorted = TRUE;

    node *prevNode, *node, *aux;

    for (int i = 0; i < l->size - 1; i++) {

        prevNode = NULL;
        node = l->head;

        for (int j = 0; j < l->size - 1 - i; j++) {

            if(strcmp(node->data, node->next->data) > 0) {

                sorted = FALSE;

                aux = node->next;
                node->next = node->next->next;
                aux->next = node;

                if (j == 0) l->head = prevNode = aux;
                else prevNode->next = aux;

                prevNode = aux;

            } else {

                prevNode = node;
                node = node->next;

            }
        }

        if (sorted == TRUE) return;
    }
}