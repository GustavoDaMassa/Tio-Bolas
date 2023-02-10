#include "produto.h"
#include "arquivos.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Card * c = NULL;

void load_cardapio() {
    int i;

    fseek(cardapio, 0, SEEK_SET); // Garantindo que o ponteiro que aponta para o arquivo cardápio está no início do arquivo.

    c = (Card *) malloc(sizeof(Card)); // Alocando espaço para o ponteiro para o cardápio.
    if (!c) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    c->prods = NULL; // Garantindo que não tem "lixo" no ponteiro para os produtos (prods) que acaba de ser criado dentro do cardápio.

    fread(&(c->qtd), sizeof(int), 1, cardapio); // Lendo o número de produtos do cardápio que fica no inicio do arquivo

    c->prods = (Produto_card *) malloc(sizeof(Produto_card)*(c->qtd)); // Alocando o espaço no ponteiro para produtos dentro do cardápio para a quantidade de produtos que o cardápio possui
    if (!(c->prods)) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    for(i = 0; i < c->qtd; i++) { // Lendo cada um dos produtos do cardápio e colocando no vetor de produtos.
        fread(&(c->prods[i]), sizeof(Produto_card), 1, cardapio);
    }

}

void save_cardapio() {
    int i;
    int fd; // File descriptor, ele é necessário para identificar o arquivo, já que a função truncate pede o inteiro file descriptor do arquivo e não o ponteiro.

    printf("aaaa\n");
    fseek(cardapio, 0, SEEK_SET); // Garante que o ponteiro pro arquivo está no começo.

    printf("aaaa\n");
    fwrite(&(c->qtd), 1, sizeof(int), cardapio); // Escrevendo o número de produtos no arquivo.

    for(i = 0; i < (c->qtd); i++) { // Escrevendo os produtos no arquivo
        fwrite(&(c->prods[i]), 1, sizeof(Produto_card), cardapio);
    }


    /* Função que trunca o arquivo de acordo com tamanho dado.
    *  Garante que os dados que sobram são descartados caso o cardápio tenha sido diminuído em relação ao anterior.
    */
    fd = fileno(cardapio); // Função que extrai o file descriptor do arquivo.
    ftruncate(fd, sizeof(int)+(sizeof(Produto_card)*c->qtd));

}

int check_price(char * s) {
    int dot_num = 0, num = 0, i = 0;

    num = strlen(s); // Variável que guarda o tamanho da string.

    for(i = 0; i < num; i++) { // for que irá verificar cada caractere.
        if(!(s[i] >= '0' && s[i] <= '9')) { // Se o caractere for diferente de número.
            if (s[i] == '.') { // Se o caractere for um ponto.
                dot_num++;
                if(!(s[i+1] >= '0' && s[i+1] <= '9')) return 1; // Caso o caractere depois do ponto não seja número ou o ponto está no final
            }
            else return 1; // Se não for um número nem um ponto a string já é inválida para ser um preço.
        }
    }

    if(dot_num > 1) return 1; //Caso mais tenha mais de um ponto no preço.
    else return 0; // Se tudo ocorrer bem e a string for válida para um preço.
}

void ver_cardapio() {
    int num = -1, num2 = -1;

    while(1) { 
        print_cardapio(); // Printa o cardápio
        printf("///////////////////////////////////////////\n");
        printf("[1] Adicionar produto\n");
        printf("[2] Remover produto\n");
        printf("[0] Voltar\n");
        scanf("%d%*c", &num);

        if (num == 0) {// Opção 0
            while(1) {
                printf("Deseja salvar as alterações do cardápio?\n");
                printf("[1] Sim\n");
                printf("[0] Não (As alterações feitas valerão apenas para essa sessão)\n");       
                scanf("%d%*c", num2);

                if(num2 == 1) {
                    save_cardapio();
                    return;
                }
                if(num2 == 0) return;
                printf("Opção inválida\n");
            }
        }
        if(num == 1) { // Opção 1
            add_produto();
            while(1) { 
                printf("Deseja continuar adicionando produtos?\n");
                printf("[1] Sim\n");
                printf("[0] Não\n");
                scanf("%d%*c", &num2);

                if(num2 == 1) {
                    add_produto();
                    continue;
                }
                if(num2 == 0) break;
                printf("Opção inválida\n"); // Se não entrar no 1º nem no 2º if, então num2 é uma opção inválida.
            }
        }

        if(num == 2) { // Opção 2
            if(!(c->qtd)) printf("Não há produtos no cardápio para remover\n");
            else {
                rem_produto();
                while(1) {
                    printf("Deseja continuar removendo produtos?\n");
                    printf("[1] Sim\n");
                    printf("[0] Não\n");
                    scanf("%d%*c", &num2);

                    if(num2 == 1) {
                        rem_produto();
                        continue;
                    }
                    if(num2 == 0) break;
                    printf("Opção inválida\n");
                }
            }
        }
        printf("Opção inválida\n");// Se não entrar no 1º nem no 2º if, então num é uma opção inválida.
    }

}

void print_cardapio() {
    int i;

    if(!(c->qtd)) printf("Não há nenhum produto no cardápio.\n"); // Caso a variável que guarda o número de produtos do cardápio seja 0
    else {
        for(i = 1; i <= c->qtd; i++) { // Printando cada produto
            printf("%d. %s R$%lf\n", c->prods[i-1].id, c->prods[i-1].nome, c->prods[i-1].preco);
        }
    }
}

void add_produto() {
    Produto_card * p = NULL;
    int carac = 0;
    char buffer[1000];
    char * endptr;

    

    p = (Produto_card *) malloc(sizeof(Produto_card)); // Alocando espaço de um elemento para um ponteiro para Produto_card, será usado para guardar as informações do novo produto.
    if(!p) {
        perror("Erro de alocação.");
        exit(1);
    }
    
    // Lendo o nome
    while(1) {
        memset(buffer, 0, sizeof(char)); 
        /* Testamos e vimos que caso o usuário apenas aperte enter o nome será o que já estava na buffer, 
        que poderia ser um "lixo" qualquer, para garantir que esse lixo não seja considerado como nome ou
        que o nome inválido digitado anteriormente apresente o erro errado, então limpamos o primeiro char
        para \0, indicando o final da string, fazendo com que o texto de buffer sempre será inicialmente vazio.
        */

        printf("[0] Cancelar\n");
        printf("Escolha o nome do produto(Até 100 caracteres): ");
        scanf("%[^\n]%*c", buffer);
        
        carac = strlen(buffer);
        if(!carac) {
            printf("Erro: você não digitou o nome.\n");
            continue;
        }
        if(carac > 100) { // Caso o nome tenha mais de 100 caracteres.
            printf("Nome inválido, o nome tem mais de 100 caracteres.\n");
            continue;
        }
        if (buffer[0] == '0') { // Caso tenha cancelado.
            free(p);
            return;
        }
        else break;
    
    }
    
    strcpy(p->nome, buffer);
    
    // Lendo o preço
    while(1) {
        memset(buffer, 0, sizeof(char));

        printf("[0] Cancelar\n");
        printf("[0.00] Produto de graça\n");
        printf("Escolha o preço do produto(Até 10 caracteres, dígitos e ponto): R$");
        scanf("%[^\n]%*c", buffer);

        carac = strlen(buffer);
        if(!carac) { // Caso o usuário apenas aperte enter
            printf("Erro: você não digitou o preço.\n");
            continue;
        }
        if(carac > 10) { // Caso o preço tenha mais de 10 caracteres.
            printf("Preço inválido, o preço tem mais de 10 caracteres.\n");
            continue;
        }
        if (carac = 1 && buffer[0] == '0') { // Caso tenha cancelado.
            free(p);
            return;
        }
        if(check_price(buffer) == 0) break;
        else printf("Preço inválido\n");
        
    }

    p->preco = strtod(buffer, &endptr); //string to double, endptr nesse contexto é inútil pois já lidamos com qualquer problema de formato.
    
    (c->qtd)++; // Atualizando a variável do número de produtos no cardápio

    c->prods = realloc(c->prods, (c->qtd)*sizeof(Produto_card)); // Alocando espaço para mais um produto no cardápio.
    if (!(c->prods)) {
        perror("Erro de alocação de memória");
        free(p);
        exit(1);
    }

    p->id = c->qtd; // Mudando o id de acordo com o número de produtos.
    c->prods[(c->qtd)-1] = *(p); // Colocando o produto novo no cardápio.

    free(p);

}

void rem_produto() {
    int i = 0;
    int num = -1;
  
    while(1) {
        print_cardapio(); // Printa o cardápio.
        printf("//////////////////////////\n");
        printf("[0] Cancelar a remoção de produto\n");
        printf("Digite o id do produto que deseja remover: ");
        scanf("%d%*c", &num);

        if(num == 0) return;
        
        if(num >= 1 && num <= (c->qtd)) break; // Caso tenha digitado um id válido, sai do loop.
        printf("Não há um produto com esse id\n");
    }

    for(i = (num-1); i < c->qtd; i++) { // Reorganiza todos os elementos do cardápio sobrescrevendo a partir do elemento que será excluído.
        c->prods[i] = c->prods[i+1];
        c->prods[i].id = i+1;
    }

    (c->qtd)--; // Atualizando a variável que guarda quantidade de produtos do cardápio.
    c->prods = realloc(c->prods, (c->qtd)*sizeof(Produto_card)); // Realocando o espaço para o tamanho novo, que um 1 a menos que o anterior. O último termo que já foi salvo no penúltimo é descartado.
    if (!(c->prods)) {
        perror("Erro de alocação de memória");
        exit(1);
    }

}