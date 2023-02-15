#include "pedido.h"
#include "cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

Head * h = NULL;
extern Clients * cli;

void inserir_pedido() {
    int i;
    Pedido * p = NULL;
    Pedido * aux = NULL;
    Cliente * c = NULL;
    int preco;

    p = (Pedido *) malloc(sizeof(Pedido));
    if(!p) {
        perror("Erro de alocação.");
        exit(1);
    }
    p->cliente = NULL;
    p->produtos = NULL;
    p->prox = NULL;
    c = (Cliente *) malloc(sizeof(Cliente));
    if(!c) {
        perror("Erro de alocação.");
        free(p);
        exit(1);
    }

    print_clientes();

    if(escolher_cliente(c) == 1) {
        free(c);
        free(p);
        return;
    }

    print_clientes();

    if(escolher_produtos(p) == 1) {
        free(c);
        free(p);
        return;
    }

    p->cliente = c;
    
    preco = 0;
    for (i = 0; i < (p->qtd_p); i++) preco += p->produtos[i].preco * p->produtos[i].qtd;
    p->preco_t = preco;
    
    if (h->ini == NULL) h->ini = p;
    else {
        aux = h->ini;
        while(1) {
            if(aux->prox == NULL) break;
            aux = aux->prox;
        }
        aux->prox = p;
    }
    

}

// 0 se o cliente foi escolhido com sucesso, 1 se houve desistência no processo.
int escolher_cliente(Cliente * c) {
    int num = -1;
    int num2 = -1;
    int tam;
    int aux;
    char nome[101] = {0};

    while(1) {
        num = -1;
        printf("///////////////////////////////////////////\n");
        printf("O cliente possui cadastro?\n");
        printf("[1] Sim\n");
        printf("[2] Não ou não sabe\n");
        printf("[0] Cancelar registro de pedido\n");
        scanf("%d%*c", &num);
        sleep(0.1);


        if(num == 0) return 1;
        else if(num == 1) {
            while(1) {
                memset(nome, 0, sizeof(char));
                printf("[0] Cancelar registro de pedido\n");
                printf("[1] Voltar\n");
                printf("Digite o nome do cliente: ");
                scanf("%[^\n]%*c", nome);

                tam = strlen(nome);
                if(tam == 1 && nome[0] == '0') return 1;
                else if(tam == 1 && nome[0] == '1') break;
                else if(nome[0] == '\0') {
                    printf("Nome inválido, você não digitou um nome.\n");
                    continue;
                }

                aux = busca_cliente(nome);
                if(aux == 0) {
                    printf("Não foi encontrado um cliente com esse nome\n");
                    continue;
                }
                else {
                    *(c) = cli->clis[aux-1];
                    return 0;
                }
            }
        }
        else if(num == 2) {
            while(1) {
                num2 = -1;
                printf("O cliente deseja fazer cadastro?\n");
                printf("[1] Sim\n");
                printf("[2] Não\n");
                printf("[0] Cancelar registro de pedido\n");
                scanf("%d%*c", &num2);

                if(num2 == 0) return 1;
                else if(num2 == 1) {
                    if(cadastrar_cliente(c) == 0) return 0; // Caso o cliente tenha sido cadastrado com sucesso.
                    else continue; // Caso tenha desistido do cadastro, apenas volta para essa página, já que ainda não desistiu do pedido.
                }
                else if(num2 == 2) {
                    while(1) {
                        if(pick_name(nome) == 1) return 1;
                        if(check_cli_name(nome) == 0) {
                            strcpy(c->nome, nome);
                            c->cadastro = 0;
                            return 0;
                        }
                    }

                }
                else printf("Opção inválida\n");
            }
            break;
        }
        else printf("Opção inválida\n");
        sleep(0.3);
    }
}

int escolher_produtos(Pedido * p) {
    int num = -1;
    int qtd_p = 0;
    int qtd;

    if(cli->qtd == 0) {
        printf("Não há produtos no cardápio para serem escolhidos, cancelando pedido\n");
        return 1;
    }

    while(1) {
        num = -1;
        print_cardapio();
        printf("/////////////////////////////////////////////\n");
        printf("[0] Cancelar registro de pedido\n");
        printf("[-1] Terminar registro de produtos\n");
        printf("Digite o id do produto que deseja adicionar no pedido: \n");
        scanf("%d%*c", &num);

        if(num == 0) return 1;
        if(num == -1) return 0;
        else if(num >= 1 && num <= (car->qtd)) {
            while(1) {
                qtd = -1;
                printf("[0] Voltar\n");
                printf("Quantas unidades desse produto o cliente deseja?\n");
                scanf("%d%*c", &qtd);

                if(num == 0) break;
                else if(qtd >= 1) {
                    qtd_p++;
                    p->qtd_p = qtd_p;
                    p->produtos = (Produto_ped *) realloc(p->produtos, qtd_p*sizeof(Produto_ped));
                    if(!(p->produtos)) {
                        perror("Erro de alocação");
                        free(p);
                        exit(1);
                    }
                    p->produtos[qtd_p-1].id = num;
                    *(p->produtos[qtd_p-1].nome) = *(car->prods[qtd_p-1].nome);
                    p->produtos[qtd_p-1].preco = car->prods[qtd_p-1].preco;
                    p->produtos[qtd_p-1].qtd = qtd;                       
                }
                else printf("Número inválido de unidades.\n");
            }
        }
        else printf("Opção inválida\n");
    }

}


// 0 se ocorreu tudo bem, 1 se desistiu do processo.
int pick_name(char * s) {
    char buffer[1000];
    int carac;

    while(1) {
        memset(buffer, 0, sizeof(char)); 
        /* Testamos e vimos que caso o usuário apenas aperte enter o nome será o que já estava na buffer, 
        que poderia ser um "lixo" qualquer, para garantir que esse lixo não seja considerado como nome ou
        que o nome inválido digitado anteriormente apresente o erro errado, então limpamos o primeiro char
        para \0, indicando o final da string, fazendo com que o texto de buffer sempre será inicialmente vazio.
        */

        printf("[0] Cancelar\n");
        printf("Escolha o nome (Até 100 caracteres): ");
        scanf("%[^\n]%*c", buffer);
        
        carac = strlen(buffer);
        if(!carac) {
            printf("Erro: você não digitou o nome.\n");
            continue;
        }
        else if(carac > 100) { // Caso o nome tenha mais de 100 caracteres.
            printf("Nome inválido, o nome tem mais de 100 caracteres.\n");
            continue;
        }
        else if (buffer[0] == '0') return 1; // Caso tenha cancelado.
        
        else {
            strcpy(s, buffer);
            return 0;
        }
    }

}
