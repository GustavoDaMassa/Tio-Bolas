#include "produto.h"
#include "cliente.h"
#include "pedido.h"
#include "arquivos.h"
#include <stdlib.h>
#include <stdio.h>  
extern FILE * cardapio;
extern FILE * clientes;
extern FILE * estoque;

void end_program() {
    Pedido * p = NULL;
    Pedido * q = NULL;

    if(h != NULL) { // Caso h esteja alocado
        if(!(h->ini)) free(h); // Caso h não tenha o pedido inicial
        else { // Caso tenha, desalocar todos os pedidos.
            p = h->ini;
            q = p->prox;
            while(1) {
                free(p);
                if(!q) break; // if q == NULL
                p = q;
                q = p->prox;
            }
        }

    }
    if(car != NULL) { // Caso car esteja alocado
        if(car->prods != NULL) free(car->prods); // Caso c->prods esteja alocado
        free(car);
    }
    if(cli != NULL) { // Caso cli esteja alocado
        if(cli->clis != NULL) free(cli->clis); // Caso c->prods esteja alocado
        free(cli);
    }

    fechar_arquivos();

}
