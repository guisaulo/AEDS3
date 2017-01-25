/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
lista.h: Possue o TAD e a declaração das funções usadas por uma estrutra de dados basica lista                
====================================================================================================================*/

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

/* =============================================== TAD Lista ====================================================== */

typedef int TipoChave;

typedef struct {
  	float Distancia; //guarda a distancia para uma resposta
  	char *Palavra;  //guarda a resposta corrigida
} TipoResposta;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  	TipoResposta Resposta;
  	TipoApontador Prox;
} TipoCelula;

typedef struct {
  	TipoApontador Primeiro, Ultimo;
} TipoLista;

/*============================================= Funções ============================================================*/

//Cria lista vazia
void FazListaVazia(TipoLista *Lista);
//Verifica se a lista esta vazia
int Vazia(TipoLista Lista);
//Insere uma reposta na lista
void InsereResposta(TipoResposta x, TipoLista *Lista);
//Retira uma reposta da lista
void RetiraResposta(TipoApontador p, TipoLista *Lista);
//Imprime a lista de respostas de uma aluno
void ImprimeRespostaAluno(TipoLista Lista, FILE *ArqSaida);

#endif // LISTA_H_INCLUDED