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
#include "../headers/binmanager.h"
#include "../headers/linkedlist.h"
#include "../headers/constants.h"
#include "../headers/commands.h"
#include "../headers/registers.h"
#include "../headers/display.h"

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

    char filename[MAX_SIZE_STR], destinationfilename[MAX_SIZE_STR];
    int cmd;
    int number;

    eraseCRLF(inputstr);

    str = strtok(inputstr, " ");
    cmd = atoi(str);
    str = strtok(NULL, " ");
    strncpy(filename, str, MAX_SIZE_STR);

    switch(cmd) {

        case createGraph:
            createGraphFromBIN(filename);
            break;

//        case selectData:
//            selectDataTable(filename);
//            break;
//
//        case selectDataWhere:
//            str = strtok(NULL, " ");
//            number = atoi(str);
//            selectDataWhereTable(filename, number);
//            break;
//
//        case deleteData:
//            str = strtok(NULL, " ");
//            number = atoi(str);
//            deleteDataTable(filename, number);
//            break;
//
//        case insertData:
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

void createGraphFromBIN(char *filename) {

}