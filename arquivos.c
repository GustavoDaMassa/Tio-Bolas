#include "arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE * cardapio = NULL;
FILE * clientes = NULL;

void abrir_arquivos() {
    int x = 0;

    if(access("cardapio.bin", F_OK) == -1) { // Se o arquivo não existe

        cardapio = fopen("cardapio.bin", "wb"); // O modo wb cria o arquivo caso ele não exista.
        if(!cardapio) {
            perror("Erro ao abrir o arquivo cardápio.");
            exit(1);
        }

        fwrite(&x, 1, sizeof(int), cardapio); // Como o arquivo acabou de ser criado, então é necessário escrever no começo do arquivo que há 0 produtos.

        fclose(cardapio); // Fechar pois o programa já acessa ele futuramente no modo r+b.
        cardapio = NULL; // Evitar qualquer uso com o endereço antigo de ponteiro para arquivo, já que a função fclose não coloca o valor NULL para a variável.

    }

    if(access("clientes.bin", F_OK) == -1) { // Se o arquivo não existe

        clientes = fopen("clientes.bin", "wb"); // O modo wb cria o arquivo caso ele não exista.
        if(!cardapio) {
            perror("Erro ao abrir o arquivo clientes.");
            exit(1);
        }

        fwrite(&x, 1, sizeof(int), clientes); // Como o arquivo acabou de ser criado, então é necessário escrever no começo do arquivo que há 0 clientes.

        fclose(clientes); // Fechar pois o programa já acessa ele futuramente no modo r+b.
        clientes = NULL; // Evitar qualquer uso com o endereço antigo de ponteiro para arquivo, já que a função fclose não coloca o valor NULL para a variável.

    }

    cardapio = fopen("cardapio.bin", "r+b"); // Abrindo o cardáio no modo r+b
    if(!cardapio) {
        perror("Erro ao abrir o arquivo cardápio.");
        exit(1);
    }
    clientes = fopen("clientes.bin", "r+b"); // Abrindo os clientes no modo r+b
    if(!clientes) {
        perror("Erro ao abrir o arquivo clientes.");
        exit(1);
    }
    
    // O modo r+b nos permite ler e escrever em binário sem perder os dados que já estavam nos arquivos anteriormente.
    


}

void fechar_arquivos() {

    if(cardapio != NULL) fclose(cardapio); // Caso o arquivo cardapio esteja aberto
    if(clientes != NULL) fclose(clientes); // Caso o arquivo cliente esteja aberto
}