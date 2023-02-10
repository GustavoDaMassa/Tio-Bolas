#include "produto.h"
#include "pedido.h"
#include "arquivos.h"
#include <stdlib.h>
#include <stdio.h>
extern FILE * cardapio;
extern FILE * clientes;

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
    if(c != NULL) { // Caso c esteja alocado
        if(c->prods != NULL) free(c->prods); // Caso c->prods esteja alocado
        free(c);
    }

    fechar_arquivos();

}