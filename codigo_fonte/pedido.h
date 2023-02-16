#ifndef PEDIDO
#define PEDIDO

#include "produto.h"
#include "cliente.h"
#include <stdio.h>

typedef struct pedido Pedido;
typedef struct head Head;

struct pedido {
    int qtd_p;
    Produto_ped * produtos;
    double preco_t;
    Cliente * cliente;
    Pedido * prox;
};

struct head {
    Pedido * ini;
};

extern Head * h;

int pick_name(char * s);
void inserir_pedido();
void concluir_pedido();
void excluir_pedido();
int escolher_cliente(Cliente * c);
int escolher_produtos(Pedido * p);
void print_pedido(Pedido * p);
void pedidos_andamento();
void cancelar_pedido();

#endif
