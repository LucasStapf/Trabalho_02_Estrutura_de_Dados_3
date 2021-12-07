
#include <stdio.h>
#include "headers/linkedlist.h"

int main() {
	
	linkedlist strings;
	createLinkedList(&strings);

    addStringLinkedList(&strings, "etanol");
    addStringLinkedList(&strings, "uva");
	addStringLinkedList(&strings, "banana");
	addStringLinkedList(&strings, "abacaxi");
    addStringLinkedList(&strings, "zebra");


    printStringLinkedList(strings);

    printf("%d \n", strings.size);

    sortStringLinkedList(&strings);

    printStringLinkedList(strings);
}