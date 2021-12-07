/**
* Trabalho 02 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


typedef struct node node;
typedef struct linkedlist linkedlist;


struct node {
  void *data;
  node *next;
};

struct linkedlist {
  int size;
  node *head;
};

void createLinkedList(linkedlist *l);
void deleteLinkedList(linkedlist *l);
int addElementLinkedList(linkedlist *l, void *data);
node* getElementLinkedList(linkedlist l, int index);

void addStringLinkedList(linkedlist *l, char *str);
int hasStringElementLinkedList(linkedlist *l, char *str);
void printStringLinkedList(linkedlist l);
//void sortStringLinkedList(linkedlist *l);

#endif 