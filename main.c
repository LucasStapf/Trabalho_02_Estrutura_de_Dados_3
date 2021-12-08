
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "headers/constantes.h"
#include "headers/linkedlist.h"
#include "headers/sort.h"

int main() {

    linkedlist l;
    createLinkedList(&l);

    addStringLinkedList(&l, "uva");
    addStringLinkedList(&l, "banana");
    addStringLinkedList(&l, "abacaxi");

    printStringLinkedList(l);

    sortLinkedList(&l, strcmp);

    printStringLinkedList(l);

    printf("\n\nARRAAAAAAAAAAAY:\n");
    char **s;

    s = malloc(sizeof(char*) * 5);
    for (int i = 0; i < 5; i++) s[i] = malloc(sizeof(char) * STR_MAX_SIZE);

    strcpy(s[0], "uva");
    strcpy(s[1], "tomate");
    strcpy(s[2], "caqui");
    strcpy(s[3], "banana");
    strcpy(s[4], "ameixa");

    for (int i = 0; i < 5; i++) printf("%s\n", s[i]);

    sortArray((void**) s, 5, strcmp);

    for (int i = 0; i < 5; i++) printf("%s\n", s[i]);

}
















