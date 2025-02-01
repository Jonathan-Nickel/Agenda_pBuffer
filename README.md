Agenda pBuffer        
Jonathan Goulart Nickel – 23200579

Problema: Agenda

Faça uma agenda com o seguinte menu:
1- Adicionar Pessoa (Nome, Idade, email)
2- Remover Pessoa
3- Buscar Pessoa
4- Listar todos
5- Sair

O desafio é não poder criar variáveis e sim um buffer de memória (void *pBuffer). Nisso vocês terão que fazer o trabalho que o Sistema Operacional faz para vocês ao organizar a memória.

Regras:
1.	Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
1.	Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
2.	Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
2.	Não pode usar struct em todo o programa.
Entregar link de um vídeo explicando o código e mostrando alguns testes e ao final o resultado do DrMemory ou Valgrind.
Vou perguntar no 1:1 sobre a sua implementação. Posso pedir para fazer alguma modificação no código na nossa conversa. O objetivo é saber se entenderam o que fizeram.

Testes: 
Realizei testes onde eu adicionei 1 pessoa, busquei por ela e depois a removi.
Realizei teste onde eu adicionei 2 pessoas, busquei por elas a 1 e depois a 2, e depois a 2 depois a 1. Removi a 1 e depois a segunda, adicionei novamente e removi a 2 e depois a 1.
Realize teste onde adicionei 3 pessoas, busquei elas por ordem que adicionei da 1 a última, depois da última para a primeira, e por fim a do meio depois a ultima e então a primeira. Removi elas em ordem que adicionei, adicionei de volta e remove da ultima para a primeira, adicionei de novo e removi de forma aleatória.
Todos os testes funcionaram sem apresentar erros nem de código nem de alocação.
