#include "end.h"
#include "arquivos.h"
#include "pedido.h"
#include "produto.h"
#include <unistd.h>
#include <stdlib.h>

int main(){
    int num = -1, c=0;
    char senha[15]={"030201TioBolas?"};
    char tentativa[100]={0};

    /*
    Função que registra uma função para ser executada ao fim do programa
    mesmo que o programa seja encerrado por um return na main ou por um exit em qualquer lugar do código.
    */
    atexit(end_program); 

    abrir_arquivos();

    load_cardapio();

    h = (Head *) malloc(sizeof(Head));
    if (!h) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    while(1) {
        printf("\nBem vinde a sorveteria Tio Bolas!\n\n");
        printf("Digite um numero para escolher qual interface deseja acessar:\n");
        printf("[1] Interface do Atendente\n");
        printf("[2] Interface do Gerente\n");
        printf("[0] Terminar programa\n");
        scanf("%d%*c", &num);
        sleep(0.1);

        if(num == 1 || num == 2 || num == 0) break;
        else printf("Opção inválida\n");
    }

    if(num==1){
        while(1){
            printf("\nBem vinde a sorveteria Tio Bolas!\n\n");
            printf("O que você deseja fazer?\n");
            printf("[1] Iniciar um novo pedido\n");
            printf("[2] Verificar pedidos em andamento\n");
            printf("[3] Voltar ao menu inicial\n");
            printf("[0] Terminar programa\n");
            scanf("%d%*c", &num);
            sleep(0.1);

            if(num == 1 || num == 2 || num == 0 || num == 3) break;
            else printf("Opção inválida\n");
        }

        if(num == 1){

        }
        else if(num == 2){

        }
        else if(num == 3){
            
        }
        else if(num == 0){
            
        }
    }
    if(num==2){
        while(1){
            printf("\nBem vinde a sorveteria Tio Bolas!\n\n");
            printf("Digite a senha (de até 15 caracteres) para ter acesso a interface de gerente:\n");
            scanf("%s", tentativa);

            for(c=0; c<15; c++) if(senha[c]!=tentativa[c]) break;
            
            if(c!=15) printf("Senha invalida, tente novamente\n");
            else {
                while(1){
                    printf("\nBem vinde a sorveteria Tio Bolas!\n\n");
                    printf("Acesso liberado, o que deseja fazer?\n");
                    printf("[1] Ver cardápio\n");
                    printf("[2] Ver o estoque\n");
                    printf("[3] Ver finanças\n");
                    printf("[4] Ver clientes\n");
                    printf("[5] Ver historico de pedidos\n");
                    printf("[6] Voltar ao menu inicial\n");
                    printf("[0] Terminar o programa\n");
                    scanf("%d%*c", &num);
                    sleep(0.1);

                    if(num == 1) ver_cardapio();
                    else printf("Opção inválida\n");
                    printf("aaaaaa\n");
                }
            
            }
        }

    }


    return 0;
}