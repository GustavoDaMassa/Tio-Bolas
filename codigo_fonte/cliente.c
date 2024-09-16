#include "cliente.h"
#include "arquivos.h"
#include "pedido.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

Clients * cli = NULL;

// retorna 0 se for igual, retorna 1 se s1 está acima de s2, retorna 2 se s1 está abaixo de s2.
int compara_nome(char * s1, char * s2) {
    int tam1, tam2;
    int i=0;

    while (1){
        if(s1[i] == '\0' || s2[i] == '\0') break; // Se chegar no final de um dos nomes.
        
        if(s1[i] < s2[i])return 1; // Caso uma tenha sido achado uma letra diferente, verificamos se é lexicograficamente menor ou maior para retornar 1 ou 2.
        if(s1[i] > s2[i])return 2;
        
        i++;
    }

    tam1 = strlen(s1); 
    tam2 = strlen(s2);
    if(tam1 == tam2) return 0; // Caso tenha saído do loop sem encontrar uma letra diferente, se for de tamanho igual, os nomes são iguais
    if(tam1 < tam2) return 1; // Caso tenha saído do loop sem encontrar uma letra diferente, se tam1 for menor que tam2, então s1 é lexicograficamente menor que s2.
    if(tam1 > tam2) return 2; // Caso tenha saído do loop sem encontrar uma letra diferente, se tam1 for maior que tam2, então s2 é lexicograficamente maior que s2.
    
}   

// Retorna 0 se o nome não foi achado, retorna o id do nome se ele foi achado.
int busca_cliente(char * s1) {
    int mid;
    int num;
    int L = 0, R = (cli->qtd)-1;
    
    while (L <= R) { // Algoritmo de busca binária que funciona definindo os extremos L ou R do vetor, e eles mudam de acordo com a análise do termo do meio.
        mid = L+((R-L)/2);
        num = compara_nome(s1, cli->clis[mid].nome);
        if (num == 0) return (mid+1); // Caso o retorno da compara_nome seja 0, então quer dizer que achamos o nome no vetor, retorna mid+1 pois estamos retornando o id e não a posição.
        if (num == 1) R = mid - 1; // O extremo direito vai para o meio - 1, pois sabemos que se o nome estiver na lista ele está lexicograficamente a esquerda do meio atual.
        if (num == 2) L = mid + 1; // O extremo esquerdo vai para o meio + 1, pois sabemos que se o nome estiver na lista ele está lexicograficamente a direita do meio atual.            
    }     

    return 0;
    
}

// 0 se o cliente foi cadastrado, 1 se houve desistência no processo.
int cadastrar_cliente(Cliente * c) {
    int i;
    char nome[101];
    Data d;
    char email[101];
    Cliente aux1, aux2;

    while(1) {
        if(pick_name(nome) == 1) return 1;
        if(check_cli_name(nome) == 0) break; 
    }
    strupper(nome);
    strcpy(c->nome, nome);
    c->cadastro = 1;
    if(pick_date(&d) == 1) return 1; // caso tenha sido cancelado o processo 
    c->nasc = d;
    if(pick_email(email) == 1) return 1;
    strcpy(c->email, email);
    c->qnt_compras = 0;

    c->id = define_pos(nome)+1;
    (cli->qtd)++;

    cli->clis = (Cliente *) realloc(cli->clis, sizeof(Cliente)*cli->qtd);
    if(!(cli->clis)){
        perror("Erro de alocação");
        free(c);
        exit(1);
    }

    aux1 = cli->clis[(c->id)-1];
    cli->clis[(c->id)-1] = *(c);
    for(i = c->id; i < (cli->qtd); i++) {
        aux2 = cli->clis[i];
        aux1.id = i+1;
        cli->clis[i] = aux1;
        aux1 = aux2;
    }

    save_clientes();

    return 0;
}

// retorna 0 caso o nome esteja a correto e 1 caso há algum erro; 
int check_cli_name(char * s) {
    int i = 0;    

    strupper(s); //coloca todas as letras em maiusculo;

    while(1) {
        if(s[i] == '\0') break;

        if((!(s[i] >= 'A' && s[i] <= 'Z')) && s[i] != ' ') { // Se tem alguma letra diferente de A-Z e ' '
            printf("\033[31mNome de cliente inválido, apenas é permitidos letras de A-Z e espaços, sem acentos ou caracteres especiais\033[0m\n");
            return 1;
        }

        i++;
    }

    return 0;

}


// retorna 0 se a data foi salva com sucesso, 1 caso o processo seja cancelado;
int pick_date(Data * d) {
    
    time_t rawtime;
    struct tm * timeinfo;
    int num;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // DIA;
    while(1) {
        printf("[0] - Cancelar\n\n");
        printf("Digite o dia da data de nascimento do cliente: ");
        scanf("%d%*c", &num);
        
        if(num == 0) return 1; // cancelou o processo ;
        else if(!(num >= 1 && num <= 31)) { // verifica se o dia digitado existe;
            printf("\033[31mDia de data inválido, digite um dia válido.\033[0m\n");
        }
        else {
            d->dia = num; // salva o dia digitado;
            break;
        }
    }
    // MES;
    while(1) {
        printf("[0] - Cancelar\n");
        printf("Digite o mês de nascimento do cliente: ");
        scanf("%d%*c", &num);
        
        if(num == 0) return 1; // cancelou o processo ;
        else if(!(num >= 1 && num <= 12)) { // mês digitado nao existe;
            printf("Mês de nascimento inválido, digite um mês válido.\n");
        }
        // verifica se o mês é fevereiro e se existirá o dia digitado caso seja;
        else if (num == 2 && d->dia > 29)printf("\033[31mMês de nascimento inválido, não possui o dia digitado, digite um mês válido.\033[0m\n"); 
        else if (d->dia == 31 && (num == 4 || num == 6 || num == 9 || num == 11))printf("\033[31mMês de nascimento inválido, não possui o dia digitado, digite um mês válido.\033[0m\n"); 
        else {
            d->mes = num; // salva o mês digitado;
            break;
        }
   
    }
    //ANO;
    while(1) {
        printf("[0] - Cancelar\n");
        printf("Digite o ano de nascimento do cliente: ");
        scanf("%d%*c", &num);

        if(num == 0) return 1;
        else if(!(num >= 1900 && num <= (timeinfo->tm_year + 1900))) { //_____________________________________________
            printf("\033[31mAno de data inválido, digite um ano válido.\033[0m\n"); // ano inválido(não existe ainda ou a idade do cliente seria inválida)
        }
        else if ( d->mes == 2){ // verificação se o ano é bissexto;
            
            int bissexto=0; // 1 para ano bissexto , 0 para os que não são;
            if(num%4 == 0 && !(num%100 == 0)) bissexto = 1; // só é bissexto se for divisível por 4, porém os que são por 4 e por 100, não são bissextos
            else if((num%4 == 0 && (num%100 == 0)) && num%400 == 0) bissexto = 1; // excessão da excessão, os divisíveis por 4 e 100 é bissextos se também divisível por 400; 

            if(bissexto == 0 && d->dia == 29)printf("\033[31mAno de data inválido, pois o ano não é bissexto, digite um ano válido.\033[0m\n");
            else {
                d->ano = num; // salvar ano informado;
                return 0;
            }
        }
        else {
            d->ano = num; // salvar ano informado caso tenha skipado todos os if's
            break;
        }
    }

    return 0;
}

// retorna 0 caso o email informado seja válido, e retorna 1 caso seja cancelado;
int pick_email(char * s) {
    
    int arroba=0;
    int ponto=0;
    int i;
    int a; // posição arroba
    int p; // posição do ponto;
    int letras;
    int aux = 0;

    while(1) {
        arroba = 0;
        ponto = 0;
        aux = 0;
        
        printf("[0] - Cancelar\n");
        printf("Digite o email do cliente: ");
        
        scanf("%s", s);

        if(strlen(s) == 1 && s[0] == '0') return 1;
            
        // caso seja a primeira letra do email
        if(s[0] == '@') {
            printf("\033[31mEmail inválido, por favor digite novamente.\033[0m\n");
            continue;
        }

        for(i=0;s[i] != '\0';i++){ // percorre toda a string contabilizando os @'s, nescessário conter apenas um;
            if(s[i] == '@'){
                arroba++;
                a = i; // salva a posição do arroba, que delimita o começo do dominio do email;
            } 
        }

        // é nescessário ter apenas um arroba
        if(arroba != 1) {
            printf("\033[31mEmail inválido, por favor digite novamente.\033[0m\n");
            continue;
        }

        for(i=a+1; s[i] != '\0'; i++){ //começa da posição em que achamos o @ até o final procurando pelo final do domínio;
                
            if(s[i] == '.'){  // contabilizando os pontos;
                ponto++;
                p = i;
                    
                // caso tenha dois pontos seguidos será inválido e caso o ponto esteja na última posição, ou caso o ponto esteja após o @;
                if(s[i+1] == '.' || s[i+1] == '\0' || s[a+1] == '.'){
                    printf("\033[31mEmail inválido, por favor digite novamente\033[0m.\n");
                    aux++;
                    break;
                }
            }
        }

        // caso alguma irregularidade em relação ao ponto tenha sido encontrada
        if(aux > 0) {
            printf("\033[31mEmail inválido, por favor digite novamente.\033[0m\n");
            continue;
        }
        
        if(ponto < 1){ // se não houver pontos o email é inválido;
            printf("\033[31mEmail inválido, por favor digite novamente.\033[0m\n");
            continue;
        } 
        

        for (i=a+1; s[i] != '\0'; i++){  // percorre o dominio somando as letras;
            if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))letras++;
        }
        

        if(letras < 1){ // tem que haver ao menos uma letra no domínio do email;
            printf("\033[31mEmail inválido, por favor digite novamente.\033[0m\n");
            continue;
        } 
        

        else break;
    }

    return 0;
}

int define_pos(char * s1) {
    int mid;
    int num;
    int L = 0, R = (cli->qtd)-1;

    while (L <= R) { // Algoritmo de busca binária que funciona definindo os extremos L ou R do vetor, e eles mudam de acordo com a análise do termo do meio.
        mid = L+(R-L)/2;
        num = compara_nome(s1, cli->clis[mid].nome);
        if (num == 1) R = mid - 1; // O extremo direito vai para o meio - 1, pois sabemos que se o nome estiver na lista ele está lexicograficamente a esquerda do meio atual.
        if (num == 2) L = mid + 1; // O extremo esquerdo vai para o meio + 1, pois sabemos que se o nome estiver na lista ele está lexicograficamente a direita do meio atual.            
    }     

    /*
    Ao tirar a opção do return na busca binária quando é igual, deixamos o algoritmo rodar até sair do loop
    isso nos garante que o L é a posição em que o novo cliente deve estar para que seja adicionado em ordem
    alfabética.
    */
    return L;
}

void save_clientes() {
    int i;
    int fd; // File descriptor, ele é necessário para identificar o arquivo, já que a função truncate pede o inteiro file descriptor do arquivo e não o ponteiro.

    fseek(clientes, 0, SEEK_SET); // Garante que o ponteiro pro arquivo está no começo.

    fwrite(&(cli->qtd), 1, sizeof(int), clientes); // Escrevendo o número de clientes no arquivo.

    for(i = 0; i < (cli->qtd); i++) { // Escrevendo os clientes no arquivo
        fwrite(&(cli->clis[i]), 1, sizeof(Cliente), clientes);
    }


    /* Função que trunca o arquivo de acordo com tamanho dado.
    *  Garante que os dados que sobram são descartados caso o vetor de clientes tenha sido diminuído em relação ao anterior.
    */
    fd = fileno(clientes); // Função que extrai o file descriptor do arquivo.
    ftruncate(fd, sizeof(int)+(sizeof(Cliente)*cli->qtd));

}

void load_clientes() {
    int i;

    fseek(clientes, 0, SEEK_SET); // Garantindo que o ponteiro que aponta para o arquivo cardápio está no início do arquivo.

    cli = (Clients *) malloc(sizeof(Clients)); // Alocando espaço para o ponteiro para o cardápio.
    if (!cli) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    cli->clis = NULL; // Garantindo que não tem "lixo" no ponteiro para os produtos (prods) que acaba de ser criado dentro do cardápio.

    fread(&(cli->qtd), sizeof(int), 1, clientes); // Lendo o número de produtos do cardápio que fica no inicio do arquivo

    cli->clis = (Cliente *) malloc(sizeof(Cliente)*(cli->qtd)); // Alocando o espaço no ponteiro para produtos dentro do cardápio para a quantidade de produtos que o cardápio possui
    if (!(cli->clis)) {
        perror("Erro de alocação de memória");
        exit(1);
    }

    for(i = 0; i < cli->qtd; i++) { // Lendo cada um dos produtos do cardápio e colocando no vetor de produtos.
        fread(&(cli->clis[i]), sizeof(Cliente), 1, clientes);
    }

}

void print_clientes() {
    int i;

    if(!(cli->qtd)) printf("\033[31mNão há nenhum cliente cadastrado.\033[0m\n"); // Caso a variável que guarda o número de produtos do cardápio seja 0
    else {
        printf("\033[34m  -- Clientes cadastrados -- \033[0m\n\n");
        for(i = 1; i <= cli->qtd; i++) { // Printando cada cliente
            printf("%d. %s %s %d/%d/%d quantidade de compras:%d\n", cli->clis[i-1].id, cli->clis[i-1].nome, cli->clis[i-1].email, cli->clis[i-1].nasc.dia, cli->clis[i-1].nasc.mes, cli->clis[i-1].nasc.ano ,cli->clis[i-1].qnt_compras);
        }
    }
}

void strupper(char * s) {
    int i = 0;

    while(s[i] != '\0') {
        if(s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
        i++;
    }


}