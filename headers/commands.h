/**
* Trabalho 02 - Estrutura de Dados III
*
* Integrantes do grupo:
* 
* Leonardo Hannas de Carvalho Santos  NUSP: 11800480
* Lucas Carvalho Freiberger Stapf     NUSP: 11800559
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include "graph.h"

/**
 * @brief Constantes para identificao dos comandos digitados.
 */
enum command {

  CREATE_GRAPH = 7,
  SHORTEST_PATH,
  CYCLIC_PATH,
  deleteData, 
  insertData, 
  updateData

};

void cmdSelector();

graph* createGraphFromBIN(char *filename, int directedGraph);


void binarioNaTela(char *nomeArquivoBinario);

char* strtok_custom(char* str, char delimitador);
void eraseCRLF(char *str);

#endif

