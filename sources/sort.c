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
#include "../headers/constantes.h"


void sortLinkedList(linkedlist *l, int(*comparator)(void*, void*)) {

    if (l == NULL || l->size == 0) return;

    int sorted = TRUE;

    node *prevNode, *node, *aux;

    for (int i = 0; i < l->size - 1; i++) {

        prevNode = NULL;
        node = l->head;

        for (int j = 0; j < l->size - 1 - i; j++) {

            if(comparator(node->data, node->next->data) > 0) {

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


void sortStringArray(char strings[][STR_MAX_SIZE], int size) {

    if (strings == NULL || size == 0) return;
    int sorted = TRUE;


    char strAux[STR_MAX_SIZE];

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {

                sorted = FALSE;
                strcpy(strAux, strings[j]);

                strcpy(strings[j], strings[j + 1]);
                strcpy(strings[j + 1], strAux);
            }
        }
        if (sorted == TRUE) return;
    }
}