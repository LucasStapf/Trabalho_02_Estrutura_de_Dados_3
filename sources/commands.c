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
#include <malloc.h>
#include "commands.h"
#include "binmanager.h"
#include "graph.h"


/**
 * @brief Funcao responsavel por ler e realizar um determinado comando passado no stdin.
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
//void cmdSelector() {
//
//    char inputstr[MAX_SIZE_STR];
//    char *str;
//
//    fgets(inputstr, MAX_SIZE_STR, stdin);
//
//    char filename[MAX_SIZE_STR], destinationfilename[MAX_SIZE_STR];
//    int cmd;
//    int number;
//
//    eraseCRLF(inputstr);
//
//    str = strtok(inputstr, " ");
//    cmd = atoi(str);
//    str = strtok(NULL, " ");
//    strncpy(filename, str, MAX_SIZE_STR);
//
//    switch(cmd) {
//
//        case CREATE_GRAPH:
//            createGraphFromBIN(filename);
//            break;
//
////        case selectData:
////            selectDataTable(filename);
////            break;
////
////        case selectDataWhere:
////            str = strtok(NULL, " ");
////            number = atoi(str);
////            selectDataWhereTable(filename, number);
////            break;
////
////        case deleteData:
////            str = strtok(NULL, " ");
////            number = atoi(str);
////            deleteDataTable(filename, number);
////            break;
////
////        case insertData:
////            str = strtok(NULL, " ");
////            number = atoi(str);
////            insertDataTable(filename, number);
////            break;
////
////        case updateData:
////            str = strtok(NULL, " ");
////            number = atoi(str);
////            updateDataTable(filename, number);
////            break;
//
//        default:
//            break;
//    }
//}

void createGraphFromBIN(char *filename) {

    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return; // arrumar
    }

    HeaderRegister hr;
    readHeaderRegisterBIN(f, &hr);

    graph g;
    createGraph(&g, hr.nroEstacoes);

    DataRegister dr, dr_search, dr_return;

    while (!feof(f)) {

        if (readDataRegisterBIN(f, &dr) == NOT_REMOVED) {

            setEmptyDataRegister(&dr_search);
            dr_search.codEstacao = dr.codProxEstacao;

            if (findDataRegisterBIN(f, &dr_search, &dr_return) == REGISTER_FOUND) {
                insertEdge(&g, dr.nomeEstacao, dr_return.nomeEstacao,
                           dr.distProxEstacao, dr.nomeLinha);
            } else if(hasVertex(g, dr.nomeEstacao) == -1) {

                vertex *v = malloc(sizeof(vertex));
                strcpy(v->nomeEstacao, dr.nomeEstacao);
                createLinkedList(&v->verticesAdjacentes);

                insertVertex(&g, v);
            }

            dr_search.codEstacao = dr.codEstIntegra;

            if (findDataRegisterBIN(f, &dr_search, &dr_return) == REGISTER_FOUND) {
                if (strcmp(dr.nomeEstacao, dr_return.nomeEstacao) != 0) {
                    insertEdge(&g, dr.nomeEstacao, dr_return.nomeEstacao,
                               0, "Integração");
                }
            }
        } else {

        }
    }

    printGraph(g);
}