
#include <stdio.h>
#include "headers/constantes.h"
#include "headers/linkedlist.h"
#include "headers/sort.h"

int main() {
	
	char strs[][STR_MAX_SIZE] = {{"epaminondas"}, {"bilongas"}, {"seila"}, {"aoaaaa"}};

    for(int i = 0; i < 4; i++) printf("%s\n", strs[i]);

    sortStringArray(strs, 4);

    for(int i = 0; i < 4; i++) printf("%s\n", strs[i]);

}