#include "pedido.h"
#include <stdio.h>
#include <unistd.h>

Head * h = NULL;

void inserir_pedido() {
    int num;

    while(1) {
        printf("///////////////////////////////////////////");
        printf("O cliente possui cadastro?\n");
        printf("[1] Sim\n");
        printf("[2] Não ou não sabe\n");
        printf("[0] Cancelar registro de pedido\n");
        scanf("%d%*c", &num);
        sleep(0.1);

        if(num == 1 || num == 2 || num == 3 || num == 0) break;
        else printf("Opção inválida\n");
        sleep(0.3);
    }

    if(num == 0) return;
    if(num == 2) {
        printf("O cliente deseja fazer cadastro?\n");
        printf("[1] Sim\n");
        printf("[2] Não\n");
        scanf("%d%*c", &num);

        if (num == 1) cadastrar_cliente();
    }

    if (h->ini == NULL) {

    }



}