#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif        

}

int login_gerente() {
    int i = 0;
    char senha[15]={"030201TioBolas?"};
    char tentativa[100]={0};

    while(1) {
        printf("\n\033[32m--Login do Gerente --\033[0m\n\n");
        printf("[0] - Voltar ao menu inicial\n\n");
        printf("Digite a senha (de até 15 caracteres) para ter acesso a interface de gerente:\n");
        scanf("%[^\n]%*c", tentativa);
        clear_screen();

        if(strlen(tentativa) == 1 && tentativa[0] == '0') return 0; // Caso tenha escolhido Voltar ao menu inicial.
        

        for(i=0; i<15; i++) if(senha[i]!=tentativa[i]) break;
        if(i!=15) printf("\033[31mSenha invalida, tente novamente\033[0m\n");
        else return 1; // Login deu certo.
    }
}
