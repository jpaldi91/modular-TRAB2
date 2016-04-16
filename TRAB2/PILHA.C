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

#define PILHA_OWN
#include "PILHA.h"
#include "LISTA.h"
#undef PILHA_OWN


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PIL  &Criar Pilha
*  ****/

	 PIL_tpCondRet PIL_CriarPilha( LIS_tppLista * ppPilha )
	 {
		 LIS_tpCondRet LIS_CondRet;

		 LIS_CondRet = LIS_CriarLista ( ppPilha );
		 if (LIS_CondRet == LIS_CondRetFaltouMemoria) {
			 return PIL_CondRetFaltouMemoria ;
		 } /* if */

		 return PIL_CondRetOK ;
		 
	 } /* Fim função: PIL &Criar Pilha */
	 
/***************************************************************************
*
*  Função: PIL Esvaziar Pilha
*  ****/

	PIL_tpCondRet PIL_EsvaziarPilha(LIS_tppLista pPilha)
	{
		LIS_EsvaziarLista ( pPilha ) ;

		return PIL_CondRetOK;
	}/* Fim função: PIL Destruir Pilha */

/***************************************************************************
*
*  Função: PIL Destruir pilha
*  ****/

	PIL_tpCondRet PIL_DestruirPilha(LIS_tppLista pPilha)
	{
		LIS_DestruirLista ( pPilha ) ;

		return PIL_CondRetOK;
	}/* Fim função: PIL Destruir Pilha */

/***************************************************************************
*
*  Função: PIL &Adicionar elemento na pilha
*  ****/

	PIL_tpCondRet PIL_Empilha(LIS_tppLista pPilha, void * Valor)
	{
		LIS_tpCondRet LIS_CondRet ;

		LIS_CondRet = LIS_InserirElementoApos ( pPilha, Valor );

		if (LIS_CondRet == LIS_CondRetFaltouMemoria) {
			return PIL_CondRetFaltouMemoria ;
		} /* if */

		return PIL_CondRetOK;
	} /* Fim função: PIL &Inserir elemento na pilha */
	
/***************************************************************************
*
*  Função: PIL  &Remover elemento da pilha
*  ****/
	
	PIL_tpCondRet PIL_Desempilha(LIS_tppLista pPilha)
	{
		LIS_tpCondRet LIS_CondRet;

		LIS_CondRet = LIS_ExcluirElemento ( pPilha ) ;
		if (LIS_CondRet == LIS_CondRetListaVazia) {
			return PIL_CondRetPilhaVazia ;
		} /*if*/

		return PIL_CondRetOK;
	} /* Fim função: PIL &Remover elemento da pilha */
	
/***************************************************************************
*
*  Função: PIL  &Obter referência para o valor contido no elemento do topo
*  ****/	
	
	PIL_tpCondRet PIL_ObterValor(LIS_tppLista pPilha, void *pValor)
	{
		LIS_tpCondRet LIS_CondRet;

		if (pPilha == NULL) {
			return PIL_CondRetPilhaNaoExiste;
		} /* if */

		LIS_CondRet = LIS_ObterValor( pPilha, pValor );
		if (LIS_CondRet == LIS_CondRetNaoAchou) {
			return PIL_CondRetPilhaVazia ;
		}

		//*(void **)pValor = endValor ;

		return PIL_CondRetOK;
		
	} /* Fim função: PIL &Obter Valor do elemento do topo */
	
/********** Fim do módulo de implementação: PIL Módulo pilha **********/