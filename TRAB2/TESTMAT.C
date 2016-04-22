/***************************************************************************
*  $MCI Módulo de implementação: TPIL Teste matriz de pilhas
*
*  Arquivo gerado:              TestMAT.c
*  Letras identificadoras:      TMAT
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gdl - Guido Dowsley Leme
*           jpd - José Paulo Diniz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       jpd   20/abr/2016 início do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Matriz.h"
#include	"PILHA.H"


static const char CMD_CRIAR           [] = "=criar" ;
static const char CMD_DESTRUIR        [] = "=destruir" ;
static const char CMD_INSERIR_COLUNA  [] = "=inscol" ;
static const char CMD_INSERIR_LINHA   [] = "=inslin" ;
static const char CMD_LER_CELULA      [] = "=lercel" ;
static const char CMD_ESCREVER_CELULA [] = "=esccel" ;
static const char CMD_EXCLUIR_COLUNA  [] = "=exccol" ;
static const char CMD_EXCLUIR_LINHA   [] = "=exclin" ;
static const char CMD_CRIAR_PIL       [] = "=criarpil" ;
static const char CMD_DESTRUIR_PIL    [] = "=destruirpil" ;
static const char CMD_ESVAZIAR_PIL    [] = "=esvaziarpil" ;
static const char CMD_EMPILHAR_PIL    [] = "=empilharpil" ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_MATRIZ  11
#define DIM_VT_PILHA   10
#define DIM_VALOR     100

PIL_tppPilha   vtPilhas[ DIM_VT_PILHA ] ;
MAT_tppMatriz  vtMatrizes[ DIM_VT_MATRIZ + 1] ;

/***** Protótipos das funções encapsuladas no módulo *****/

   static int ValidarInxPilha  ( int inxPilha , int Modo ) ;

   static int ValidarInxMatriz ( int inxMatriz ) ;

   static int j=0;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPIL &Testar matriz
*
*  $ED Descrição da função
*     Podem ser criadas até 11 matrizes, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criar <int>  - chama a função MAT_CriarMatriz( mat )
*                     Obs. mat é a matriz identificada por <int>.
*                     <int> é o valor do parâmetro que se encontra
*                     no comando de teste.
*
*     =destruir <int>  - chama a função MAT_DestruirMatriz( mat )
*                        Obs. mat é a matriz identificada por <int>.
*                        <int> é o valor do parâmetro que se encontra
*                        no comando de teste.
*
*     =inscol <int>  - chama a função MAT_InserirColuna( mat )
*                    Obs. mat é a matriz identificada por <int>.
*                    <int> é o valor do parâmetro que se encontra
*                    no comando de teste.
*
*     =inslin <int>  - chama a função MAT_InserirLinha( mat )
*                    Obs. mat é a matriz identificada por <int>.
*                    <int> é o valor do parâmetro que se encontra
*                    no comando de teste.
*
*     =lercel <int, int, int, int>
*                    - chama a função MAT_LerCelula( mat, linha, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha e coluna são
*                    os dois parâmetros seguintes.
*                    O quarto parâmetro indica com qual pilha devemos
*                    comparar o ponteiro lido.
*                    Caso especial: Se linha ou coluna < 0, é passado
*                    NULL no ponteiro de retorno da pilha.
*
*     =esccel <int, int, int, int>
*                    - chama a função MAT_EscreverCelula( mat, linha, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha e coluna são
*                    os dois parâmetros seguintes. O quarto parâmetro
*                    indica qual pilha devemos colocar na célula.
*
*     =exccol <int, int>
*                    - chama a função MAT_ExcluirColuna( mat, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. coluna é o segundo
*                    parâmetro.
*
*     =exclin <int, int>
*                    - chama a função MAT_ExcluirLinha( mat, linha )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha é o segundo
*                    parâmetro.
*
*     ------------------ Funções de manipulação de pilhas ----------------
*
*     =criarpil <int>
*                    - cria uma pilha com <int> como identificador.
*
*     =destruirpil <int>
*                    - destroi a pilha identificada por <int>
*
*     =esvaziarpil <int>
*                    - remove todos os elementos da pilha identificada
*                    por <int>.
*
*     =empilharpil <int, char>
*                    - empilha um elemento contendo <char> na pilha
*                    identificada por <int>.
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxPilha   = -1 ,
		  inxMatriz  = -1 ,
		  inxDado	 = -1 ,
          numLidos   = -1 ,
		  linha		 = -1 ,
		  coluna	 = -1 ,
          CondRetEsp = -1 ;

	  PIL_tpCondRet PIL_CondRet ;
      MAT_tpCondRet MAT_CondRet ;

	  PIL_tppPilha Pilha ;

      char   StringDado [ DIM_VALOR ] ;
	  char   vetDado[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'} ;
	  char   teste = '\0' ;

      int ValEsp = -1 ;

      int numElem = -1 ;

	  void *EndObtido = NULL;
	  void *EndEsperado = NULL;

      StringDado[ 0 ] = 0 ;


      /* Testar CriarPilha */

         if ( strcmp( ComandoTeste , CMD_CRIAR_PIL ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
				&inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxPilha( inxPilha , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			PIL_CondRet = PIL_CriarPilha( &vtPilhas[ inxPilha ] ) ;

            return TST_CompararInt( CondRetEsp , PIL_CondRet ,
               "Erro ao criar lista."  ) ;

         } /* fim ativa: Testar CriarPilha */

      /* Testar Esvaziar pilha */

		 else if ( strcmp( ComandoTeste , CMD_ESVAZIAR_PIL ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp, PIL_EsvaziarPilha( vtPilhas[ inxPilha ] ),
					"Retorno inesperado." );

         } /* fim ativa: Testar Esvaziar pilha */

      /* Testar Destruir pilha */

		 else if ( strcmp( ComandoTeste , CMD_DESTRUIR ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			PIL_CondRet = PIL_DestruirPilha( vtPilhas[ inxPilha ] ) ;
            vtPilhas[ inxPilha ] = NULL ;

            return TST_CompararInt( CondRetEsp , PIL_CondRet , "Retorno inesperado." ) ;

         } /* fim ativa: Testar Destruir pilha */

      /* Testar inserir elemento */

         else if ( strcmp( ComandoTeste , CMD_EMPILHAR_PIL ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxPilha , &inxDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			PIL_CondRet = PIL_Empilha( vtPilhas[ inxPilha ], &vetDado[inxDado]);

            return TST_CompararInt( CondRetEsp , PIL_CondRet ,
                     "Condicao de retorno errada ao inserir antes." ) ;

         } /* fim ativa: Testar inserir elemento */

		 /* Testar criar matriz */
		 else if ( strcmp( ComandoTeste , CMD_CRIAR ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "ii" ,
						&inxMatriz , &CondRetEsp ) ;

			 if ( ( numLidos != 2 )
				 || (! ValidarInxMatriz( inxMatriz )) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 if (inxMatriz == DIM_VT_MATRIZ)
			 {
				 MAT_CondRet = MAT_CriarMatriz( NULL );
			 } else
			 {
				 MAT_CondRet = MAT_CriarMatriz( &vtMatrizes[inxMatriz] );
			 }
			 return TST_CompararInt( CondRetEsp, MAT_CondRet ,
					"Condicao de retorno errada ao criar matriz." ) ;

		 } /* fim ativa: Testar criar matriz */

		 /* Testar destruir matriz */
		 else if ( strcmp( ComandoTeste , CMD_DESTRUIR ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "ii" ,
						&inxMatriz , &CondRetEsp ) ;

			 if ( ( numLidos != 2 )
				 || ( ! ValidarInxMatriz( inxMatriz )) )
			 {
				 return TST_CondRetParm ;
			 } /* if */
			 
			 MAT_CondRet = MAT_DestruirMatriz( vtMatrizes[inxMatriz] );
			 
			 return TST_CompararInt( CondRetEsp, MAT_CondRet ,
					"Retorno inesperado." ) ;

		 } /* fim ativa: Testar destruir matriz */

		 /* Testar inserir coluna */
		 else if ( strcmp( ComandoTeste , CMD_INSERIR_COLUNA ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "ii" ,
						&inxMatriz , &CondRetEsp ) ;

			 if ( ( numLidos != 2 )
				 || !( ValidarInxMatriz( inxMatriz )) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 MAT_CondRet = MAT_InserirColuna (vtMatrizes[inxMatriz]) ;
			 
			 return TST_CompararInt( CondRetEsp, MAT_CondRet,
					"Erro ao inserir coluna.") ;

		 } /* fim ativa: Testar inserir coluna */

		 /* Testar inserir linha */
		 else if ( strcmp( ComandoTeste , CMD_INSERIR_LINHA ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "ii" ,
						&inxMatriz , &CondRetEsp ) ;

			 if ( ( numLidos != 2 )
				 || ( !ValidarInxMatriz( inxMatriz)) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 MAT_CondRet = MAT_InserirLinha (vtMatrizes[inxMatriz]) ;
			 
			 return TST_CompararInt( CondRetEsp, MAT_CondRet,
					"Erro ao inserir linha.") ;

		 } /* fim ativa: Testar inserir linha */

		 /* Testar ler célula */
		 else if ( strcmp( ComandoTeste , CMD_LER_CELULA ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "iiiii", &inxMatriz,
						&coluna, &linha, &inxPilha, &CondRetEsp ) ;
			 if ( (numLidos != 5)
				 || !ValidarInxMatriz(inxMatriz) )
			 {
				 return TST_CondRetParm ;
			 } /* if */
			 
			 /* Caso especial: parâmetro de retorno nulo */
			 if ( (linha < 0 ) || (coluna < 0) )
			 {
				 MAT_CondRet = MAT_LerCelula (vtMatrizes[inxMatriz],
								coluna, linha, NULL);
			 } else
			 {
				 MAT_CondRet = MAT_LerCelula (vtMatrizes[inxMatriz],
								coluna, linha, &Pilha);
			 } /* if */

			 if (MAT_CondRet != MAT_CondRetOK )
			 {
				 return TST_CompararInt( CondRetEsp, MAT_CondRet,
					"Erro ao ler célula da matriz.") ;
			 } /* if */
			 
			 if (Pilha != vtPilhas[inxPilha])
			 {
				 return TST_CompararPonteiro(vtPilhas[inxPilha], Pilha,
						"Pilha diferente da esperada.");
			 } /* if */

			 return TST_CondRetOK;
		 } /* fim ativa: Testar ler célula */

		 /* Testar escrever célula */
		 else if ( strcmp( ComandoTeste , CMD_ESCREVER_CELULA ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "iiiii", &inxMatriz,
						&coluna, &linha, &inxPilha, &CondRetEsp ) ;
			 if ( (numLidos != 5)
				 || !ValidarInxMatriz(inxMatriz) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 MAT_CondRet = MAT_EscreverCelula(vtMatrizes[inxMatriz],
							coluna, linha, vtPilhas[inxPilha]);
			 
			 return TST_CompararInt(CondRetEsp, MAT_CondRet,
					"Erro ao escrever na célula");
		 } /* fim ativa: Testar escrever célula */

		 /* Testar excluir coluna */
		 else if ( strcmp( ComandoTeste , CMD_EXCLUIR_COLUNA ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "iii", &inxMatriz, &coluna,
											&CondRetEsp);
			 if ( (numLidos != 3)
				 || !ValidarInxMatriz(inxMatriz) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 MAT_CondRet = MAT_ExcluirColuna(vtMatrizes[inxMatriz], coluna);

			 return TST_CompararInt(CondRetEsp, MAT_CondRet,
									"Erro ao excluir coluna");
		 } /* fim ativa: Testar excluir coluna */

		 /* Testar excluir linha */
		 else if ( strcmp( ComandoTeste , CMD_EXCLUIR_LINHA ) == 0 )
		 {
			 numLidos = LER_LerParametros ( "iii", &inxMatriz, &linha,
											&CondRetEsp);
			 if ( (numLidos != 3)
				 || !ValidarInxMatriz(inxMatriz) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 MAT_CondRet = MAT_ExcluirLinha(vtMatrizes[inxMatriz], linha);

			 return TST_CompararInt(CondRetEsp, MAT_CondRet,
									"Erro ao excluir linha");
		 } /* fim ativa: Testar excluir linha */

	  return TST_CondRetNaoConhec ;

   } /* Fim função: TPIL &Testar pilha */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TMAT -Validar indice de pilha
*
***********************************************************************/

   int ValidarInxPilha( int inxPilha , int Modo )
   {

      if ( ( inxPilha <  0 )
        || ( inxPilha >= DIM_VT_PILHA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtPilhas[ inxPilha ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtPilhas[ inxPilha ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TMAT -Validar indice de pilha */


/***********************************************************************
*
*  $FC Função: TMAT -Validar indice de matriz
*
***********************************************************************/

   int ValidarInxMatriz( int inxMatriz )
   {

      if ( ( inxMatriz <  0 )
        || ( inxMatriz > DIM_VT_MATRIZ ))
      {
         return FALSE ;
      } /* if */
         
      return TRUE ;

   } /* Fim função: TMAT -Validar indice de matriz */

/********** Fim do módulo de implementação: TMAT Teste pilha genérica **********/