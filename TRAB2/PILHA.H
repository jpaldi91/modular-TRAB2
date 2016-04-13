#if ! defined( PILHA_ )
#define PILHA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo pilha
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
*	  1.0	   gdl	07/04/2016	Início do desenvolvimento 
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar pilhas genéricas.
*     Ao iniciar a execução do programa não existe pilha.
*	  O módulo de pilha é formado por duas estruturas a da própria pilha
*	  e a estrutura elemento.
*	  A estrutura pilha possui um ponteiro para o elemento no topo da pilha.
*	  A estrutura elemento possui a informação armazenada e um ponteiro para o elemento anterior.
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

typedef struct PIL_tgPilha * PIL_tppPilha ;

/***********************************************************************
*
*  $TC Tipo de dados: PIL Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PIL_CondRetOK = 0 ,
               /* Executou correto */

         PIL_CondRetNaoCriouElemento = 1 ,
               /* Não criou Elemento */

         PIL_CondRetErroEstrutura = 2 ,
               /* Estrutura da pilha está errada */

         PIL_CondRetPilhaNaoExiste = 3 ,
               /* Pilha não existe */

         PIL_CondRetPilhaVazia = 4 ,
               /* Pilha está vazia */

         PIL_CondRetFaltouMemoria = 5
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


   PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha * ppPilha ) ;


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

   PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha pPilha ) ;


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
*     PIL_CondRetErroEstrutura
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

   PIL_tpCondRet PIL_Empilha( PIL_tppPilha pPilha, void Valor ) ;

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
*	  PIL_CondRet
*	  PIL_CondRetPilhaVazia
*
***********************************************************************/

	PIL_tpCondRet PIL_Desempilha (PIL_tppPilha pPilha) ;
	
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

	PIL_tpCOndRet PIL_ObterValor(PIL_tppPilha, void *Valor) ;
	
#undef PILHA_EXT

/********** Fim do módulo de definição: Módulo pilha **********/

#else
#endif
	  
