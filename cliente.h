#ifndef CLIENTE
#define CLIENTE

typedef struct cliente Cliente;
typedef struct data Data;

struct data{
    int dia;
    int mes;
    int ano;
};

struct cliente{
    int id;
    int cadastro; // 0 quando não tem cadastro, 1 quando tem cadastro.
    char nome[100];
    Data nasc;
    char email[100];
    int qnt_compras;
};

/* 
Quando o cliente não tem e não deseja realizar o cadastro, o tipo Cliente ainda será criado e a única 
identificação será o nome (poderá ser apenas o primeiro), mas ele não será salvo no arquivo clientes.bin
*/

void cadastrar_cliente();

#endif