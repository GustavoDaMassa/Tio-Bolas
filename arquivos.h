#ifndef ARQUIVOS
#define ARQUIVOS
#include <stdio.h>

/*
O arquivo cardapio.bin guarda informações em binário do número de produtos e os produtos.
Ou seja, o início do arquivo é a informação do número e a partir disso são as informações dos produtos.

Já o arquivo clientes.bin guarda informações em binário do número de clientes cadastrados e os clientes.
Ou seja, o início do arquivo é a informação do número e a partir disso são as informações dos clientes.
*/

extern FILE * cardapio;
extern FILE * clientes;

/**
 * @brief Função que verifica se os arquivos necessários existem e abre esses arquivos, caso algum dos arquivos não exista ele cria.
 * 
 */
void abrir_arquivos();

/**
 * @brief Fecha os arquivos que foram abertos, caso não tenham sido fechados ainda.
 * 
 */
void fechar_arquivos();

#endif