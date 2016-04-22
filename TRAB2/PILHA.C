/***************************************************************************
*  $MCI Módulo de implementação: PIL  Módulo pilha genérica
*
*  Arquivo gerado:              PILHA.c
*  Letras identificadoras:      PIL
*
*  Nome da base de software:    
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PILHA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gdl - Guido Dowsley Leme
*           jpd - José Paulo Diniz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  2		  jpd	16/abr/2016 Corrigiu o módulo para o uso de listas
*     1       gdl   11/abr/2016 Início do desenvolvimento
*
***************************************************************************/

#include<stdio.h>
#include<malloc.h>

#define PILHA_OWN
#include "PILHA.h"
#include "LISTA.h"
#undef PILHA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de pilha
*
*
***********************************************************************/

   typedef struct PIL_tagPilha {

         int numElem ;
               /* Número de elementos da pilha */

		 LIS_tppLista Lista;
				/* Ponteiro para a lista onde serão armazenados os elementos da pilha */

   } PIL_tpPilha ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PIL  &Criar Pilha
*  ****/

	 PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha * ppPilha )
	 {
		 LIS_tpCondRet LIS_CondRet;
		 LIS_tppLista *pLista = NULL;
		 PIL_tpPilha *pPilha = NULL;

		 pLista = (LIS_tppLista*) malloc (sizeof(LIS_tppLista));
		 pPilha = (PIL_tpPilha*) malloc (sizeof(PIL_tpPilha));
		 pPilha->numElem = 0;

		 if (pPilha == NULL || pLista == NULL) {
			 return PIL_CondRetFaltouMemoria ;
		 } /* if */

		 LIS_CondRet = LIS_CriarLista ( pLista );
		 if (LIS_CondRet == LIS_CondRetFaltouMemoria) {
			 return PIL_CondRetFaltouMemoria ;
		 } /* if */

		 pPilha->Lista = *pLista;
		 *ppPilha = pPilha;

		 return PIL_CondRetOK ;
		 
	 } /* Fim função: PIL &Criar Pilha */
	 
/***************************************************************************
*
*  Função: PIL Esvaziar Pilha
*  ****/

	PIL_tpCondRet PIL_EsvaziarPilha(PIL_tppPilha pPilha)
	{
		LIS_EsvaziarLista ( pPilha->Lista ) ;
		pPilha->numElem = 0;

		return PIL_CondRetOK;
	}/* Fim função: PIL Destruir Pilha */

/***************************************************************************
*
*  Função: PIL Destruir pilha
*  ****/

	PIL_tpCondRet PIL_DestruirPilha(PIL_tppPilha pPilha)
	{
		LIS_DestruirLista ( pPilha->Lista ) ;
		free(pPilha);

		return PIL_CondRetOK;
	}/* Fim função: PIL Destruir Pilha */

/***************************************************************************
*
*  Função: PIL &Adicionar elemento na pilha
*  ****/

	PIL_tpCondRet PIL_Empilha(PIL_tppPilha pPilha, void * Valor)
	{
		LIS_tpCondRet LIS_CondRet ;

		LIS_CondRet = LIS_InserirElementoApos ( pPilha->Lista, Valor );

		if (LIS_CondRet == LIS_CondRetFaltouMemoria) {
			return PIL_CondRetFaltouMemoria ;
		} /* if */

		pPilha->numElem++;

		return PIL_CondRetOK;
	} /* Fim função: PIL &Inserir elemento na pilha */
	
/***************************************************************************
*
*  Função: PIL  &Remover elemento da pilha
*  ****/
	
	PIL_tpCondRet PIL_Desempilha(PIL_tppPilha pPilha)
	{
		LIS_tpCondRet LIS_CondRet;

		LIS_CondRet = LIS_ExcluirElemento ( pPilha->Lista ) ;
		if (LIS_CondRet == LIS_CondRetListaVazia) {
			return PIL_CondRetPilhaVazia ;
		} /*if*/

		pPilha->numElem--;

		return PIL_CondRetOK;
	} /* Fim função: PIL &Remover elemento da pilha */
	
/***************************************************************************
*
*  Função: PIL  &Obter referência para o valor contido no elemento do topo
*  ****/	
	
	PIL_tpCondRet PIL_ObterValor(PIL_tppPilha pPilha, void *pValor)
	{
		LIS_tpCondRet LIS_CondRet;

		if (pPilha == NULL) {
			return PIL_CondRetPilhaNaoExiste;
		} /* if */

		LIS_CondRet = LIS_ObterValor( pPilha->Lista, pValor );
		if (LIS_CondRet == LIS_CondRetNaoAchou) {
			return PIL_CondRetPilhaVazia ;
		}

		return PIL_CondRetOK;
		
	} /* Fim função: PIL &Obter Valor do elemento do topo */
	
/********** Fim do módulo de implementação: PIL Módulo pilha **********/