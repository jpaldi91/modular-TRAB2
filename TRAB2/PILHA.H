#if ! defined( PILHA_ )
#define PILHA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo pilha genérica
*
*  Arquivo gerado:              PILHA.H
*  Letras identificadoras:      PIL
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
*	  2.0	   jpd	16/abr/2016 Corrigiu o módulo para o uso de listas
*	  1.0	   gdl	07/04/2016	Início do desenvolvimento 
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar pilhas genéricas.
*     Ao iniciar a execução do programa não existe pilha.
*	  O módulo de pilha é, essencialmente, o módulo de listas, porém com algumas
*	  diferenças a serem respeitadas.
*	  Todo elemento incluído na pilha é adicionado no final da mesma. Chamaremos
*	  o final da pilha de "topo".
*	  O elemento corrente da pilha aponta sempre para o topo da mesma.
*	  Só é permitido remover elementos do topo da pilha.
*	  As pilhas poderão estar vazias. Neste caso o valor do elemento no
*	  topo da pilha será NULL.
*
***************************************************************************/

#include "LISTA.H"

#if defined( PILHA_OWN )
   #define PILHA_EXT
#else
   #define PILHA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PIL Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PIL_CondRetOK ,
               /* Concluiu corretamente */

		 PIL_CondRetPilhaVazia ,
				/* A pilha não contém elementos */

         PIL_CondRetPilhaNaoExiste ,
               /* Pilha não existe */

         PIL_CondRetFaltouMemoria
               /* Faltou memória ao alocar dados */

   } PIL_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PIL  &Criar pilha
*
*  $ED Descrição da função
*     Cria uma pilha vazia e retorna a mesma por referência.
*  $FV Valor retornado
*	  PIL_CondRetOK
*	  PIL_COndRetFaltouMemoria
*
***********************************************************************/


   PIL_tpCondRet PIL_CriarPilha( LIS_tppLista * ppPilha ) ;


/***********************************************************************
*
*  $FC Função: PIL Esvaziar pilha
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a pilha
*
*  $FV Valor retornado
*     PIL_CondRetOK
*
***********************************************************************/


   PIL_tpCondRet PIL_EsvaziarPilha(LIS_tppLista pPilha) ;


/***********************************************************************
*
*  $FC Função: PIL Destruir pilha
*
*  $ED Descrição da função
*     Destrói os elementos da pilha passados por parâmetro.
*     Faz nada caso a pilha especificada não exista.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*
***********************************************************************/

   PIL_tpCondRet PIL_DestruirPilha(LIS_tppLista pPilha) ;


/***********************************************************************
*
*  $FC Função: PIL &Adicionar elemento na pilha
*
*  $ED Descrição da função
*     Adiciona um elemento no topo da pilha.
*     O ponteiro do elemento adicionado apontará para o elemento que
*	  estava antes no topo.
*
*  $EP Parâmetros
*	  pPilha - ponteiro da pilha em que será inserido o novo elemento.
*     Valor - valor a ser inserido no novo elemento.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

   PIL_tpCondRet PIL_Empilha(LIS_tppLista pPilha, void * Valor) ;

/***********************************************************************
*
*  $FC Função: PIL Remover elemento da pilha
*
*  $ED Descrição da função
*	  Remove o elemento do topo da pilha.
*	  O novo elemento do topo da pilha será o elemento que era apontado pelo o que foi
*	  removido.
*  $EP Parâmetros
*	  pPilha - ponteiro da pilha que será removido o elemento.
*
*  $FV Valor retornado
*	  PIL_CondRetOK
*	  PIL_CondRetPilhaVazia
*
***********************************************************************/

	PIL_tpCondRet PIL_Desempilha(LIS_tppLista pPilha) ;
	
/***********************************************************************
*	
*  $FC Função: PIL &Obter valor do elemento no topo
*  $EP Parâmetros
*	  pPilha - endereço da pilha que deseja-se observar.
*	  Valor - parâmetro que receberá o valor contido no
*	  elemento. Este parâmetro é passado por referência
*  $FV Valor retornado
*	  PIL_CondRetOK
*	  PIL_CondRetPilhaNaoExiste
*	  PIL_CondRetPilhaVazia
*
***********************************************************************/

	PIL_tpCondRet PIL_ObterValor(LIS_tppLista pPilha, void *pValor) ;
	
#undef PILHA_EXT

/********** Fim do módulo de definição: Módulo pilha **********/

#else
#endif
	  
