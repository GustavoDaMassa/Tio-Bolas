#include "pedido.h"
#include "cliente.h"
#include "arquivos.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

Head * h = NULL;
extern Clients * cli;

void inserir_pedido() {
    int i;
    int num;
        
    
    Pedido * p = NULL;
    Pedido * aux = NULL;
    Cliente * c = NULL;
    int preco = 0;

    p = (Pedido *) malloc(sizeof(Pedido));
    if(!p) {
        perror("\033[33mErro de alocação.\033[0m\n");
        exit(1);
    }
    p->qtd_p = 0;
    p->cliente = NULL;
    p->produtos = NULL;
    p->prox = NULL;
    c = (Cliente *) malloc(sizeof(Cliente));
    if(!c) {
        perror("\033[33mErro de alocação.\033[0m\n");
        free(p);
        exit(1);
    }

    if(escolher_cliente(c) == 1) {
        free(c);
        free(p);
        return;
    }

    p->cliente = (Cliente *) malloc(sizeof(Cliente));
    if(!(p->cliente)) {
        perror("\033[33mErro de alocação.\033[0m\n");
        free(p);
        free(c);
        exit(1);
    }
    print_clientes();

    if(escolher_produtos(p) == 1) {
        free(c);
        free(p->cliente);
        free(p);
        return;
    }

    *(p->cliente) = *(c);

    free(c);
    
    preco = 0;
    for (i = 0; i < (p->qtd_p); i++) preco = preco + (p->produtos[i].preco * p->produtos[i].qtd);

    p->preco_t = preco;

    while(1) {
        num = -1;
        print_pedido(p);
        printf("------------------------------------\n");
        printf("[0] - Cancelar registro de pedido\n");
        printf("[1] - Confirmar registro de pedido\n\n");
        printf("Os dados do pedido estão certos?\n");
        scanf("%d%*c", &num);
        clear_screen();

        if(num == 0) {
            free(p->cliente);
            free(p->produtos);
            free(p);
            free(c);
            return;
        }
        else if(num == 1) {
            break;
        }
        else printf("\033[31mOpção inválida\033[0m\n");
    }

    if (h->ini == NULL) {
        h->ini = p;
    }    
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
        printf("---------------------------------------\n");
        printf("O cliente possui cadastro?\n\n");
        printf("[1] - Sim\n");
        printf("[2] - Não ou não sabe\n");
        printf("[0] - Cancelar registro de pedido\n");
        scanf("%d%*c", &num);
        clear_screen();


        if(num == 0) return 1;
        else if(num == 1) {
            while(1) {
                memset(nome, 0, sizeof(char));
                printf("[0] - Cancelar registro de pedido\n");
                printf("[1] - Voltar\n\n");
                printf("Digite o nome do cliente: ");
                scanf("%[^\n]%*c", nome);
                clear_screen();

                strupper(nome);

                tam = strlen(nome);
                if(tam == 1 && nome[0] == '0') return 1;
                else if(tam == 1 && nome[0] == '1') break;
                else if(nome[0] == '\0') {
                    printf("\033[31mNome inválido, você não digitou um nome.\033[0m\n");
                    continue;
                }

                aux = busca_cliente(nome);
                if(aux == 0) {
                    printf("\033[31mNão foi encontrado um cliente com esse nome\033[0m\n");
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
                printf("[1] - Sim\n");
                printf("[2] - Não\n");
                printf("[0] - Cancelar registro de pedido\n");
                scanf("%d%*c", &num2);
                clear_screen();

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
                else printf("\033[31mOpção inválida\033[0m\n");
            }
            break;
        }
        else printf("\033[31mOpção inválida\033[0m\n");
    }
}

int escolher_produtos(Pedido * p) {
    int num = -1;
    int qtd_p = 0;
    int qtd;

    if(cli->qtd == 0) {
        printf("\033[33mNão há produtos no cardápio para serem escolhidos, cancelando pedido\033[0m\n");
        return 1;
    }

    while(1) {
        num = -1;
        print_cardapio();
        printf("---------------------------------------\n");
        printf("[0] - Cancelar registro de pedido\n");
        printf("[-1] - Terminar registro de produtos\n\n");
        printf("Digite o id do produto que deseja adicionar no pedido: \n");
        scanf("%d%*c", &num);
       

        if(num == 0) return 1;
        if(num == -1) return 0;
        else if(num >= 1 && num <= (car->qtd)) {
            while(1) {
                qtd = -1;
                printf("[0] - Voltar\n\n");
                printf("Quantas unidades desse produto o cliente deseja?\n");
                scanf("%d%*c", &qtd);
                clear_screen();

                if(qtd == 0) break;
                else if(qtd >= 1) {
                    qtd_p++;
                    p->qtd_p = qtd_p;
                    printf("qtd_p: %d\n", p->qtd_p);
                    p->produtos = (Produto_ped *) realloc(p->produtos, qtd_p*sizeof(Produto_ped));
                    if(!(p->produtos)) {
                        perror("\033[33mErro de alocação\033[0m");
                        free(p);
                        exit(1);
                    }
                    p->produtos[qtd_p-1].id = num;
                    strcpy(p->produtos[qtd_p-1].nome, car->prods[num-1].nome);
                    p->produtos[qtd_p-1].preco = car->prods[num-1].preco;
                    p->produtos[qtd_p-1].qtd = qtd;
                    break;                       
                }
                else printf("\033[31mNúmero inválido de unidades.\033[0m\n");
            }
        }
        else printf("\033[31mOpção inválida\033[0m\n");
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

        printf("[0] - Cancelar\n\n");
        printf("Escolha o nome (Até 100 caracteres): ");
        scanf("%[^\n]%*c", buffer);
        clear_screen();
        
        carac = strlen(buffer);
        if(!carac) {
            printf("\033[31mErro: voce nao digitou o nome.\033[0m\n");
            continue;
        }
        else if(carac > 100) { // Caso o nome tenha mais de 100 caracteres.
            printf("\033[31mNome invalido, o nome tem mais de 100 caracteres.\033[0m\n");
            continue;
        }
        // else if (check_cli_name(buffer) == 1)printf("Nome invalido, possui caracteres especiais ou numeros.\n");
        else if (buffer[0] == '0') return 1; // Caso tenha cancelado.
        
        else {
            strcpy(s, buffer);
            return 0;
        }
    }

}

void print_pedido(Pedido * p) {

    int i;

    printf("Quantidade de produtos diferentes: %d\n", p->qtd_p);
    printf("Produtos:\n");
    for(i = 0; i < (p->qtd_p); i++) {
        printf("    %d. %s  quantidade: %d preço: %.2lfx%d = %.2lf\n", i+1, p->produtos[i].nome, p->produtos[i].qtd, p->produtos[i].preco, p->produtos[i].qtd, (p->produtos[i].preco*p->produtos[i].qtd));
    }
    printf("Preço total: %.2lf\n", p->preco_t);
    printf("Nome do cliente: %s\n", p->cliente->nome);

}

void pedidos_andamento() {
    int i = 1;
    Pedido * p = NULL;

    if(h->ini == NULL) printf("Não há nenhum pedido em andamento\n");
    else {
        p = h->ini;
        while(1) {
            if(p == NULL) break;
            printf("%d. ", i);
            print_pedido(p);
            p = p->prox;
            i++;
        }
    }
}

void concluir_pedido() {
    int num = -1;
    int id;
    Pedido * aux = NULL;

    if(h->ini == NULL) {
        printf("Não há pedidos na fila para serem concluídos\n");
        return;
    }

    while(1) {    
        num = -1;   
        print_pedido(h->ini);
        printf("[1] - Sim\n");
        printf("[0] - Não\n");
        printf("Deseja concluir o pedido a seguir?\n");
        scanf("%d%*c", &num);

        if(num == 1) {
            id = busca_cliente(h->ini->cliente->nome);
            printf("id: %d\n", id);
            if(id != 0) {
                h->ini->cliente->qnt_compras++;
                (cli->clis[id-1].qnt_compras)++; // Atualizando a quantidade de compras do cliente no vetor de clientes global.
                fseek(clientes, sizeof(int)+(sizeof(Cliente)*(id-1)), SEEK_SET);
                fwrite(&(cli->clis[id-1]), 1, sizeof(Cliente), clientes);
            }
            
            aux = h->ini->prox;
            free(h->ini->cliente);
            free(h->ini->produtos);
            free(h->ini);
            h->ini = aux;

            return;            

        }
        else if(num == 0) return;
        else printf("\33[31mOpção Inválida\033[0m\n");
    }
}

void cancelar_pedido() {
    int num = -1;
    int num2 = -1;
    int i = 0;
    Pedido * p = NULL;
    Pedido * q = NULL;

    while(1) {
        num = -1;
        if(h->ini == NULL) {
            printf("Não há pedidos para serem cancelados\n");
            return;
        }
        pedidos_andamento();
        printf("[0] Cancelar cancelamento\n");
        printf("Digite o id do pedido que deseja cancelar: ");
        scanf("%d%*c", &num);

        if(num == 0) return;
        else if(num > 0) {
            p = h->ini;
            if(num == 1) {
                h->ini = p->prox;
                free(p->cliente);
                free(p->produtos);
                free(p);
                return;

            }
            while(1) {
                i++;
                if(p == NULL) {
                    printf("Opção inválida\n");
                    return;
                }

                if(num == i) { // Caso tenha chegado no pedido escolhido
                    while(1) {
                        num2 = -1;
                        print_pedido(p);
                        printf("[1] Sim\n");
                        printf("[0] Não\n");
                        printf("Deseja cancelar o pedido acima?\n");
                        scanf("%d%*c", &num2);

                        if(num2 == 0) return;
                        else if(num2 == 1) {
                            q->prox = p->prox;
                            free(p->cliente);
                            free(p->produtos);
                            free(p);
                            return;
                        }
                        else printf("Opção inválida\n");
                    }

                }

                q = p;
                p = p->prox;
            }

        }
        else printf("Opção inválida\n");
    }
}