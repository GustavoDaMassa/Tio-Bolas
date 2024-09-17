# Sistema de Gerenciamento de pedidos, produtos e clientes usando Estrutura de Dados 

Neste projeto tínhamos o objetivo de fazer um sistema que auxilie no gerenciamento de uma sorveteria.
Para isso, simulamos toda a situação, desde a criação da sorveteria "Tio Bolas" e seu cardapio até a implementação do seu sistema.

Para o sistema, utilizamos as listas pensando na chegada e entrega dos pedidos, utilizamos também arquivos para guardar informações diversas das vendas, além dos algoritmos de busca que consequentemente utilizamos para a maior organização das informações.

Para o funcionamento de tudo em harmonia, pensamos na interface de 2 perfis: gerente e funcionário. Cada um destes apresenta diferentes funções de acordo com as necessidades do seu cargo.

## Funcionalidades:
Irei demostrar como o sistema funciona a seguir, caso deseje compilar e navegar por si só no sistema siga para [como executar](#como-executar)

![image](https://github.com/user-attachments/assets/e02427fe-1904-456f-92ab-690ae8c3cc84)


AO executar o código é apresentado uma tela inicial onde pode-se fazer o cadastro como um atendente ou como um gerente. 

### Atendente

Ao escolher acessar como um atendente somos guiados à seguinte interface com as funcionalidades a seguir:

![image](https://github.com/user-attachments/assets/0fef0b33-96f7-41e4-8330-a98742494244)



- #### Iniciar um novo pedido

  Para iniciar um novo pedido verificamos se o cliente já é cadastrado no sistema, caso não seja, poderá ser feito o cadastro ou continuar sem ele
  
![image](https://github.com/user-attachments/assets/5c1a11f4-cf86-4bd8-bf3a-6c068b6aa1fa) ![image](https://github.com/user-attachments/assets/c6dd233e-503f-4ce2-8e0d-05871e8db164)


Durante o cadastro é pedido os dados do cliente, todos eles são validados:
![image](https://github.com/user-attachments/assets/e10c176e-49b0-444f-95fd-1ce2a97522e1)
![image](https://github.com/user-attachments/assets/34e4a0c0-2f77-4c3c-8d99-aee970420b80)


Após o cadastro finalizado, é exibido o cardápio para escolha dos itens e confirmação do pedido já com o calculo do valor total
![image](https://github.com/user-attachments/assets/716024f7-a1b3-4c25-ab6b-7bc8f682cc08)



- #### Verificar pedidos em andamento

  Exibi a fila de pedidos, em ordem de preparo.
  
  ![image](https://github.com/user-attachments/assets/e4c3c195-f74b-4866-b4d1-c18d4d11e808)


- #### Concluir pedidos

  Apenas o pedido que está na frente na fila é mostrado.

  ![image](https://github.com/user-attachments/assets/ad45af2c-1dab-43a2-a4e1-53f7da58936c)

  
- #### Cancelar um pedido

  Todos os pedidos da lista poderão ser cancelados.

  ![image](https://github.com/user-attachments/assets/a2c0948c-d97d-41af-b668-9b056900b1cb)


### Gerente

Já para o gerente é nescessário uma senha (030201TioBolas?) para acessar a interface 

![image](https://github.com/user-attachments/assets/c626a3f3-ff98-4d97-adb9-681be9ea50d9)

Senha correta! 

![image](https://github.com/user-attachments/assets/e9131622-3311-4d96-ae02-e3e8de776a69)


- #### Ver cardápio
 Em nossa aplicação usamos arquivos para guardar as informações tanto do cardápio quanto dos clientes do estabelecimento. Apenas o gerente pode editar os produtos do cardápio.

![image](https://github.com/user-attachments/assets/0dbf0d48-a5ec-4844-ad26-b25ea42de3d0)


- #### Ver clientes
  Para armazenar os clientes pensamos também em salvar dados como a data de nescimento e quantidade de compras para que promoções possam ser trabalhas encima dessas informações e atrair mais clientes

![image](https://github.com/user-attachments/assets/e5e7d8fb-416a-48af-90aa-7e38bee192c1)



## como executar
   Para compilar e executar o programa certifique-se que o *GCC* está instalado.

  
  - Você pode clonar o repositório para a sua máquina local com o comando:
    
    ```
    git clone https://github.com/GustavoDaMassa/TioBolas.git
    ```
    
  - Compilando:
   
    ```
    gcc main.c arquivos.c cliente.c end.c menu.c pedido.c produto.c -o tiobolas
    ```
    
  - Executando:
    
    ```
    ./tiobolas
    ```




   
  

