#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEINT ( sizeof ( int ) )
#define SIZE2 ( SIZEINT + SIZEINT )
#define SIZE3 ( SIZEINT + SIZEINT + SIZEINT )
#define FIXO ( SIZEINT + SIZEINT + SIZEINT + NOME )
#define FAKE_I ( * ( int * )  ( *pBuffer + SIZE2 ) )


#define NOME 20
#define EMAIL 40
#define IDADE ( sizeof ( int ) )
#define PESSOA ( NOME  + IDADE + EMAIL )

#define PESSOA_ANT ( * ( int * ) ( *pBuffer ) - 1 )


//Funções
void AdicionarPessoa ( void **pBuffer );
void RemoverPessoa ( void **pBuffer );
void BuscarPessoa ( void **pBuffer );
void ListarTodos ( void **pBuffer );

int main () 
{
void *pBuffer = malloc  ( FIXO ) ; // Um espaço pra número de pessoas, outro para menu e outro para agir como i.
    if ( !pBuffer ) {
        printf ( "Erro de alocação.\n" );
        return 1;
    }

    * ( int * ) pBuffer = 1; //o numero de pessoas

    while ( 1 )  {
        printf ( "\n-------------------------\n" );
        printf ( "Menu:\n" ) ;
        printf ( "1- Adicionar Pessoa  ( Nome, Idade, email ) \n" );
        printf ( "2- Remover Pessoa\n" ) ;
        printf ( "3- Buscar Pessoa\n" ) ;
        printf ( "4- Listar todos\n" ) ;
        printf ( "5- Sair\n" ) ;
        printf ( "\n-------------------------\n" ) ;

        scanf ( "%d", ( int * ) ( pBuffer + SIZEINT ) ); //le e guarda no 2 inteiro
        getchar (  ) ;

        switch  ( * ( int * )  ( pBuffer + SIZEINT )  ) 
        {
        case 1:
            AdicionarPessoa ( &pBuffer );
            break;
        case 2:
            RemoverPessoa ( &pBuffer );
            break;
        case 3:
            BuscarPessoa ( &pBuffer );
            break;
        case 4:
            ListarTodos ( &pBuffer );
            break;
        case 5:
            printf ( "\nSaindo da agenda!\n" );
            free ( pBuffer );
            return 0;
            break;
        
        default:
            printf ( "Opção inválida. Tente novamente.\n" );
            break;
        }
    }
    return 0;
}

/*
=================================================================
AdicionarPessoa
 aumenta o tamanho alocado para caber todos os dados de uma pessoa nova adicionada; 
 lê o nome da pessoa e armazena logo apos a ultima pessoa;
 lê a idade da pessoa e armazena apos o nome;
 lê o email da pessoa e armazena apos a idade;
 e por fim aumenta o número de pessoas;
=================================================================
*/

void AdicionarPessoa ( void **pBuffer ) {
    
    *pBuffer = realloc ( *pBuffer, FIXO + ( * ( int * ) *pBuffer )  * PESSOA ); //n de pessoa, menu, dados das pessoas
    if ( !*pBuffer ) {
        printf ( "Erro de alocação de memória.\n" );
        exit ( 1 );
    }

    printf ( "\nDigite o nome da pessoa: " ) ;
    scanf ( "%19[^\n]", ( char * ) ( *pBuffer ) + FIXO + PESSOA_ANT * PESSOA ); //o pessoa ant é pra ter 1 pessoa a menos e escrever no fim
	getchar ();

    printf ( "Digite a idade da pessoa: " ) ;
    scanf ( "%d", ( int * ) ( ( char * ) ( *pBuffer ) + FIXO + PESSOA_ANT * PESSOA + NOME ) );
    getchar ();

    printf ( "Digite o email da pessoa: " ) ;
    scanf ( "%39[^\n]", ( char * ) ( *pBuffer ) + FIXO + PESSOA_ANT * PESSOA + NOME + IDADE );
    getchar ();


    ( * ( int * ) *pBuffer ) ++; //mais uma pessoa
    printf ( "Pessoa adicionada com sucesso!\n" );
}

/*
=============================================================================
RemoverPessoa
 verifica se já existe alguma pessoa para remover;
 lê o nome da pessoa a ser removida e armazena no espaço reservado para nome no começo;
 utiliza o 3 inteiro do pBuffer como uma variavel I no for;
 realiza o for de 0 até < o numero de pessoas -1 devido a iniciar o FAKE_I em 1;
 compara o nome a ser buscado com todos os nomes da agenda;
 se encontrada a pessoa que tem que ser removida utiliza a função
 memmove para pegar todos dados das proximas pessoas caso existam e mover para onde
 foi encontrado a pessoa a ser removida.
============================================================================
*/

void RemoverPessoa ( void **pBuffer ) {
    if ( * ( int * ) *pBuffer == 1 ) {
        printf ( "Nenhuma pessoa para remover.\n" );
        return;
    } else {
        printf ( "Digite o nome da pessoa a ser removida: " );
        scanf ( "%19[^\n]", ( char * ) ( *pBuffer ) + SIZE3 );
        getchar () ;
        
        for ( FAKE_I = 0 ; FAKE_I < * ( int * ) *pBuffer - 1 ; FAKE_I++ ) {
            if ( strcmp (( char * ) ( *pBuffer ) + FIXO + ( FAKE_I * PESSOA ) , ( char * ) ( *pBuffer ) + SIZE3 ) == 0 ) {
                //void *memmove ( void *dest, const void *src, size_t n );

                if ( FAKE_I < ( * ( int * ) *pBuffer ) - 2 )  { // pois caso seja a 1 pessoa não existe uma segunda para mover pra cima.
                    memmove (( char * ) ( *pBuffer ) + FIXO + ( FAKE_I * PESSOA ) ,
                            ( char * ) ( *pBuffer ) + FIXO + ( FAKE_I * PESSOA ) + PESSOA , 
                            ( * ( int * ) *pBuffer - FAKE_I - 2 ) * PESSOA );
                    //posição que encontrou a pessoa, até o tamanho de 1 pessoa, até o fim da ultima pessoa.
                }
                ( * ( int * ) *pBuffer ) --;

                *pBuffer = realloc ( *pBuffer, FIXO + ( * ( int * ) *pBuffer ) * PESSOA );
                if ( !*pBuffer ) {
                    printf ( "Erro ao realocar memória.\n" );
                    exit ( 1 );
                }
                printf ( "Pessoa removida com sucesso!\n" );
                return;
            }
        }
        printf ( "Pessoa não encontrada.\n" );
    }
}


/*
==========================================================================================
BuscarPessoa
 verifica se há alguma pessoa para ser buscada;
 lê o nome da pessoa que se deseja buscar e armazena no espaço reservado para nome no começo;
 utiliza o 3 inteiro do pBuffer como uma variavel I no for;
 realiza o for de 0 até < o numero de pessoas -1 devido a iniciar o FAKE_I em 1;
 compara o nome a ser buscado com todos os nomes da agenda;
 caso encontre o nome imprime os dados da pessoa; 
==========================================================================================
*/

void BuscarPessoa ( void **pBuffer )  {
    if ( * ( int * ) *pBuffer == 1 ) {
        printf ( "Nenhuma pessoa cadastrada.\n" );
        return;
    } else {
        printf ( "Digite o nome da pessoa a ser buscada: " );
        scanf ( "%19[^\n]", ( char * ) ( *pBuffer ) + SIZE3 );
        getchar ();

        for ( FAKE_I = 0; FAKE_I < * ( int * ) *pBuffer - 1; FAKE_I++ )  {
            if ( strcmp ( ( char * ) ( *pBuffer ) + FIXO + ( FAKE_I * PESSOA ) , ( char * ) ( *pBuffer ) + SIZE3 ) == 0 ) {
                printf ( "Pessoa encontrada:\n" ) ;
                printf ( "Nome: %s\n", ( char * ) ( *pBuffer ) + FIXO + ( FAKE_I * PESSOA ) );
                printf ( "Idade: %d\n", * ( int * ) ( ( char * ) ( *pBuffer ) + FIXO + ( FAKE_I * PESSOA ) + NOME ) );
                printf ( "Email: %s\n", ( char * ) ( *pBuffer ) + FIXO + ( FAKE_I * PESSOA ) + NOME + IDADE );
                return;
            }    
        }
        printf ( "Pessoa nao encontrada" );
    }
}


/*
=========================================================
ListarTodos
 verifica se já existe alguma pessoa cadastrada;
 utiliza o 3 inteiro do pBuffer como uma variavel I no for;
 realiza o for de 0 até < o numero de pessoas -1 devido a iniciar o FAKE_I em 1;
 imprime todas os dados das pessoas que estão na agenda.
==========================================================
*/

void ListarTodos ( void **pBuffer ) {
    if ( * ( int * ) *pBuffer == 1 ) {
        printf ( "Nenhuma pessoa cadastrada.\n" );
        return;
    } else {
         for ( FAKE_I = 0; FAKE_I < ( ( * ( int * ) *pBuffer ) -1 ) ; FAKE_I++ ) {
            printf ( "\nPessoa %d:\n", FAKE_I + 1 );
            printf ( "Nome: %s\n", ( char * ) ( *pBuffer ) + FIXO + FAKE_I * PESSOA );
            printf ( "Idade: %d\n", * ( int * ) ( ( char * ) ( *pBuffer ) + FIXO + FAKE_I * PESSOA + NOME ) );
            printf ( "Email: %s\n", ( char * ) ( *pBuffer ) + FIXO + FAKE_I * PESSOA + NOME + IDADE );
        }
    }
}