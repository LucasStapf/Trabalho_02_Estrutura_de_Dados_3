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
#include "../headers/linkedlist.h"
#include "../headers/constants.h"

/**
 * @brief Inicializa com os valores padrao uma lista encadeada
 *
 * @param l Lista encadeada a ser inicializada.
 * 
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void createLinkedList(linkedlist *l) {
  l->size = 0;
  l->head = NULL;
}

/**
 * @brief Libera todos os nodos alocados para a lista encadeada.
 * 
 * @param l Lista encadeada a ser apagada.
 * 
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void deleteLinkedList(linkedlist *l) {

  node *n = l->head;

  while (n != NULL) {
    l->head = l->head->next;
    free(n->data);
    free(n);
    n = l->head;
  }
}

/**
 * @brief Adiciona um elemento generico na lista encadeada.
 * 
 * @param l Lista onde o elemento sera adicionado.
 * @param data Elemento generico a ser adicionado.
 * @return TRUE caso o elemento tenha sido adicionado com sucesso e FALSE caso contrario. 
 * 
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
int addElementLinkedList(linkedlist *l, void *data) {

  if(l == NULL || data == NULL) return FALSE;

  node *n = malloc(sizeof(node));
  if(n == NULL) return FALSE;

  n->data = data;
  n->next = NULL;

  if(l->head == NULL) { // Lista vazia

    l->head = n;
    l->size++;
    return TRUE;
  
  } else {

    node *aux = l->head;
    while (aux->next != NULL) aux = aux->next;
    aux->next = n;
    l->size++;
    return TRUE;
  }
}

node* getNodeLinkedList(linkedlist l, int index) {
    if (index < 0 || index >= l.size) return NULL;
    node *aux = l.head;
    for(int i = 0; i < index; i++) aux = aux->next;
    return aux;
}

int hasDataLinkedList(linkedlist l, void *data, int (*comparator)()) {
    node *aux = l.head;
    for (int i = 0; i < l.size; i++) {
        if (comparator(aux->data, data) == 0) return i;
        else aux = aux->next;
    }
    return -1; // Elemento não encontrado.
}


int hasNodeLinkedList(linkedlist l, node n, int (*comparator)()) {
    node *aux = l.head;
    for (int i = 0; i < l.size; i++) {
        if (comparator(*aux, n) == 0) return i;
        else aux = aux->next;
    }
    return -1;
}


/**
 * @brief Funcao que adiciona apenas strings em uma lista encadeada. Strings iguais nao serao
 * adicionadas.
 *
 * @param l Lista onde a string sera adicionada.
 * @param str String a ser adicionada.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void addStringLinkedList(linkedlist *l, char *str) {

  if(l == NULL || str == NULL) return;

  node *n = (node*) malloc(sizeof(node));
  if(n == NULL) return;

  n->data = malloc(sizeof(char) * MAX_SIZE_STR);

  if (n->data == NULL) {
    free(n);
    return;
  }

  n->next = NULL;
  strcpy(n->data, str);

  if(l->head == NULL) { // Lista vazia

    l->head = n;
    l->size++;
    return;

  } else {

    node *aux = l->head;

    while(aux != NULL) {

      if(strcmp(aux->data, str) == 0) {
        free(n->data);
        free(n);
        return;

      } else if(aux->next == NULL) {
        aux->next = n;
        l->size++;
        return;

      } else aux = aux->next;
    }
  }
}


int hasStringElementLinkedList(linkedlist *l, char *str) {

    int i = 0; // Elemento não encontrado.
    node *node = l->head;

    while (node != NULL) {

        char *s = (char*) node->data;
        if (strcmp(s, str) == 0) return i;
        else node = node->next;
        i++;
    }

    return -1; // Elemento não encontrado.
}

void printStringLinkedList(linkedlist l) {

  node *aux = l.head;
  while (aux != NULL) {
    printf("%s ", (char *)aux->data);
    aux = aux->next;
  }
}

void createIterator(linkedlist l, iterator *i) {
    i->list = l;
    i->current = l.head;
}

node* getNextNode(iterator *i) {
    node *n = i->current;
    if (i->current != NULL) i->current = i->current->next;
    return n;
}

int hasNextNode(iterator *i) {
    if (i->current != NULL) return TRUE;
    else return FALSE;
}

int addElementFirstLinkedList(linkedlist *l, void *data) {

    if (l == NULL) return ERROR;

    if (l->size == 0) addElementLinkedList(l, data);
    else {
        node *n = malloc(sizeof(node));
        n->data = data;
        n->next = l->head;
        l->head = n;
    }

    return SUCCESS;
}

void removeNodeLinkedList(linkedlist *l, node *n) {

    if (l == NULL || n == NULL) return;

    if (l->head == n) { // É o primeiro elemento
        l->head = n->next;
        l->size--;
    }

    node *aux = l->head;

    while (aux != NULL) {
        if (aux->next == n) {
            aux->next = n->next;
            l->size--;
            return;
        }
    }
}