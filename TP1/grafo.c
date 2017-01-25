#include<stdio.h>
#include<stdlib.h>
#include "busca.h"

//Cria Lista de Adjacencia Vazia
void FLVazia(TipoLista *Lista){

    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

//Cria um Grafo Vazio
void FGVazio(TipoGrafo *Grafo){

    short i;
    for(i=1; i<=Grafo->NumVertices; i++)
       FLVazia(&Grafo->Adj[i]); //chama função pra inicializar todas listas de adjacentes como vazia
}

//Insere um vertice depois do ultimo item da lista
void Insere(TipoItem *x, TipoLista *Lista){

    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
}

//Insere uma aresta entre 2 vertices
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso, TipoGrafo *Grafo){

    TipoItem x;
    x.Vertice = *V2;
    x.Peso = *Peso;
    Insere(&x, &Grafo->Adj[*V1]); //chama função para inserir na lista de adjacentes
}

//Verifica se uma lista esta vazia
int ListaVazia(TipoLista Lista){

    return (Lista.Primeiro == Lista.Ultimo);
}

//Verifica se a lista  de adjacentes está vazia
int ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo){

    return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo); //uma lista está vazia se seu primeiro elemento é igual ao ultimo
}

//Retorna o primeiro vertice da lista de adjacentes de um dado vertice
TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo){

    return (Grafo->Adj[*Vertice].Primeiro->Prox);
}

//Retorna Adj apontado por Prox
void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox, short *FimListaAdj){

    /* --Retorna Adj apontado por Prox--*/
    *Adj = (*Prox)->Item.Vertice;
    *Peso = (*Prox)->Item.Peso;
    *Prox = (*Prox)->Prox;
    if (*Prox == NULL)
        *FimListaAdj=TRUE;
}
