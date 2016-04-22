/***************************************************************************
*  $MCI Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              matriz.c
*  Letras identificadoras:      MAT
*
*  Projeto: Disciplina INF 1301
*  Autores: gdl - Guido Dowsley Leme
*			jpd - José Paulo Diniz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  3.0	   jpd  20/abr/2016 Revisou a documentação do módulo
*	  2.0	   jpd  19/abr/2016 Implementou o módulo para o uso de matriz de pilhas
*	  1.0	   gdl	13/abr/2016	Início do desenvolvimento 
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   "matriz.h"

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da célula da matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct MAT_tgCelulaMatriz {

         struct MAT_tgCelulaMatriz * pNorte ;
		 struct MAT_tgCelulaMatriz * pSul ;
		 struct MAT_tgCelulaMatriz * pLeste ;
		 struct MAT_tgCelulaMatriz * pOeste ;
               /* Ponteiros para as células adjacentes
                *
                *$EED Assertivas estruturais
                *   Cada ponteiro só é NULL se não existir uma célula
                *   na direção correspondente
                *   Se não for NULL, a célula apontada tem um ponteiro na
                *   direção oposta apontando para esta célula
                *   Norte <-> Sul
                *   Leste <-> Oeste
                */

         PIL_tppPilha Pilha ;
               /* Estrutura de pilha contida na célula */

   } MAT_tpCelulaMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma matriz
*
*
*  $ED Descrição do tipo
*     A cabeça da matriz é o ponto de acesso para uma determinada matriz.
*     Por intermédio da referência para célula corrente e dos ponteiros
*     para as células vizinhas pode-se navegar a matriz sem necessitar
*     de uma lista.
*     Pode-se, inclusive, operar com a matriz em forma de co-rotina.
*     Os índices LinhaCorr e ColCorr permitem calcular a posição
*     relativa entre a célula corrente e a desejada pelo usuário.
*     QuantidadeLinhas e QuantidadeColunas permitem determinar se a célula desejada
*     existe sem a necessidade de navegar na matriz.
*
***********************************************************************/

   typedef struct MAT_tgMatriz {

         MAT_tpCelulaMatriz * pCelRaiz ;
               /* Ponteiro para a raiz da matriz: Célula superior esquerda,
                * Coluna 0, Linha 0 */

         MAT_tpCelulaMatriz * pCelCorr ;
               /* Ponteiro para o nó corrente da matriz */

         int LinhaCorr ;
               /* Índice da linha de pCelCorr */

         int ColCorr ;
               /* Índice da coluna de pCelCorr */

         int QuantidadeLinhas ;
               /* Número de linhas da matriz */

         int QuantidadeColunas ;
               /* Número de colunas da matriz */

   } MAT_tpMatriz ;


/***** Protótipos das funções encapuladas no módulo *****/

   static MAT_tpCondRet ObterCelulaNasCoordenadas( MAT_tppMatriz Matriz , int Coluna , int Linha ,
                                                   MAT_tpCelulaMatriz ** Celula ) ;

   static void ExcluirCelula( MAT_tpCelulaMatriz * cel ) ;



/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar matriz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz * ppMatriz )
   {
		
	   MAT_tpMatriz * pMat ;

	  if ( ppMatriz == NULL )
      {
         return MAT_CondRetPonteiroRetornoNulo ;
      } /* if */
	  
	   pMat = (MAT_tpMatriz *) calloc (sizeof(MAT_tpMatriz), 1);
	   
	   if (pMat == NULL)
	   {
		   return MAT_CondRetFaltouMemoria ;
	   } /* if */
	   
	   *ppMatriz = pMat;
	   
	   return MAT_CondRetOK ;

   } /* Fim função: MAT  &Criar matriz */

/***************************************************************************
*
*  Função: MAT Destruir matriz
*  ****/

	MAT_tpCondRet MAT_DestruirMatriz( MAT_tppMatriz Matriz )
	{
		MAT_tpMatriz * pMatriz = (MAT_tpMatriz *) Matriz;
		MAT_tpCelulaMatriz * pCel ;
		if ( pMatriz != NULL )
		{
			if ( pMatriz->pCelRaiz != NULL )
			{
				pCel = pMatriz->pCelRaiz ;
				while ( pCel != NULL )
				{
					pCel = pCel->pSul ;
					MAT_ExcluirLinha( Matriz, 0 ) ;
				} /* while */
			} /* if */

			free( pMatriz ) ;
			pMatriz = NULL;
		} /* if */

		return MAT_CondRetOK;

	} /* Fim função: MAT &Destruir matriz */

/***************************************************************************
*
*  Função: MAT Inserir coluna
*  ****/

   MAT_tpCondRet MAT_InserirColuna( MAT_tppMatriz Matriz )
   {
		int linha;
		MAT_tpCelulaMatriz * cel = NULL,
						   * ultimaCriada = NULL,
						   * novaCelula = NULL;
		MAT_tpMatriz * pMatriz = ( MAT_tpMatriz * ) Matriz ;
		MAT_tpCondRet ret ;

		if ( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		/* Se a matriz estiver vazia, cria uma única célula */
		if ((pMatriz->QuantidadeColunas == 0) && (pMatriz->QuantidadeLinhas == 0))
		{
			pMatriz->pCelRaiz = (MAT_tpCelulaMatriz *) calloc(sizeof(MAT_tpCelulaMatriz),1);
			
			if (pMatriz->pCelRaiz == NULL)
			{
				return MAT_CondRetFaltouMemoria;
			} /* if */

			pMatriz->QuantidadeColunas = 1;
			pMatriz->QuantidadeLinhas = 1;
			pMatriz->pCelCorr = pMatriz->pCelRaiz;

			return MAT_CondRetOK;
		} /* if */

		/* Obtém a célula na primeira linha, última coluna */
		ret = ObterCelulaNasCoordenadas( Matriz, pMatriz->QuantidadeColunas - 1, 0, &cel);

		if (ret != MAT_CondRetOK)
		{
			return ret;
		} /* if */

		for (linha = 0; linha < pMatriz->QuantidadeLinhas; linha++)
		{
			if (cel == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula = (MAT_tpCelulaMatriz*) calloc(sizeof(MAT_tpCelulaMatriz), 1);

			if (novaCelula == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula->pOeste = cel;
			novaCelula->pNorte = ultimaCriada;

			if (ultimaCriada != NULL)
			{
				ultimaCriada->pSul = novaCelula;
			} /* if */

			ultimaCriada = novaCelula;
			cel->pLeste = novaCelula;
			cel = cel->pSul;
		} /* for */

		pMatriz->QuantidadeColunas++;

		return MAT_CondRetOK;
   } /* Fim função: MAT &Inserir coluna */


/***************************************************************************
*
*  Função: MAT Inserir linha
*  ****/
   MAT_tpCondRet MAT_InserirLinha( MAT_tppMatriz Matriz )
   {
	   int coluna;
	   MAT_tpCelulaMatriz * cel = NULL ,
						  * novaCelula = NULL ,
						  * ultimaCriada = NULL ;
	   MAT_tpMatriz *pMatriz = (MAT_tpMatriz *) Matriz;
	   MAT_tpCondRet ret;


	   if ( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		/* Se a matriz estiver vazia, cria uma única célula */
		if ((pMatriz->QuantidadeColunas == 0) && (pMatriz->QuantidadeLinhas == 0))
		{
			pMatriz->pCelRaiz = (MAT_tpCelulaMatriz *) calloc(sizeof(MAT_tpCelulaMatriz),1);
			
			if (pMatriz->pCelRaiz == NULL)
			{
				return MAT_CondRetFaltouMemoria;
			} /* if */

			pMatriz->QuantidadeColunas = 1;
			pMatriz->QuantidadeLinhas = 1;
			pMatriz->pCelCorr = pMatriz->pCelRaiz;

			return MAT_CondRetOK;
		} /* if */

		/* Obtém a célula na primeira coluna, última linha */
		ret = ObterCelulaNasCoordenadas( Matriz, 0, pMatriz->QuantidadeLinhas - 1, &cel );

		if (ret != MAT_CondRetOK)
		{
			return ret;
		} /* if */

		for (coluna = 0; coluna < pMatriz->QuantidadeColunas; coluna++)
		{
			if (cel == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula = (MAT_tpCelulaMatriz*) calloc(sizeof(MAT_tpCelulaMatriz), 1);

			if (novaCelula == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula->pNorte = cel;
			novaCelula->pOeste = ultimaCriada;

			if (ultimaCriada != NULL)
			{
				ultimaCriada->pLeste = novaCelula;
			} /* if */

			ultimaCriada = novaCelula;
			cel->pSul = novaCelula;
			cel = cel->pLeste;
		} /* for */

		pMatriz->QuantidadeLinhas++;

		return MAT_CondRetOK;
   } /* Fim função: MAT &Inserir linha */

/***************************************************************************
*
*  Função: MAT Ler célula
*  ****/

   MAT_tpCondRet MAT_LerCelula( MAT_tppMatriz Matriz , int Coluna , int Linha , PIL_tppPilha * Pilha )
   {
	   MAT_tpCelulaMatriz * pCel ;
	   MAT_tpCondRet ret;

      if ( Pilha == NULL )
      {
         return MAT_CondRetPonteiroRetornoNulo ;
      } /* if */

      ret = ObterCelulaNasCoordenadas( Matriz , Coluna , Linha , &pCel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

	  *Pilha = pCel->Pilha ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Ler célula */

/***************************************************************************
*
*  Função: MAT Escrever célula
*  ****/

   MAT_tpCondRet MAT_EscreverCelula( MAT_tppMatriz Matriz , int Coluna , int Linha , PIL_tppPilha Pilha )
   {

      MAT_tpCelulaMatriz * pCel ;
      MAT_tpCondRet ret ;
	  
	  ret = ObterCelulaNasCoordenadas( Matriz , Coluna , Linha , &pCel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */
	  
      pCel->Pilha = Pilha ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Escrever célula */

/***************************************************************************
*
*  Função: MAT Excluir coluna
*  ****/

   MAT_tpCondRet MAT_ExcluirColuna( MAT_tppMatriz Matriz , int Coluna )
   {

      MAT_tpMatriz * pMatriz = ( MAT_tpMatriz * ) Matriz ;
      MAT_tpCelulaMatriz * pCel ,
			             * pProximaCel ;
      MAT_tpCondRet ret ;
	  
	  ret = ObterCelulaNasCoordenadas( Matriz , Coluna , 0 , &pCel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      /* cel é obrigatoriamente válido a partir desse ponto */

      if ( Coluna == 0 )
      {
		  pMatriz->pCelRaiz = pCel->pLeste ;
      } /* if */

      /* Troca a célula corrente para a raiz caso ela seja excluida */
      if ( pMatriz->ColCorr == Coluna )
      {
         pMatriz->pCelCorr = pMatriz->pCelRaiz ;
         pMatriz->LinhaCorr = 0 ;
         pMatriz->ColCorr = 0 ;
      } /* if */

      /* Conserta ColCorr */
      if ( pMatriz->ColCorr > Coluna )
      {
         pMatriz->ColCorr -- ;
      } /* if */

      while ( pCel != NULL )
      {
         pProximaCel = pCel->pSul ;

         if ( pCel->Pilha != NULL )
         {
			 PIL_DestruirPilha(pCel->Pilha);
         } /* if */

         ExcluirCelula( pCel ) ;
         pCel = pProximaCel ;
      } /* while */

      pMatriz->QuantidadeColunas-- ;

      return MAT_CondRetOK;

   } /* Fim função: MAT Excluir coluna */

/***************************************************************************
*
*  Função: MAT Excluir linha
*  ****/

   MAT_tpCondRet MAT_ExcluirLinha( MAT_tppMatriz Matriz , int Linha )
   {

      MAT_tpMatriz * pMatriz = ( MAT_tpMatriz * ) Matriz ;
      MAT_tpCelulaMatriz * cel ,
					     * proximaCel ;
      MAT_tpCondRet ret ;
	  
	  ret = ObterCelulaNasCoordenadas( Matriz , 0 , Linha , &cel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      /* cel é obrigatoriamente válido a partir desse ponto */

      if ( Linha == 0 )
      {
         pMatriz->pCelRaiz = cel->pSul ;
      } /* if */

      /* Troca a célula corrente para a raiz caso ela seja excluida */
      if ( pMatriz->LinhaCorr == Linha )
      {
         pMatriz->pCelCorr = pMatriz->pCelRaiz ;
         pMatriz->LinhaCorr = 0 ;
         pMatriz->ColCorr = 0 ;
      } /* if */

      /* Conserta LinhaCorr */
      if ( pMatriz->LinhaCorr > Linha )
      {
         pMatriz->LinhaCorr -- ;
      } /* if */

      while ( cel != NULL )
      {
         proximaCel = cel->pLeste ;

         if ( cel->Pilha != NULL )
         {
            PIL_DestruirPilha( cel->Pilha ) ;
         } /* if */

         ExcluirCelula( cel ) ;
         cel = proximaCel ;
      } /* while */

      pMatriz->QuantidadeLinhas-- ;

      return MAT_CondRetOK;

   } /* Fim função: MAT Excluir linha */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: MAT Obter célula nas coordenadas
*
*  $ED Descrição da função
*     Essa função retorna um ponteiro para a célula da matriz nas coordenadas
*     (Coluna, Linha). Essa função tem o efeito colateral de atualizar o
*     ponteiro para a célula atual na estrutura da matriz.
*
*  $EP Parâmetros
*     $P Matriz - matriz que contém a célula desejada
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Celula - parâmetro para retorno do ponteiro para a célula desejada
*                 este parâmetro é passado por referência
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*
*  $AE Assertivas de saída
*      - Celula aponta para a celula desejada da matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK    - obteve a célula sem problemas
*     MAT_CondRetMatrizNaoExiste - o parâmetro Matriz é NULO
*     MAT_CondRetNaoPossuiCelula - coordenadas da célula estão fora da matriz
*     MAT_CondRetErroEstrutura - estrutura da matriz está corrompida
*
***********************************************************************/

   static MAT_tpCondRet ObterCelulaNasCoordenadas( MAT_tppMatriz Matriz , int Coluna , int Linha ,
                                                   MAT_tpCelulaMatriz ** Celula )
   {

      int distCol ,         /* Distância em colunas da célula atual para a desejada */
          distLin ;         /* Distância em linhas da célula atual para a desejada */

	  MAT_tpMatriz * pMatriz ;

      if ( Matriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      pMatriz = ( MAT_tpMatriz * ) Matriz ;

      if ( ( Coluna >= pMatriz->QuantidadeColunas )
        || ( Linha >= pMatriz->QuantidadeLinhas ))
      {
         return MAT_CondRetNaoPossuiCelula ;
      } /* if */

      if ( pMatriz->pCelCorr == NULL )
      {
         return MAT_CondRetErroEstrutura;
      } /* if */

      distCol = ( pMatriz->ColCorr - Coluna ) ;
	  if (distCol < 0)
	  {
		  distCol *= -1 ;
	  } /* if */

      distLin = ( pMatriz->LinhaCorr - Linha ) ;
	  if (distLin < 0)
	  {
		  distLin *= -1 ;
	  } /* if */

	  /* Percorre a matriz na horizontal */
      while (distCol != 0)
	  {
		  if (pMatriz->ColCorr < Coluna)
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pLeste;
			  pMatriz->ColCorr++;
		  } /* if */
		  else
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pOeste;
			  pMatriz->ColCorr--;
		  } /* else */

		  distCol--;
	  } /* while */

	  /* Percorre a matriz na vertical */
      while (distLin != 0)
	  {
		  if (pMatriz->LinhaCorr < Linha)
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pSul;
			  pMatriz->LinhaCorr++;
		  } /* if */
		  else
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pNorte;
			  pMatriz->LinhaCorr--;
		  } /* else */

		  distLin--;
	  } /* while */

      /* Retorna a célula obtida */
      *Celula = pMatriz->pCelCorr;
	  
      return MAT_CondRetOK ;
   } /* Fim função: Obter Celula nas Coordenadas */


/***********************************************************************
*
*  $FC Função: Excluir Célula
*
*  $ED Descrição da função
*     Essa função exclui a célula passada por parâmetro e troca os ponteiros
*     das células vizinhas de acordo.
*     Essa função não exclui a pilha armazenada na célula
*
*  $EP Parâmetros
*     $P cel - Célula a excluir
*              este parâmetro é passado por referência
*
*  $AE Assertivas de entrada
*      - cel != NULL
*
*  $AE Assertivas de saída
*      - Célula desejada foi excluída com sucesso
*	   - Valem as assertivas estruturais da matriz de pilhas deste módulo
*
***********************************************************************/

   static void ExcluirCelula( MAT_tpCelulaMatriz * cel )
   {
	   MAT_tpCelulaMatriz *pcel = cel;
	   if (cel ->pNorte != NULL)
	   {
		   cel->pNorte->pSul = cel->pSul;
	   } /* if */
	   
	   if (cel ->pSul != NULL)
	   {
		   cel->pSul->pNorte = cel->pNorte;
	   } /* if */

	   if (cel ->pLeste != NULL)
	   {
		   cel->pLeste->pOeste = cel->pOeste;
	   } /* if */

	   if (cel ->pOeste != NULL)
	   {
		   cel->pOeste->pLeste = cel->pLeste;
	   } /* if */

	   free( pcel ) ;

   } /* Fim função: Excluir Celula */