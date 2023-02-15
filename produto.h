#ifndef PRODUTO
#define PRODUTO

#include <stdio.h>

typedef struct produto_ped Produto_ped;
typedef struct produto_card Produto_card;
typedef struct card Card;

struct produto_ped{ // O tipo que estará contido no pedido, contém a variável quantidade
    int id;
    char nome[101];
    double preco;
    int qtd;
};

struct produto_card{// O tipo que estará contido no cardápio, não contém a variável quantidade
    int id;
    char nome[101];
    double preco;
};

struct card{
    int qtd;
    Produto_card * prods;
};


extern Card * car;

/**
 * @brief Lê o arquivo cardapio.bin e coloca a variável de quantidade e todos os produtos dentro da variável global 'c' do tipo ponteiro pra Cardapio
 * 
 */
void load_cardapio();

/**
 * @brief Escreve no arquivo cardapio.bin a quantidade e todos os produtos da variável global 'c' do tipo ponteiro pra Cardapio.
 * 
 */
void save_cardapio();

/**
 * @brief Checa se um preço digitado é válido. (Checa se há espaços ou letras)
 * 
 * @return 0 se é válido, 1 se não é válido.
 */
int check_price(char * s);


void ver_cardapio();

/**
 * @brief Função que printa o cardápio
 * 
 */
void print_cardapio();

/**
 * @brief Função que adiciona um produto no ponteiro pra Cardapio 'c'
 * 
 * @return 0 Se algum produto foi adicionado, 1 se o usuário desistiu.
 */
int add_produto();

/**
 * @brief Função que remove um produto do ponteiro pra Cardapio 'c'
 * 
 * @return 0 Se algum produto foi removido, 1 se o usuário desistiu.
 */
int rem_produto();

void teste_cardapio();

#endif
