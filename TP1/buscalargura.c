#include<stdio.h>
#include<stdlib.h>
#include "busca.h"

//Faz uma fila vazia
void FFVazia(TipoFila *Fila){

    Fila->Frente = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
}

//verifica se a fila está vazia
int FilaVazia(TipoFila Fila){

    return (Fila.Frente == Fila.Tras);
}

//enfileira um vertice na fila
void Enfileira(TipoItem x, TipoFila *Fila){

    Fila->Tras->Prox =(TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->Item = x;
    Fila->Tras->Prox = NULL;
}

//desenfileira um vertice da fila
void Desenfileira(TipoFila *Fila, TipoItem *Item){

    TipoApontador q;
    if (FilaVazia(*Fila)){
        printf(" Erro, fila esta  vazia\n");
        return;
    }
    q = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;
    *Item = Fila->Frente->Item;
    free(q);
}

//Busca em largura de um vertice inicial à um vertice final em um grafo
void BuscaEmLargura(TipoValorVertice u, TipoValorVertice Final, TipoGrafo *Grafo, FILE *saida){

    TipoCor Cor[MAXNUMVERTICES];
    TipoValorVertice v, x;
    short FimListaAdj;
    TipoApontador Aux;
    TipoPeso Peso;
    TipoItem Item;
    TipoFila Fila;

    for(x=1; x<=Grafo->NumVertices; x++) //inicialisa todos vertices de branco
        Cor[x]=branco;

    Cor[u]=cinza; //colore vertice inicial de branco

    FFVazia(&Fila); //cria uma fila vazia
    Item.Vertice=u;
    Enfileira(Item, &Fila); //enfileira o primeiro vertice na fila

    while(!FilaVazia(Fila)){ //enquanto existir vertices na fila, faça

        Desenfileira(&Fila, &Item); //tira o vertice da fila
        u=Item.Vertice;

        if(!ListaAdjVazia(&u, Grafo)){ //se existir vertices adjacentes ao vertice, faça
            Aux = PrimeiroListaAdj(&u, Grafo);
            FimListaAdj = FALSE;
         
            while(FimListaAdj == FALSE){ //enquanto a lista de adjacentes nao estiver fazia
                
                ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj);
                
                if(Cor[v] != branco) 
                    continue;
                Cor[v] = cinza;
                Item.Vertice = v;
                Enfileira(Item, &Fila);
            }
        }

        Cor[u]=preto;
        fprintf(saida,"%d ", u); //imprime os vertices visitados no arquivo de saida

        if(u==Final){   //caso o vertice for o vertice final, sai do loop
            fprintf(saida,"\n");
            break;
        }
    }
}

