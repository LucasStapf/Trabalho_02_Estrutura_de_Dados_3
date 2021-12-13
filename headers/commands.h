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

/**
 * @brief Constantes para identificao dos comandos digitados.
 */
enum command {

  createGraph = 7,
  selectData, 
  selectDataWhere, 
  deleteData, 
  insertData, 
  updateData

};

void cmdSelector();

void createGraphFromBIN(char *filename);


void binarioNaTela(char *nomeArquivoBinario);

char* strtok_custom(char* str, char delimitador);
void eraseCRLF(char *str);

#endif

