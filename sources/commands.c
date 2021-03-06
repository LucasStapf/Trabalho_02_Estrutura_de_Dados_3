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
#include "../headers/sort.h"


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

        case CYCLIC_PATH:
            strtok_custom(NULL, ' ');
            str = strtok_custom(NULL, ' ');
            cyclicPathCommand(filename, str);
            break;


        case MINIMUM_SPANNIG_TREE:
            strtok_custom(NULL, ' ');
            str = strtok_custom(NULL, ' ');
            minimumSpannigTreeCommand(filename, str);
            break;

        case ALL_AVAILABLE_PATHS:
            strtok_custom(NULL, ' ');
            char strOrigem[MAX_SIZE_STR], strDestino[MAX_SIZE_STR];
            str = strtok_custom(NULL, ' ');
            strcpy(strOrigem, str);
            strtok_custom(NULL, ' ');
            str = strtok_custom(NULL, ' ');
            strcpy(strDestino, str);
            allAvailablePathsCommand(filename, strOrigem, strDestino);
            break;

        default:
            break;
    }
}

/**
 * Cria um grafo a partir de um arquivo bin??rio e imprime esse na tela.
 * @param filename nome do arquivo de dados.
 */
void createGraphCommand(char *filename) {
    graph *g;
    if((g = createGraphFromBIN(filename, TRUE)) == NULL) showMessage(ERROR);
    else printGraph(*g);
}

/**
 * Cria um grafo a partir de um arquivo de dados e utiliza o algortimo de Dijkstra para encontrar, se existir, o menor caminho entre duas esta????es.
 * Caso houver um caminho, este ser?? printado conforme especifica????o do trabalho.
 * @param filename nome do arquivo bin??rio de dados.
 * @param nomeOrigem nome da esta????o de partida.
 * @param nomeDestino nome da esta????o de chegada.
 */
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


void cyclicPathCommand(char *filename, char *nomeOrigem) {

    graph *g;

    if((g = createGraphFromBIN(filename, TRUE)) == NULL) showMessage(ERROR);
    else {

        linkedlist path;
        iterator iter;
        int distancia;
        dfsAlgorithm(*g, nomeOrigem, nomeOrigem, &path, &distancia);
        createIterator(path, &iter);

        if (path.size == 1) {
            showMessage(CYCLE_NOT_FOUND);
            return;
        }

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

void minimumSpannigTreeCommand(char *filename, char *nomeOrigem) {

    graph *g;

    if((g = createGraphFromBIN(filename, TRUE)) == NULL) showMessage(ERROR);
    else {
        graph mst;
        primAlgorithm(*g, nomeOrigem, &mst);
        printDFS(mst, nomeOrigem);
    }
}

void allAvailablePathsCommand(char *filename, char *nomeOrigem, char *nomeDestino) {

    graph *g;

    if((g = createGraphFromBIN(filename, TRUE)) == NULL) showMessage(ERROR);
    else {


        linkedlist caminhos;
        createLinkedList(&caminhos);

        findAllPaths(*g, nomeOrigem, nomeDestino, &caminhos);

        if (caminhos.size == 0) {
            showMessage(PATH_NOT_FOUND);
            return;
        }

        sortLinkedList(&caminhos, comparePaths);

        iterator iter;
        createIterator(caminhos, &iter);

        while (hasNextNode(&iter) == TRUE) {

            node *n = getNextNode(&iter);
            linkedlist *l = n->data;

            iterator iter2;

            printf("Numero de estacoes que serao percorridas: %d\n", l->size - 1);
            int distancia = 0;

            createIterator(*l, &iter2);
            while (hasNextNode(&iter2) == TRUE) {
                node *n2 = getNextNode(&iter2);
                VD *vd = n2->data;
                distancia += vd->distancia;
            }

            printf("Distancia que sera percorrida: %d\n", distancia);

            createIterator(*l, &iter2);
            while (hasNextNode(&iter2) == TRUE) {

                node *n2 = getNextNode(&iter2);
                VD *vd = n2->data;
                if (hasNextNode(&iter2) == TRUE) printf("%s, ", vd->nomeVertice);
                else printf("%s", vd->nomeVertice);
            }

            printf("\n\n");
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
