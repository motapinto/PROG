Pontos assumidos:
  -quando um clientes não tem nenhum travel pacote comprado, não é posto nada no ficheiro de texto a indicar, apenas passa para o próximo clientes ou termina o ficheiro;
  -o id que aparece no inicio de um ficheiro de travel pacotes é sempre positivo de acordo com a disponibilidade do pacote;
  -a disponibilidade de um pacote é um atributo que é possivel ser alterado e não é posto automaticamente a não disponível se não poderem ser comprados mais pacotes.

Todos os pontos referidos no trabalho foram implementados(1 a 8).

Funcionalidades não pedidas:
  -Pesquisas por nome e por id de clientes;
  -Ver agencia e alterá-la.

Ficheiros são alterados e guardados de forma relativamente segura:
  -é criado um ficheiro temporário com o nome de temp.txt;
  -são guardados os dados neste ficheiro;
  -de seguida é eliminado o ficheiro original;
  -logo após é feita a mudança de nome do ficheiro temporário para o ficheiro original.

Nos ficheiros de texto é necessário deixar uma linha vazia no final destes.
O ficheiro da agência tem que ter todos os valores da agencia, os ficheiros dos pacotes e dos clientes podem estar vazios quando se inicia o programa, mas os nomes para onde os dados destes serão guardados tem que ser indicados no ficheiro da agência

Este trabalho foi feito usando classes porque quando foi entregue o inunciado do trabalho, comecei a fazer o trabalho com um colega sendo que pensavamos que seria um trabalho de grupo.
  Quando o Professor Jorge Silva disse que não seria a pares, fomos perguntar-lhe e este disse que poderiamos manter o código feito em conjunto, tendo começado a implementar com classes o Professor também nos disse que poderiamos continuar a usar estas mesmas.


NOTA: é incluído um makefile para este projeto que compila os ficheiros e chama ao programa: main.


A FAZER:---------------------------------------------------------------------------------------------------------------------------------- - Usar as funcoes de StringFunctions de read_uint, read_int, read_string em alternativa aos cin e getline
- Utilizar apenas uma funcao decompose

