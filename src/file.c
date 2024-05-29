#include "file.h"

#include <stdio.h>
#include <stdlib.h>

/* função para ler conteudo de um arquivo, lembrar de liberar da memoria o conteudo */
char * readFile(const char * nameFile) {

    FILE *file = fopen(nameFile, "r");

    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    rewind(file);

    char *content = (char*)malloc(length + 1);
    fread(content, sizeof(char), length, file);
    *(content + length) = '\0';

    fclose(file);

    return content;

}