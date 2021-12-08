/**
* Trabalho 02 - Estrutura de Dados III
*
* Integrantes do grupo:
*
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef SORT_H
#define SORT_H

#include "constantes.h"
#include "linkedlist.h"

void sortStringLinkedList(linkedlist *l);
void sortStringArray(char strings[][STR_MAX_SIZE], int size);

#endif
