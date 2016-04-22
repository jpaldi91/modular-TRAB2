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
*	  O módulo de pilha é composto por um inteiro, que guarda a quantidade de 
*	  elementos da pilha e um ponteiro para Lista, que faz referência à lista que
*	  contém os elementos da pilha.
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

/* Tipo referência para uma pilha */

typedef struct PIL_tagPilha * PIL_tppPilha ;


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
*
*  $FV Valor retornado
*	  PIL_CondRetOK
*	  PIL_COndRetFaltouMemoria
*
*	$AE Assertivas de entrada
*	  - ppPilha recebe o endereço da pilha a ser criada
*
*	$AS Assertivas de saida
*	  - A pilha foi criada e seu endereço foi inserido em ppPilha
*	  - A pilha está vazia. Portanto não possui elemento corrente.
*
***********************************************************************/


   PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha * ppPilha ) ;


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
*  $AE Assertivas de Entrada
*	 - pPilha aponta para a pilha a ser esvaziada
*	 - valem as assertivas estruturais da pilha
*
*  $AE Assertivas de Saida
*	 - a pilha está vazia. Portanto não possui elemento corrente.
*
***********************************************************************/


   PIL_tpCondRet PIL_EsvaziarPilha(PIL_tppPilha pPilha) ;


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
*	$AE Assertivas de Entrada
*	  - pPilha aponta para a Pilha a ser destruida
*	  - valem as assertivas estruturais da Pilha
*
*	$AS Assertivas de Saida
*	  - Pilha foi esvaziada e excluida
*	  - pPilha agora tem valor NULL
*
***********************************************************************/

   PIL_tpCondRet PIL_DestruirPilha(PIL_tppPilha pPilha) ;


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
*  $AE Assertivas de entrada
*	 - pPilha aponta para a pilha onde deseja-se inserir o elemento
*	 - valem as assertivas estruturais da pilha
*    - se a pilha estiver vazia, sera criado o primeiro elemento dela
*
*  $AS Assertivas de saida
*    - elemento foi criado no topo da pilha
*	 - pElemCorr agora aponta para o ultimo elemento criado
*	 - valem as assertivas estruturais da pilha
*
***********************************************************************/

   PIL_tpCondRet PIL_Empilha(PIL_tppPilha pPilha, void * Valor) ;

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
*  $AE Assertivas de entrada
*	 - pLista aponta para pilha onde deseja-se excluir o elemento
*	 - valem as assertivas estruturais da pilha
*
*  $AS Assertivas de saida
*    - elemento foi excluido
*	 - valem as assertivas estruturais da pilha
*
***********************************************************************/

	PIL_tpCondRet PIL_Desempilha(PIL_tppPilha pPilha) ;
	
/***********************************************************************
*	
*  $FC Função: PIL &Obter valor do elemento no topo
*
*  $EP Parâmetros
*	  pPilha - endereço da pilha que deseja-se observar.
*	  Valor - parâmetro que receberá o valor contido no
*	  elemento. Este parâmetro é passado por referência
*
*  $FV Valor retornado
*	  PIL_CondRetOK
*	  PIL_CondRetPilhaNaoExiste
*	  PIL_CondRetPilhaVazia
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a pilha onde deseja-se obter o valor do elemento topo
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*  $AS Assertivas de saida
*	 - pValor contem o endereço do valor desejado do topo da pilha
*	 - valem as assertivas estruturais da pilha
*
***********************************************************************/

	PIL_tpCondRet PIL_ObterValor(PIL_tppPilha pPilha, void *pValor) ;
	
#undef PILHA_EXT

/********** Fim do módulo de definição: Módulo pilha **********/

#else
#endif
	  
