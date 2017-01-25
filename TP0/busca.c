#include <stdio.h>
#include <stdlib.h>
#include "busca.h"

//Cria Lista de Adjacencia Vazia
void FLVazia(TipoLista *Lista){

    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

//Verifica se uma lista esta vazia
int ListaVazia(TipoLista Lista){

    return (Lista.Primeiro == Lista.Ultimo);
}

//Insere depois do ultimo item da lista
void Insere(TipoItem *x, TipoLista *Lista){

    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
}

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

//Insere uma aresta entre 2 vertices
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoGrafo *Grafo){
    
    TipoItem x;
    x.Vertice = *V2;
    Insere(&x, &Grafo->Adj[*V1]); //chama função para inserir na lista de adjacentes
}

//Cria um Grafo Vazio
void FGVazio(TipoGrafo *Grafo){ 

    short i;
    for(i=1; i<=Grafo->NumVertices; i++)
       FLVazia(&Grafo->Adj[i]); //chama função pra inicializar todas listas de adjacentes como vazia
}

//Verifica se uma lista está vazia
int ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo){
    
    return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo); //uma lista está vazia se seu primeiro elemento é igual ao ultimo
}

//Retorna o primeiro vertice da lista de adjacentes de um dado vertice
TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo){
    
    return (Grafo->Adj[*Vertice].Primeiro->Prox);
}

//Retorna Adj apontado por Prox
void ProxAdj(TipoValorVertice *Adj, TipoApontador *Prox, char *FimListaAdj){

    *Adj=(*Prox)->Item.Vertice; //Prox começa sendo o primeiro da lista de adjacentes
    *Prox=(*Prox)->Prox;
    if(*Prox==NULL)
        *FimListaAdj = 1; //não existe mais vertices na lista de adjacentes

}

//Busca em profundidade iterativa usando pilha em que encontra o caminho entre 2 vertices
void BuscaEmProfundidade(TipoGrafo *Grafo, TipoValorVertice *Inicial, TipoValorVertice *Final){

    TipoValorVertice i, VerticeInicial, VerticeTopoPilha, Prox;
    TipoCor Cor[Grafo->NumVertices];
    TipoApontador Aux;
    TipoItem Item;
    TipoPilha Pilha;
    char FimListaAdj;
    
    //Faz Leitura Arquivo de Saida
    FILE *saida;
    saida=fopen("output.txt","w");
    if(saida==NULL)
	return;
 
    //impreme no arquivo o vertice inicial
    fprintf(saida, "%d ", *Inicial);   

    //inicialisa todos vertices de branco
    for(i=1; i<=Grafo->NumVertices; i++)
        Cor[i]=branco;

    //colore o primeiro vertice raiz de cinza
    VerticeInicial=*Inicial; 
    Cor[VerticeInicial]=cinza;

    //Poe o vertice raiz no topo da pilha
    FPVazia(&Pilha);
    Item.Vertice=VerticeInicial;
    Empilha(Item, &Pilha);
    fprintf(saida,"%d ", Item.Vertice);

    while(!PilhaVazia(Pilha)){ //Enquanto estiver vertices na pilha faça

        //Pega o vertice do topo e seu primeiro vertice adjacente branco
        VerticeTopoPilha=Pilha.Topo->Prox->Item.Vertice;
        Aux=PrimeiroListaAdj(&VerticeTopoPilha, Grafo);
        FimListaAdj=0;

        while(!FimListaAdj && Prox!=*Final){ //Enquanto existir adjacentes a aux não descobertos (brancos) faça

            ProxAdj(&Prox, &Aux,  &FimListaAdj); //Prox Adjacente
            fprintf(saida,"%d ", Prox); //imprime no arquivo
 
            if(Aux!=NULL && Cor[Prox]==branco){ //se o vertice for branco, marque v como descoberto (cinza);
                fprintf(saida, "%d", Prox);
                Cor[Prox]=cinza; 
                Item.Vertice=Prox;
                Empilha(Item, &Pilha); //empilha (***está com erro de segmentation fault aqui, na segunda iteração***)
            }
        } //Fim do enquanto fim da lista de adjacentes

        fprintf(saida,"%d" , VerticeTopoPilha);
        Cor[VerticeTopoPilha]=preto; //Marque v como terminado (preto);
        Item.Vertice=VerticeTopoPilha;
        Desempilha(&Pilha, &Item);

    } //Fim do enquanto (pilha vazia)

    fprintf(saida,"\n"); //imprime nova linha no arquivo
}
