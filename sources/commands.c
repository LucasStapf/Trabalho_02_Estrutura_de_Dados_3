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
#include "../headers/display.h"
#include "../headers/commands.h"
#include "../headers/graph.h"


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

    str = strtok_custom(inputstr, ' ');
    cmd = atoi(str);
    str = strtok_custom(NULL, ' ');
    strncpy(filename, str, MAX_SIZE_STR);

    switch(cmd) {

        case CREATE_GRAPH:
            createGraphCommand(filename);
            break;

        case SHORTEST_PATH:
            strtok_custom(NULL, ' ');
            char nomeOrigem[MAX_SIZE_STR], nomeDestino[MAX_SIZE_STR];
            str = strtok_custom(NULL, ' ');
            strcpy(nomeOrigem, str);
            strtok_custom(NULL, ' ');
            str = strtok_custom(NULL, ' ');
            strcpy(nomeDestino, str);
            shortestPathCommand(filename, nomeOrigem, nomeDestino);
            break;
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

void shortestPathCommand(char *filename, char *nomeOrigem, char *nomeDestino) {
    graph *g;
    if((g = createGraphFromBIN(filename, TRUE)) == NULL) showMessage(ERROR);
    else {
        linkedlist path;
        iterator iter;
        int distancia;

        if(dijkstraAlgorithm(*g, nomeOrigem, nomeDestino, &path, &distancia)
        == PATH_NOT_FOUND) {
            showMessage(PATH_NOT_FOUND);
            return;
        }

        createIterator(path, &iter);

        printf("Numero de estacoes que serao percorridas: %d\n", path.size - 1);
        printf("Distancia que sera percorrida: %d\n", distancia);

        while (hasNextNode(&iter) == TRUE) {
            node *n = getNextNode(&iter);
            char *str = n->data;
            printf("%s", str);
            if (hasNextNode(&iter) == TRUE) printf(", ");
        }
    }
}


/**
 * @brief Esta funcao possui a mesma funcionalidade da funcao original stktok da string.h,
 * porem a string nao eh quebrada no delimitador se estiver entre aspas duplas, sendo
 * quebrado o bloco inteiro de caracteres dentro das aspas.
 *
 * @param str string a ser quebrada.
 * @param delimitador char, baseado no qual eh feita a quebra da string.
 * @return ponteiro para o inicio do token valido (pedaco da string).
 *
 * @author Leonardo Hannas de Carvalho Santos
 * @author Lucas Carvalho Freiberger Stapf
 */
char *strtok_custom(char *str, char delimitador) {

    static char *pi, *pf;

    if(str != NULL) pi = pf = str;
    else pi = pf;

    if(pi == NULL) return NULL;

    int i = 0;

    if(pf[i] == delimitador) {
        for (; pf[i] == delimitador; i++);
        pi = pf = &pf[i];
    }

    for(i = 0; pf[i] != delimitador && pf[i] != '"' && pf[i] != '\0'; i++);

    if(pf[i] == delimitador) {

        pf[i] = '\0';
        pf = &pf[i + 1];
        return pi;

    } else if(pf[i] == '"') {

        pi++;
        pf++;
        for (i = 0; pf[i] != '"'; i++);
        pf[i] = '\0';
        pf = &pf[i + 1];
        return pi;

    } else {

        if (i == 0) return NULL;
        else {
            pf = NULL;
            return pi;
        }
    }
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
