#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Autores: gdl - Guido Dowsley Leme
*           jpd - José Paulo Diniz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  3.0	   jpd  20/abr/2016 Revisou a documentação do módulo
*	  2.0	   jpd  19/abr/2016 Implementou o módulo para o uso de matriz de pilhas
*	  1.0	   gdl	13/abr/2016	Início do desenvolvimento 
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     manipular matrizes de pilhas.
*	  
*	  A matriz é referenciada pelo usuário utilizando um ponteiro para
*	  uma estrutura alocada pela função MAT_CrarMatriz.
*	  Ao ser criada, uma matriz não possui linhas nem colunas. Estas
*	  devem ser adicionadas utilizando as funções  MAT_InserirLinha e
*	  MAT_InserirColuna. A primeira chamada de qualquer dessas funções
*	  cria uma única célula vazia.
*	  Cada célula da matriz pode conter uma pilha do tipo PIL_tppPilha.
*
***************************************************************************/

/***********************************************************************
*
*  Módulo de pilha
*
*
***********************************************************************/

#include "PILHA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct MAT_tgMatriz * MAT_tppMatriz ;

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

         MAT_CondRetNaoPossuiCelula = 3 ,
				/* Matriz não possui a célula desejada */
		 
		 MAT_CondRetFaltouMemoria = 4 ,
				/* Faltou memória ao alocar dados */

		 MAT_CondRetPonteiroRetornoNulo = 5
				/* Endereço passado por parâmetro para retorno é NULL */

   } MAT_tpCondRet ;

/***********************************************************************
*
*  $FC Função: MAT  &Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*	
*  $EP Parâmetros
*	  $P Matriz		 - parâmetro para retorno da matriz.
*					   Este parâmetro é passado por referência
*
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_CondRetPonteiroRetornoNulo
*	  MAT_COndRetFaltouMemoria
*
*  $AE Assertivas de entrada
*      - pMatriz != NULL
*
*  $AE Assertivas de saída
*      - pMatriz aponta para a nova matriz criada
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
***********************************************************************/


   MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz * pMatriz ) ;
   
   
/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz passada
*	  Essa função se encarrega de destruir as pilhas contidas na matriz.
*	  Faz nada caso a matriz passada não exista.
*
*  $EP Parâmetros
*	  $P Matriz - matriz a ser destruída
*
*  $FV Valor retornado
*     MAT_CondRetOK
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*
*  $AE Assertivas de saída
*      - Matriz desejada foi excluída com sucesso
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( MAT_tppMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir coluna
*
*  $ED Descrição da função
*     Adiciona uma coluna vazia à direita da matriz.
*
*  $EP Parâmetros
*	  $P Matriz - matriz a ser estendida
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*	  MAT_CondRetMatrizNaoExiste
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
*  $AE Assertivas de saída
*      - Matriz desejada agora possui uma nova coluna de células vazias à direita
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirColuna( MAT_tppMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir linha
*
*  $ED Descrição da função
*     Adiciona uma linha vazia abaixo da matriz.
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser estendida
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*	  MAT_CondRetMatrizNaoExiste
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
*  $AE Assertivas de saída
*      - Matriz desejada agora possui uma nova linha de células vazias abaixo
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirLinha( MAT_tppMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ler célula
*
*  $ED Descrição da função
*     Obtém a pilha contida em uma célula da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser lida
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Pilha  - retorno da pilha armazenada na célula
*                 Este parâmetro é passado por referência
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoPossuiCelula
*     MAT_CondRetPonteiroRetornoNulo
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*	   - Coluna < Matriz->QuantidadeColunas
*	   - Linha < Matriz->QuantidadeLinhas
*	   - Pilha != NULL
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
*  $AE Assertivas de saída
*      - Pilha aponta para a pilha contida na célula apontada da matriz desejada
*
***********************************************************************/

   MAT_tpCondRet MAT_LerCelula( MAT_tppMatriz Matriz , int Coluna , int Linha , PIL_tppPilha * Pilha ) ;


/***********************************************************************
*
*  $FC Função: MAT Escrever célula
*
*  $ED Descrição da função
*     Adiciona uma pilha a uma célula da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser modificada
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Pilha  - pilha a armazenar na célula
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoPossuiCelula
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*	   - Coluna < Matriz->QuantidadeColunas
*	   - Linha < Matriz->QuantidadeLinhas
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
*  $AE Assertivas de saída
*      - Célula selecionada da matriz desejada agora contém a pilha passada por parâmetro
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
***********************************************************************/

   MAT_tpCondRet MAT_EscreverCelula( MAT_tppMatriz Matriz , int Coluna , int Linha , PIL_tppPilha Pilha ) ;


/***********************************************************************
*
*  $FC Função: MAT Exlcuir coluna
*
*  $ED Descrição da função
*	  Exclui a coluna especificada da matriz.
*	  Essa função se encarrega de destruir as pilhas contidas na coluna excluida.
*
*  $EP Parâmetros
*	  $P Matriz - matriz a ser modificada.
*	  $P Coluna - coluna que se deseja excluir
*				  A coluna mais a esquerda tem índice 0
*
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_CondRetErroEstrutura
*	  MAT_CondRetMatrizNaoExiste
*	  MAT_CondRetNaoPossuiCelula
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*	   - Coluna < Matriz->QuantidadeColunas
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
*  $AE Assertivas de saída
*      - Coluna selecionada da matriz desejada foi excluída com sucesso
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
***********************************************************************/

	MAT_tpCondRet MAT_ExcluirColuna (MAT_tppMatriz Matriz, int Coluna) ;


/***********************************************************************
*
*  $FC Função: MAT Exlcuir linha
*
*  $ED Descrição da função
*	  Exclui a linha especificada da matriz.
*	  Essa função se encarrega de destruir as pilhas contidas na linha excluida.
*
*  $EP Parâmetros
*	  $P Matriz - matriz a ser modificada.
*	  $P Linha  - linha que se deseja excluir.
*				  A linha mais a esquerda tem índice 0
*
*  $FV Valor retornado
*	  MAT_CondRetOK
*	  MAT_CondRetErroEstrutura
*	  MAT_CondRetMatrizNaoExiste
*	  MAT_CondRetNaoPossuiCelula
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*	   - Linha < Matriz->QuantidadeLinhas
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
*  $AE Assertivas de saída
*      - Linha selecionada da matriz desejada foi excluída com sucesso
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
***********************************************************************/
	
	MAT_tpCondRet MAT_ExcluirLinha(MAT_tppMatriz Matriz, int Linha) ;
	

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo pilha **********/

#else
#endif