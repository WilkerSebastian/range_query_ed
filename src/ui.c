#include "ui.h"

#include <stdio.h>

int8_t main_menu() {

    int8_t opcao = 0;

    printf("1) realizar query\n0) Sair\nescolha uma opção: ");
    scanf("%hhd", &opcao);

    while (opcao < EXIT || opcao > QUERY) {
        clear();
        printf("opção inválida\n");
        printf("1) realizar query\n0) Sair\nescolha uma opção: ");
        scanf("%hhd", &opcao);
    }

    clear();

    return opcao;

}

void clear() {
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}