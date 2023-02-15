#include "produto.h"
#include "arquivos.h"
#include "pedido.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Card * car = NULL;

void load_cardapio() {
    int i;

    fseek(cardapio, 0, SEEK_SET); // Garantindo que o ponteiro que aponta para o arquivo cardápio está no início do arquivo.

    car = (Card *) malloc(sizeof(Card)); // Alocando espaço para o ponteiro para o cardápio.
    if (!car) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    car->prods = NULL; // Garantindo que não tem "lixo" no ponteiro para os produtos (prods) que acaba de ser criado dentro do cardápio.

    fread(&(car->qtd), sizeof(int), 1, cardapio); // Lendo o número de produtos do cardápio que fica no inicio do arquivo

    car->prods = (Produto_card *) malloc(sizeof(Produto_card)*(car->qtd)); // Alocando o espaço no ponteiro para produtos dentro do cardápio para a quantidade de produtos que o cardápio possui
    if (!(car->prods)) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    for(i = 0; i < car->qtd; i++) { // Lendo cada um dos produtos do cardápio e colocando no vetor de produtos.
        fread(&(car->prods[i]), sizeof(Produto_card), 1, cardapio);
    }

}

void save_cardapio() {
    int i;
    int fd; // File descriptor, ele é necessário para identificar o arquivo, já que a função truncate pede o inteiro file descriptor do arquivo e não o ponteiro.

    fseek(cardapio, 0, SEEK_SET); // Garante que o ponteiro pro arquivo está no começo.

    fwrite(&(car->qtd), 1, sizeof(int), cardapio); // Escrevendo o número de produtos no arquivo.

    for(i = 0; i < (car->qtd); i++) { // Escrevendo os produtos no arquivo
        fwrite(&(car->prods[i]), 1, sizeof(Produto_card), cardapio);
    }


    /* Função que trunca o arquivo de acordo com tamanho dado.
    *  Garante que os dados que sobram são descartados caso o cardápio tenha sido diminuído em relação ao anterior.
    */
    fd = fileno(cardapio); // Função que extrai o file descriptor do arquivo.
    ftruncate(fd, sizeof(int)+(sizeof(Produto_card)*car->qtd));

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
    int verif = 0; // Variável que guarda a informação se alguma alteração foi feita.

    while(1) { 
        print_cardapio(); // Printa o cardápio
        printf("///////////////////////////////////////////\n");
        printf("[1] Adicionar produto\n");
        printf("[2] Remover produto\n");
        printf("[0] Voltar\n");
        scanf("%d%*c", &num);

        if (num == 0) {// Opção 0

            if (verif == 0) break; // Não perguntar se as alterações devem ser salvas caso nenhuma alteração tenha sido feita.
            while(1) {
                printf("Deseja salvar as alterações do cardápio?\n");
                printf("[1] Sim\n");
                printf("[0] Não (As alterações feitas valerão apenas para essa sessão)\n");       
                scanf("%d%*c", &num2);

                if(num2 == 1) {
                    teste_cardapio();
                    save_cardapio();
                    teste_cardapio();
                    return;
                }
                if(num2 == 0) return;
                printf("Opção inválida\n");
            }
        }
        else if(num == 1) { // Opção 1

            if(add_produto() == 0) verif = 1; // Se ocorreu a adição de um produto, mudar a variável verif que guarda se alguma mudança foi feita.
            else continue; // Não perguntar se deseja continuar adicionando caso nem tenha sido adicionado na primeira vez.
            
            while(1) { 
                printf("Deseja continuar adicionando produtos?\n");
                printf("[1] Sim\n");
                printf("[0] Não\n");
                scanf("%d%*c", &num2);

                if(num2 == 1) {
                    if(add_produto() == 0) continue; // Se a adição ocorreu, continue para perguntar se quer continuar adicionando.
                    else break; // Se a adição não ocorreu apenas voltar para o menu do cardápio.
                }
                if(num2 == 0) break; // Se o usuário escolheu não continar adicionando.
                printf("Opção inválida\n"); // Se não entrar no 1º nem no 2º if, então num2 é uma opção inválida.
            }
        }

        else if(num == 2) { // Opção 2
            if(!(car->qtd)) printf("Não há produtos no cardápio para remover\n"); // Caso a quantidade de produtos no cardápio seja 0.
            else {
                if(rem_produto() == 0) verif = 1; // Se ocorreu a remoção de um produto, mudar a variável verif que guarda se alguma mudança foi feita.
                else continue; // Não perguntar se deseja continuar removendo caso nem tenha sido removido nada na primeira vez.
                while(1) {
                    if(!(car->qtd)) {
                        printf("Não há mais produtos no cardápio para remover\n");
                        break;
                    }
                    printf("Deseja continuar removendo produtos?\n");
                    printf("[1] Sim\n");
                    printf("[0] Não\n");
                    scanf("%d%*c", &num2);

                    if(num2 == 1) {
                        if(rem_produto() == 0) continue; // Se a remoção ocorreu, continue para perguntar se quer continuar removendo.
                        else break; // Se a remoção não ocorreu apenas voltar para o menu do cardápio.
                    }
                    if(num2 == 0) break;
                    printf("Opção inválida\n");
                }
            }
        }
        else printf("Opção inválida\n");// Se não entrar no 1º nem no 2º if, então num é uma opção inválida.
    }

}

void print_cardapio() {
    int i;

    if(!(car->qtd)) printf("Não há nenhum produto no cardápio.\n"); // Caso a variável que guarda o número de produtos do cardápio seja 0
    else {
        for(i = 1; i <= car->qtd; i++) { // Printando cada produto
            printf("%d. %s R$%lf\n", car->prods[i-1].id, car->prods[i-1].nome, car->prods[i-1].preco);
        }
    }
}

int add_produto() {
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
    if(pick_name(p->nome) == 1) {
        free(p);
        return 1; 
    }

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
            return 1;
        }
        if(check_price(buffer) == 0) break;
        else printf("Preço inválido\n");
        
    }

    p->preco = strtod(buffer, &endptr); //string to double, endptr nesse contexto é inútil pois já lidamos com qualquer problema de formato.
    
    (car->qtd)++; // Atualizando a variável do número de produtos no cardápio

    car->prods = realloc(car->prods, (car->qtd)*sizeof(Produto_card)); // Alocando espaço para mais um produto no cardápio.
    if (!(car->prods)) {
        perror("Erro de alocação de memória");
        free(p);
        exit(1);
    }

    p->id = car->qtd; // Mudando o id de acordo com o número de produtos.
    car->prods[(car->qtd)-1] = *(p); // Colocando o produto novo no cardápio.

    free(p);

    return 0;

}

int rem_produto() {
    int i = 0;
    int num = -1;
  
    while(1) {
        print_cardapio(); // Printa o cardápio.
        printf("//////////////////////////\n");
        printf("[0] Cancelar a remoção de produto\n");
        printf("Digite o id do produto que deseja remover: ");
        scanf("%d%*c", &num);

        if(num == 0) return 1;
        
        if(num >= 1 && num <= (car->qtd)) break; // Caso tenha digitado um id válido, sai do loop.
        printf("Não há um produto com esse id\n");
    }

    for(i = (num-1); i < car->qtd; i++) { // Reorganiza todos os elementos do cardápio sobrescrevendo a partir do elemento que será excluído.
        car->prods[i] = car->prods[i+1];
        car->prods[i].id = i+1;
    }

    (car->qtd)--; // Atualizando a variável que guarda quantidade de produtos do cardápio.
    car->prods = realloc(car->prods, (car->qtd)*sizeof(Produto_card)); // Realocando o espaço para o tamanho novo, que um 1 a menos que o anterior. O último termo que já foi salvo no penúltimo é descartado.
    if (!(car->prods)) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    return 0;

}



void teste_cardapio() {
    int i;

    printf("Teste // quantidade de produtos: %d\n", car->qtd);

    for(i = 0; i < car->qtd; i++) {
        printf("Teste // produto %d: %s R$%lf\n", car->prods[i].id, car->prods[i].nome, car->prods[i].preco );
    }
}
