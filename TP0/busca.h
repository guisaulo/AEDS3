#define MAXNUMVERTICES  100

//Estruras Gerais
typedef int TipoValorVertice;
typedef struct TipoItem {
    TipoValorVertice Vertice;
} TipoItem;

//Estrutura Lista
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct TipoLista {
    TipoApontador Primeiro, Ultimo;
} TipoLista;

typedef struct TipoPilha {
    TipoApontador Fundo, Topo;
    int Tamanho;
} TipoPilha;

//Estrutura Grafo
typedef struct TipoGrafo {
    TipoLista Adj[MAXNUMVERTICES];
    TipoValorVertice NumVertices;
    int NumArestas;
} TipoGrafo;

typedef short  TipoValorTempo;
typedef enum {
  branco, cinza, preto
} TipoCor;

void FLVazia(TipoLista *Lista);

int ListaVazia(TipoLista Lista);

void Insere(TipoItem *x, TipoLista *Lista);

void FPVazia(TipoPilha *Pilha);

int PilhaVazia(TipoPilha Pilha);

void Empilha(TipoItem x, TipoPilha *Pilha);

void Desempilha(TipoPilha *Pilha, TipoItem *Item);

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoGrafo *Grafo);

void FGVazio(TipoGrafo *Grafo);

int ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo);

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo);

void ProxAdj(TipoValorVertice *Adj, TipoApontador *Prox, char *FimListaAdj);

void VisitaBfs(TipoGrafo *Grafo, TipoCor *Cor);

void BuscaEmProfundidade(TipoGrafo *Grafo, TipoValorVertice *Inicial, TipoValorVertice *Final);
