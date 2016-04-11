/***************************************************************************
*  $MCI Módulo de implementação: PIL  Módulo pilha
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
*     1       gdl   11/abr/2016 Início do desenvolvimento
*
***************************************************************************/

#include<stdio.h>



#define PILHA_OWN
#include "PILHA.h"
#include "LISTA.h"
#undef PILHA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PIL Descritor do elemento da pilha
*
*
***********************************************************************/

typedef struct tgElemPilha{
	void* Valor;
		/* Valor contido no elemento */
	struct tgElemPilha *pProx;
		/* Ponteiro para o próximo elemento da pilha */	
} tpElemPilha;

/***********************************************************************
*
*  $TC Tipo de dados: PIL Descritor da pilha
*
*
***********************************************************************/

typedef struct PIL_tgPilha{
	tpElemPilha *pPrim;
		/* Ponteiro para o topo da pilha */
} tpPilha;

/***** Protótipos das funções encapsuladas no módulo *****/

   static void LiberarElemento( PIL_tppPilha   pPilha, tpElemPilha  * pElem   ) ;

   static tpElemPil * CriarElemento( PIL_tppPilha pPilha, void *Valor  ) ;

   static void DestroiPilha( PIL_tppPilha pPilha ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PIL  &Criar Pilha
*  ****/

	 PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha * ppPilha )
	 {
		 PIL_tpPilha * pPilha = NULL;
		 pPilha = ( PIL_tpPilha * ) malloc( sizeof( PIL_tpPilha )) ;
		if ( pPilha == NULL )
		{
			return PIL_CondRetFaltouMemoria ;
		} /* if */
		pPilha->pPrim = NULL;
		
		*ppPilha = pPilha;		
		 
		 return PIL_CondRetOK; 
		 
	 } /* Fim função: PIL &Criar Pilha */
	 
/***************************************************************************
*
*  Função: PIL Destruir pilha
*  ****/

	PIL_tpCondRet PIL_DestruirPilha(PIL_tppPilha pPilha)
	{
		if(pPilha != NULL){
			if (pPrim != NULL){
				DestroiPilha(pPilha->pPrim);
			}
		}
		else
			return PIL_CondRetPilhaNaoExiste;
		
		return PIL_CondRetOK;
	}/* Fim função: PIL Destruir Pilha */

/***************************************************************************
*
*  Função: PIL &Adicionar elemento na pilha
*  ****/

	PIL_tpCondRet PIL_Empilha(PIL_tppPilha pPilha, void * Valor)
	{
	
		tpElemPilha *pElem;
		
		if(pPilha == NULL)
			return PIL_CondRetPilhaNaoExiste;
		
		pElem = CriarElemento(pPilha, Valor ) ;
		if (pElem == NULL)
			return PIL_CondRetFaltouMemoria;
		
		if(pPilha->pPrim == NULL)
			pPilha->pPrim = pElem;
		
		else{
			pElem->pProx = pPilha->pPrim;
			pPilha->pPrim = pElem;	
		} /* if */
		
		return PIL_CondRetOK;
	} /* Fim função: PIL &Inserir elemento na pilha */
	
/***************************************************************************
*
*  Função: PIL  &Remover elemento da pilha
*  ****/
	
	PIL_tpCondRet PIL_Desempilha(PIL_tppPilha pPilha){
		
		tpElemPilha *pElem;
		
		if(pPilha == NULL)
			return PIL_CondRetPilhaNaoExiste;
		if(pPilha->pPrim == NULL)
			return PIL_CondRetPilhaVazia;
		
		pElem = pPilha->pPrim;
		pPilha->pPrim = pElem->pProx;
		free(pElem);
		return PIL_CondRetOK;
	} /* Fim função: PIL &Remover elemento da pilha */
	
/***************************************************************************
*
*  Função: PIL  &Obter Valor do elemento do topo
*  ****/	
	
	PIL_tpCOndRet PIL_ObterValor(PIL_tppPilha, void *Valor)
	{
		if(pPilha == NULL)
			return PIL_CondRetPilhaNaoExiste;
		
		if(pPilha->pPrim == NULL)
			return PIL_CondRetPilhaVazia;
		
		*Valor = pPilha-pPrim->pValor;
		return PIL_CondRetOK;
		
	} /* Fim função: PIL &Obter Valor do elemento do topo */
	
/********** Fim do módulo de implementação: PIL Módulo pilha **********/