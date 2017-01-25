/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
lista.c: Possue as funções usadas por uma estrutra de dados basica lista                
====================================================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

//Cria lista vazia
void FazListaVazia(TipoLista *Lista){ 
    
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

//Verifica se a lista esta vazia
int Vazia(TipoLista Lista){ 

    return (Lista.Primeiro == Lista.Ultimo);
}

//Insere uma reposta na lista
void InsereResposta(TipoResposta x, TipoLista *Lista){ 
    
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Resposta = x;
    Lista->Ultimo->Prox = NULL;
}

//Retira uma reposta da lista
void RetiraResposta(TipoApontador p, TipoLista *Lista){ 

    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL){ 
        printf("Error! Lista vazia ou posicao  apontada nao existe\n");
        return;
    }
    q = p->Prox;
    p->Prox = q->Prox;
    if(p->Prox == NULL) 
        Lista->Ultimo = p;
    free(q);
}

//Imprime a lista de respostas de uma aluno
void ImprimeRespostaAluno(TipoLista Lista, FILE *ArqSaida){ 

    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL){ 
        fprintf(ArqSaida, "%s,%.1f ", Aux->Resposta.Palavra, Aux->Resposta.Distancia);
        Aux = Aux->Prox;
    }
}
