#ifndef CLIENTE
#define CLIENTE


typedef struct cliente Cliente;
typedef struct data Data;
typedef struct clients Clients;

struct data{
    int dia;
    int mes;
    int ano;
};

struct cliente{
    int id;
    int cadastro; // 0 quando não tem cadastro, 1 quando tem cadastro.
    char nome[101];
    Data nasc;
    char email[101];
    int qnt_compras;
};

struct clients{
    int qtd;
    Cliente * clis;
};

extern Clients * cli;

/* 
Quando o cliente não tem e não deseja realizar o cadastro, o tipo Cliente ainda será criado e a única 
identificação será o nome (poderá ser apenas o primeiro), mas ele não será salvo no arquivo clientes.bin
*/

int cadastrar_cliente();
int busca_cliente();
int pick_date(Data * d);
int pick_email(char * s);
int define_pos(char * s1);
int check_cli_name(char * s);
void save_clientes();
void load_clientes();
void print_clientes();

#endif
