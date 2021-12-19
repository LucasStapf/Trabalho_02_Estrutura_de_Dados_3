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
#include <stdlib.h>
#include "display.h"
#include "commands.h"
#include "graph.h"


/**
 * @brief Funcao responsavel por ler e realizar um determinado comando passado no stdin.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void cmdSelector() {

    char inputstr[MAX_SIZE_STR];
    char *str;

    fgets(inputstr, MAX_SIZE_STR, stdin);

    char filename[MAX_SIZE_STR];
    int cmd;

    eraseCRLF(inputstr);

    str = strtok(inputstr, " ");
    cmd = atoi(str);
    str = strtok(NULL, " ");
    strncpy(filename, str, MAX_SIZE_STR);

    switch(cmd) {

        case CREATE_GRAPH:
            createGraphCommand(filename);
            break;

//        case SHORTEST_PATH:
//            selectDataTable(filename);
//            break;
//
//        case CYCLIC_PATH:
//            str = strtok(NULL, " ");
//            number = atoi(str);
//            selectDataWhereTable(filename, number);
//            break;


//        case MINIMUM_SPANNIG_TREE:
//            str = strtok(NULL, " ");
//            number = atoi(str);
//            deleteDataTable(filename, number);
//            break;
//
//        case AVAILABLE_PATHS:
//            str = strtok(NULL, " ");
//            number = atoi(str);
//            insertDataTable(filename, number);
//            break;
//
//        case updateData:
//            str = strtok(NULL, " ");
//            number = atoi(str);
//            updateDataTable(filename, number);
//            break;

        default:
            break;
    }
}

/**
 * Cria um grafo a partir de um arquivo binário e imprime esse na tela.
 * @param filename nome do arquivo de dados.
 */
void createGraphCommand(char *filename) {
    graph *g;
    if((g = createGraphFromBIN(filename, TRUE)) == NULL) showMessage(ERROR);
    else printGraph(*g);
}



/**
 * @brief Remove os caracteres '\\r' (CR) e '\\n' (LF) da string.
 *
 * @param str String de entrada.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
void eraseCRLF(char *str) {
    if(str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0'; // Tira o '\n' se houver.
    if(str[strlen(str) - 1] == '\r') str[strlen(str) - 1] = '\0'; // Tira o '\r' se houver.
}