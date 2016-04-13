#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: 
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: gdl - Guido Dowsley Leme
*           jpd - José Paulo Diniz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  1.0	   gdl	13/abr/2016	Início do desenvolvimento 
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar matrizes.
*     Ao iniciar a execução do programa não existe matriz.
*
***************************************************************************/

#include "LISTA.H"
#include "PILHA.H"
#if defined( MAT_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct MAT_tgMAT * MAT_tppMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

          MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetErroEstrutura = 1 ,
               /* Estrutura da matriz está errada */

         MAT_CondRetMatrizNaoExiste = 2 ,
               /* Matriz não existe */

         MAT_CondRetMatrizVazia = 3 ,
               /* Matriz está vazia */

         MAT_CondRetFaltouMemoria = 4
               /* Faltou memória ao alocar dados */
			   
		 MAT_CondRetColunaNaoExiste = 5
			   /* Coluna não existe */
				
		 MAT_CondRetLinhaNaoExiste = 6
			   /* Linha não existe */

   } MAT_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PIL  &Criar matriz
*
*  $ED Descrição da função
*     Cria uma matriz vazia e retorna a mesma por referência.
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_COndRetFaltouMemoria
*
***********************************************************************/


   MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz * pMatriz ) ;
   
   
/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói os elementos da matriz passados por parâmetro.
*     Faz nada caso a matriz especificada não exista.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( MAT_tppMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir coluna
*
*  $ED Descrição da função
*     Adiciona uma coluna à matriz.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirColuna( MAT_tppMatriz Matriz ) ;

/***********************************************************************
*
*  $FC Função: MAT Exlcuir coluna
*
*  $ED Descrição da função
*	  Remove uma coluna da matriz.
*  $EP Parâmetros
*	  Coluna - número da coluna.
*
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_CondRetColunaNaoExiste
*
***********************************************************************/

	MAT_tpCondRet MAT_ExcluirColuna (MAT_tppMatriz Matriz, int Coluna) ;
	
/***********************************************************************
*
*  $FC Função: MAT Inserir linha
*
*  $ED Descrição da função
*     Adiciona uma linha à matriz.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirLinha( MAT_tppMatriz Matriz ) ;

/***********************************************************************
*
*  $FC Função: MAT Exlcuir linha
*
*  $ED Descrição da função
*	  Remove uma linha da matriz.
*  $EP Parâmetros
*	  Linha - número da coluna.
*
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_CondRetLinhaNaoExiste
*
***********************************************************************/
	
	MAT_tpCondRet MAT_ExcluirLinha(MAT_tppMatriz Matriz, int Linha) ;
	
/***********************************************************************
*
*  $FC Função: MAT Ler célula
*
*  $ED Descrição da função
*	  Lê o valor que está na célula
*  $EP Parâmetros
*	  Coluna - número da coluna
*	  Linha - número da linha
*	  *Pilha - endereço da pilha
*
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_CondRetColunaNaoExiste
*	  MAT_CondRetLinhaNaoExiste
*	  MAT_CondRetCelulaVazia
*
***********************************************************************/

	MAT_tpCondRet MAT_LerCelula(MAT_tppMatriz Matriz, int Coluna, int Linha, PI_tppPilha *Pilha) ;
	
/***********************************************************************
*
*  $FC Função: MAT Escrever célula
*
*  $ED Descrição da função
*	  Escrever na célula
*  $EP Parâmetros
*	  Coluna - número da coluna
*	  Linha - número da linha
*	  *Pilha - endereço da pilha
*
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_CondRetColunaNaoExiste
*	  MAT_CondRetLinhaNaoExiste
*
***********************************************************************/
	
	MAT_tpCondRet MAT_EscreverCelula(MAT_tppMatriz Matriz, int Coluna, int Linha, PI_tppPilha *Pilha) ;
	

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo pilha **********/

#else
#endif