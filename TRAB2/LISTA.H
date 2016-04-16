#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Listas duplamente encadeadas
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gdl - Guido Dowsley Leme
*           jpd - José Paulo Diniz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  3		  jpd	06/abr/2016 adaptou o modulo para listas genericas
*     2       jpd   26/mar/2016 revisou o codigo e atualizou a documentacao
*     1       jpd   22/mar/2016 adaptou o modulo para o uso de varias listas
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     LIS_tppLista * - ponteiro para ponteiro de lista que será
*                      retornada por referência. Se ocorrer algum erro,
*                      o parâmetro não é modificado.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*	$AE Assertivas de entrada
*	  - ppLista recebe o endereço da lista a ser criada
*
*	$AS Assertivas de saida
*	  - A lista foi criada e seu endereço foi inserido em ppLista
*	  - A lista está vazia. Portanto não possui elemento corrente, origem nem fim.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * ppLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*	$ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*	$FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
*	$AE Assertivas de Entrada
*	  - pLista aponta para a Lista a ser destruida
*	  - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*	$AS Assertivas de Saida
*	  - lista foi esvaziada e excluida
*	  - pLista agora tem valor NULL
*
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*	$FV Valor retornado
*     LIS_CondRetOK    - esvaziou sem problemas
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $AE Assertivas de Entrada
*	 - pLista aponta para a lista a ser esvaziada
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*  $AE Assertivas de Saida
*	 - a lista está vazia. Portanto não possui elemento corrente, origem nem fim.
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     Valor - valor do novo elemento
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista onde deseja-se inserir o elemento
*    - pElemCorr aponta para o elemento onde será inserido um elemento anterior a ele
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*    - se a lista estiver vazia, sera criado o primeiro elemento dela
*
*  $AS Assertivas de saida
*    - elemento foi criado antes do nó corrente
*	 - pElemCorr agora aponta para o ultimo elemento criado
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void   *Valor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        Valor - valor do novo elemento
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista onde deseja-se inserir o elemento
*    - pElemCorr aponta para o elemento onde será inserido um elemento posterior a ele
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*    - se a lista estiver vazia, sera criado o primeiro elemento dela
*
*  $AS Assertivas de saida
*    - elemento foi criado depois do nó corrente
*	 - se pElemCorr era o último da lista, o novo elemento agora é o último da lista
*	 - pElemCorr agora aponta para o ultimo elemento criado
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void    *Valor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $AE Assertivas de entrada
*	 - pLista aponta para lista onde deseja-se excluir o elemento
*	 - pElemCorr aponta para o elemento a ser excluído
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*  $AS Assertivas de saida
*    - elemento foi excluido
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista onde deseja-se obter o valor do elemento
*	 - pElemCorr aponta para o nó cujo valor deseja-se obter
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*  $AS Assertivas de saida
*	 - pValor contem o endereço do valor desejado
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista ,  void * pValor) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*	$FV Valor retornado
*     LIS_CondRetOK    - alterou pElemCorr sem problemas
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista que deseja-se percorrer
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*  $AS Assertivas de saida
*	 - pElemCorr aponta para o inicio da lista
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
***********************************************************************/

   LIS_tpCondRet IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*	$FV Valor retornado
*     LIS_CondRetOK    - alterou pElemCorr sem problemas
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista que deseja-se percorrer
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*  $AS Assertivas de saida
*	 - pElemCorr aponta para o ultimo elemento da lista
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
***********************************************************************/

   LIS_tpCondRet IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
*  $AE Assertivas de entrada
*	 - numElem != 0
*	 - pLista aponta para a lista que deseja-se percorrer
*	 - a lista não deve estar vazia
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
*  $AS Assertivas de saida
*	 - se pElemCorr estiver a menos de |NumElem| do inicio ou fim da lista,
*				pElemCorr passa a apontar para uma das extremidades da lista
*	 - pElemCorr aponta para |NumElem| antes ou depois do elemento que apontava (depende do sinal)
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabeça
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
