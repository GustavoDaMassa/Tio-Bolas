#include <stdio.h>
#include <string.h>

int login_gerente() {
    int i = 0;
    char senha[15]={"030201TioBolas?"};
    char tentativa[100]={0};

    while(1) {
        printf("\nBem vinde a sorveteria Tio Bolas!\n\n");
        printf("[0] Voltar ao menu inicial\n");
        printf("Digite a senha (de até 15 caracteres) para ter acesso a interface de gerente:\n");
        scanf("%[^\n]%*c", tentativa);

        if(strlen(tentativa) == 1 && tentativa[0] == '0') return 0; // Caso tenha escolhido Voltar ao menu inicial.
        

        for(i=0; i<15; i++) if(senha[i]!=tentativa[i]) break;
        if(i!=15) printf("Senha invalida, tente novamente\n");
        else return 1; // Login deu certo.
    }
}