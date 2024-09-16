# Sistema de Gerenciamento de pedidos, produtos e clientes usando Estrutura de Dados 

Neste projeto tínhamos o objetivo de fazer um sistema que auxilie no gerenciamento de uma sorveteria.
Para isso, simulamos toda a situação, desde a criação da sorveteria "Tio Bolas" e seu cardapio até a implementação do seu sistema.

Para o sistema, utilizamos as listas pensando na chegada e entrega dos pedidos, utilizamos também arquivos para guardar informações diversas das vendas, além dos algoritmos de busca que consequentemente utilizamos para a maior organização das informações.

Para o funcionamento de tudo em harmonia, pensamos na interface de 2 perfis: gerente e funcionário. Cada um destes apresenta diferentes funções de acordo com as necessidades do seu cargo.

## Funcionalidades:
Irei demostrar como o sistema funciona a seguir, caso deseje compilar e navegar por si só no sistema siga para [como executar](#como-executar)

![image](https://github.com/user-attachments/assets/5771841f-e89f-48a1-afc3-64530cadc93e)

AO executar o código é apresentado uma tela inicial onde pode-se fazer o cadastro como um atendente ou como um gerente. 

### Atendente

Ao escolher acessar como um atendente somos guiados à seguinte interface com as funcionalidades a seguir:
![image](https://github.com/user-attachments/assets/0d0736ad-f507-4395-bb46-7b4df89d13ce)

- #### Opção 1 - Iniciar um novo pedido

  Para iniciar um novo pedido verificamos se o cliente já é cadastrado no sistema, caso não seja, poderá ser feito o cadastro ou continuar sem ele

  ![image](https://github.com/user-attachments/assets/1c39b9f8-ad92-49e8-b0c2-b948eaa709f3)  ![image](https://github.com/user-attachments/assets/65da5d7c-fabd-4600-95cc-56d218fa20eb)

Durante o cadastro é pedido os dados do cliente, todos eles são validados:

![image](https://github.com/user-attachments/assets/b5c06199-9019-42e5-98cd-771b901d97ad)
![image](https://github.com/user-attachments/assets/0685b567-4d81-4c51-8eab-c69670d02196)

Após o cadastro finalizado, é exibido o cardápio para escolha dos itens e confirmação do pedido já com o calculo do valor total

![image](https://github.com/user-attachments/assets/e3f99c07-8300-4c2e-9461-2de87b45e00c)  ![image](https://github.com/user-attachments/assets/6886fff9-2029-4eb6-a084-a829872b7940)

- #### Opção 2 - Verificar pedidos em andamento

  Exibi a fila de pedidos, em ordem de preparo.
  ![image](https://github.com/user-attachments/assets/dc886127-1dd8-4313-b472-b576cb3f8f87)
- #### Opção 3 - Concluir pedidos

  Apenas o pedido que está na frente na fila é mostrado.
  
  ![image](https://github.com/user-attachments/assets/2c7d0e9c-6020-4196-97ec-265219b5e384)
- #### Opção 4 - Cancelar um pedido

  Todos os pedidos da lista poderão ser cancelados.

  ![image](https://github.com/user-attachments/assets/eb27928e-4286-4e96-a1a2-1613a2243e33)

### Gerente

Já para o gerente é nescessário uma senha (030201TioBolas?) para acessar a interface 
![image](https://github.com/user-attachments/assets/7de449df-08d7-4cd7-a556-43c3bf4ea867)

Senha correta! 

![image](https://github.com/user-attachments/assets/fa6ef3f8-efff-4002-904e-d3201bf14fed)

- #### Opção 1 - Ver cardápio
 Em nossa aplicação usamos arquivos para guardar as informações tanto do cardápio quanto dos clientes do estabelecimento. Apenas o gerente pode editar os produtos do cardápio.

 ![image](https://github.com/user-attachments/assets/086ec8de-fea3-4ae0-be69-11482675a185)

- #### Opção 2 - Ver clientes
  Para armazenar os clientes pensamos também em salvar dados como a data de nescimento e quantidade de compras para que promoções possam ser trabalhas encima dessas informações e atrair mais clientes
  
  ![image](https://github.com/user-attachments/assets/53c3cde2-749a-4faa-a326-c72a829baf0f)

## como executar
