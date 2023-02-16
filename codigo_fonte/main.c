#include "end.h"
#include "arquivos.h"
#include "pedido.h"
#include "produto.h"
#include "menu.h"
#include <unistd.h>
#include <stdlib.h>

int main(){
    int num = -1;

    clear_screen();

    /*
    Função que registra uma função para ser executada ao fim do programa
    mesmo que o programa seja encerrado por um return na main ou por um exit em qualquer lugar do código.
    */
    atexit(end_program); 

    abrir_arquivos();

    load_cardapio();
    load_clientes();

    h = (Head *) malloc(sizeof(Head));
    if (!h) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    h->ini = NULL;

    while(1) {
        num = -1;
        printf("\033[32m\n\nBem vinde a sorveteria Tio Bolas!\033[0m\n\n");
        printf("Digite um numero para escolher qual interface deseja acessar:\n\n");
        printf("[1] - Interface do Atendente\n");
        printf("[2] - Interface do Gerente\n");
        printf("[0] - Terminar programa\n");
        scanf("%d%*c", &num);
        clear_screen();

        if(num==1){
            while(1){
                num = -1;
                printf("\n\033[32m-- interface do atendente --\033[0m\n\n");
                printf("O que você deseja fazer?\n\n");
                printf("[1] - Iniciar um novo pedido\n");
                printf("[2] - Verificar pedidos em andamento\n");
                printf("[3] - Concluir pedidos\n");
                printf("[4] - Cancelar um pedido\n");
                printf("[5] - Voltar ao menu inicial\n");
                printf("[0] - Terminar programa\n");
                scanf("%d%*c", &num);
                clear_screen();
                
                if(num == 1) inserir_pedido();
                else if(num == 2) pedidos_andamento();
                else if(num == 3) concluir_pedido();
                else if(num == 4) cancelar_pedido();
                else if(num == 5) break;
                else if(num == 0) return 0;
                else printf("\033[31mOpção inválida\033[0m\n");
                
            }
            if(num == 3) continue;
            
        }
        if(num==2){            

            if(login_gerente() == 0) continue; // Caso o usuário tenha escolhido Voltar ao menu inicial ao logar.
            while(1){
                num = -1;
                printf("\n\033[32m-- Interface do Gerente --\033[0m\n\n");

                printf("Acesso liberado, o que deseja fazer?\n");
                printf("[1] - Ver cardápio\n");
                printf("[2] - Ver clientes\n");
                printf("[3] - Ver historico de pedidos\n");
                printf("[4] - Voltar ao menu inicial\n");
                printf("[0] - Terminar o programa\n");
                scanf("%d%*c", &num);
                clear_screen();
                

                if(num == 1) ver_cardapio();
                else if(num == 4) break;
                else if(num == 0) return 0;
                else printf("\033[31mOpção inválida\033[0m\n");
                
            
            
            }
            if (num == 6) continue;

        }
        if(num == 0) break;
        else printf("\033[31mOpção inválida\033[0m\n");
    }
    


    return 0;
}

