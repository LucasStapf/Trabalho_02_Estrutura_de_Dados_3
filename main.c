
#include <stdio.h>
#include <string.h>
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

    sortLinkedList(&l, &strcmp);

    printStringLinkedList(l);
}