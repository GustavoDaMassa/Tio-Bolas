#ifndef PEDIDO
#define PEDIDO

#include "produto.h"
#include "cliente.h"
#include <stdio.h>

typedef struct pedido Pedido;
typedef struct head Head;

struct pedido {
    int index;
    Produto_ped * produtos;
    double preco_t;
    Cliente * cliente;
    Pedido * prox;
};

struct head {
    Pedido * ini;
};

extern Head * h;

void inserir_pedido();
void concluir_pedido();
void excluir_pedido();

#endif
