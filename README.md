[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9844904&assignment_repo_type=AssignmentRepo)

# INF0286 - Algoritmos e Estruturas de Dados 1

# A03 - Seminário

Prof. Dr. Aldo André Díaz Salazar (aldo.diaz@ufg.br)

## Equipe {insert group name here}

Integrantes:

202200557 - Thiago de Souza Filgueiras (Líder)  
202204767 - Isabela Teixeira e Cerqueira  
202200492 - Anderson Barros Rigonatto  
202200517 - Gustavo Henrique Pereira da Silva  


## PROJETO: Sistema de gerenciamento de pedidos, estoque e clientes usando Estrutura de Dados  

Submissão W1 - Introdução, revisão bibliográfica e fundamentação teórica  
  
Descrição: Sistema de gerenciamento de pedidos, estoque e dados de clientes, para um estabelecimento comercial qualquer, no nosso caso, uma sorveteria.
	
<p>O gerenciamento de pedidos irá abordar o assunto de listas, pois os pedidos chegam e têm que ser produzidos e entregues em determinada ordem. Ao mesmo tempo, essas informações de venda são guardadas para que posteriormente possamos analisar e comparar informações de cada produto, como por exemplo, qual o produto com maior receita. Logo, estaremos usando também algoritmos de ordenação para mostrar informações organizadas pertinentes à gerência da empresa.</p>

<p>Planejamos fazer duas interfaces, uma para a administração do sistema de produtos e outra para o gerenciamento de pedidos. Temos em mente algumas funcionalidades do programa. Na interface do gerenciamento do sistema pensamos em fazer funções que computem, apresentem e permita ao administrador alterar informações sobre o produtos, como receitas e quantidades. Já na interface do funcionário queremos que ela permita ele registrar, atualizar, cancelar e concluir pedidos.</p>
   
Planejamos implementar uma fila (FIFO) para o gerenciamento de pedidos, e ao realizar as funções (registrar, atualizar, cancelar e concluir pedidos) automaticamente guardar em arquivos as informações dos produtos e clientes, para que essas informações sejam usadas em outras funções na interface do administrador.</p>
   


Submissão W2 - Modelagem e descrição metodológica.

<p>No projeto procuramos proporcionar para o usuário um sistema simples onde ele pode facilmente navegar de acordo com seu objetivo e de maneira gradativa.</p>

<p>É disponibilizado duas opções de perfis logo no início do programa, a interface do gerente e a interface do atendente:</p>

<p>-Onde a do gerente possui acesso administrativo as informações do estabelecimento:  O estoque , que penejamos atualizar de acordo com a venda e compra  dos produtos;  As finanças, que informará  o lucro que o estabelecimento teve em um certo dia ou mês, auxiliando na receita da empresa;  A lista de clientes que possuem cadastro, onde será registrado dados como a recorrência de tal pessoa na loja e até mesmo data de aniversario para possibilitar promoções e descontos; E o histórico de vendas, registrando as atividades da empresa, e que  assim como as demais funcionalidades utilizam como base os conceitos de listas para alocar e editar os dados e as armazenas em arquivos.</p>
<p>-A interface do atendente, será onde os pedidos serão realizados e o cardápio será apresentado com os respectivos preços, o gerente poderá remover e adicionar itens no cardápio de acordo com o estoque, ao finalizar o pedido o valor total da compra será a calculado e apresentado. O atendente pode acessar também os pedidos em andamento para ter um controle maior.</p> 
<p>o programa oferece a todo momento a opção de cancela-lo  e reinicia-lo .</p>

<p>Começamos a implementação fazendo um menu com opções e já encontramos dificuldades e dúvidas nas funções que fariam sentido serem apresentadas
para o usuário, após discussão com o grupo decidimos quais funções fazem sentido para o atendente e quais fazem sentido para o gerente e de que maneira se
apresentam. As interfaces são predominantemente implementada com loops while com quebras quando ocorre o cancelamento por parte do usuário.</p>

<p>Foi visto que algumas variáveis e arquivos eram essenciais e seriam usadas em todos os arquivos, portanto foi decidido que essas variáveis deveriam
ser globais pois facilitaria a implementação, essas variáveis são: os ponteiros para arquivos de cardapio e clientes, a fila de pedidos e o vetor do cardápio. Porém ao fazer isso obtivemos vários erros e dificuldades relacionados a dupla definição de variáveis e funções, mas foi resolvido depois de muito estudo e pesquisa ao usar as funcionalidades "extern", "#ifndef", "#define" e "#endif".</p>

<p>Foi preciso também estudo para relembrar o assunto de arquivos para saber como abrir no modo que precisávamos, como mudar o tamanho de um arquivo, como copiar informações, entre outros.</p>
