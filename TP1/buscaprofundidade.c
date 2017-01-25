#include<stdio.h>
#include<stdlib.h>
#include "busca.h"

//Faz Pilha Vazia
void FPVazia(TipoPilha *Pilha){

    Pilha->Topo=(TipoApontador) malloc(sizeof(TipoCelula));
    Pilha->Fundo=Pilha->Topo;
    Pilha->Topo->Prox=NULL;
    Pilha->Tamanho = 0;
}

//Verifica se uma pilha esta vazia
int PilhaVazia(TipoPilha Pilha){

    return (Pilha.Topo == Pilha.Fundo);
}

//Empilha um vertice no topo da Pilha
void Empilha(TipoItem x, TipoPilha *Pilha){

    TipoApontador Aux;
    Aux = (TipoApontador) malloc(sizeof(TipoCelula));
    Pilha->Topo->Item = x;
    Aux->Prox = Pilha->Topo;
    Pilha->Topo = Aux;
    Pilha->Tamanho++;
}

//Desempilha um vertice do topo da Pilha
void Desempilha(TipoPilha *Pilha, TipoItem *Item){

    TipoApontador q;
    if (PilhaVazia(*Pilha))
        return;
    q = Pilha->Topo;
    Pilha->Topo = q->Prox;
    *Item = q->Prox->Item;
    free(q);
    Pilha->Tamanho--;
}

//Busca em profundidade iterativa usando pilha em que encontra o caminho entre 2 vertices
void BuscaEmProfundidade(TipoValorVertice u, TipoValorVertice Final, TipoGrafo *Grafo, FILE *saida){

    TipoValorVertice i, VerticeTopoPilha, v;
    TipoCor Cor[Grafo->NumVertices];
    TipoApontador Aux;
    TipoItem Item;
    TipoPeso Peso;
    TipoPilha Pilha;
    short FimListaAdj;

    for(i=1; i<=Grafo->NumVertices; i++) //inicialisa todos vertices de branco
        Cor[i]=branco;

    Cor[u]=cinza; //colore o primeiro vertice raiz de cinza

    //Poe o vertice raiz no topo da pilha
    FPVazia(&Pilha);
    Item.Vertice=u;
    Empilha(Item, &Pilha);
    fprintf(saida, "%d ", u);

    while(!PilhaVazia(Pilha)){ //Enquanto estiver vertices na pilha faça

        //Pega o vertice do topo e seu primeiro vertice adjacente branco
        VerticeTopoPilha=Pilha.Topo->Prox->Item.Vertice;
        Aux=PrimeiroListaAdj(&VerticeTopoPilha, Grafo);
        FimListaAdj=FALSE;

        while(!FimListaAdj){ //Enquanto existir adjacentes a aux não descobertos (brancos) faça
            ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj); //Prox Adjacente
            if(Aux!=NULL && Cor[v]==branco){ //se o vertice for branco, marque v como descoberto (cinza);
                fprintf(saida, "%d ", v);
                Cor[v]=cinza;
                Item.Vertice=v;
                Empilha(Item, &Pilha); //empilha (***está com erro de segmentation fault aqui, na segunda iteração***)
            }
        } //Fim do enquanto fim da lista de adjacentes

        fprintf(saida, "%d " , VerticeTopoPilha);
        Cor[VerticeTopoPilha]=preto; //Marque v como terminado (preto);
        Item.Vertice=VerticeTopoPilha;
        Desempilha(&Pilha, &Item);

    } //Fim do enquanto (pilha vazia)
    fprintf(saida, "\n");
}
