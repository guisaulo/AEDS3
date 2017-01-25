#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1
#define INFINITO       INT_MAX

//Estruras Gerais
typedef int TipoValorVertice;
typedef int TipoPeso;

typedef struct TipoItem {
    TipoValorVertice Vertice;
    TipoPeso Peso;
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

//Estrutura Grafo
typedef struct TipoGrafo {
    TipoLista Adj[MAXNUMVERTICES];
    TipoValorVertice NumVertices;
    int NumArestas;
} TipoGrafo;

//Estrutura Fila
typedef struct TipoFila {
    TipoApontador Frente, Tras;
} TipoFila;

//Estrutura Pilha
typedef struct TipoPilha {
    TipoApontador Fundo, Topo;
    int Tamanho;
} TipoPilha;

typedef short  TipoValorTempo;
typedef enum {
  branco, cinza, preto
} TipoCor;

//Estrutura Heap
typedef int TipoIndice;
typedef TipoItem TipoVetor[MAXNUMVERTICES + 1];

//TAD Grafo Listas Adjacentes
void FLVazia(TipoLista *Lista);
void FGVazio(TipoGrafo *Grafo);
void Insere(TipoItem *x, TipoLista *Lista);
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso, TipoGrafo *Grafo);
int ListaVazia(TipoLista Lista);
int ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo);
TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo);
void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox, short *FimListaAdj);

//TAD Busca em Largura
void FFVazia(TipoFila *Fila);
int FilaVazia(TipoFila Fila);
void Enfileira(TipoItem x, TipoFila *Fila);
void Desenfileira(TipoFila *Fila, TipoItem *Item);
void BuscaEmLargura(TipoValorVertice u, TipoValorVertice Final, TipoGrafo *Grafo, FILE *saida);

//TAD Busca em Profundidade
void FPVazia(TipoPilha *Pilha);
int PilhaVazia(TipoPilha Pilha);
void Empilha(TipoItem x, TipoPilha *Pilha);
void Desempilha(TipoPilha *Pilha, TipoItem *Item);
void BuscaEmProfundidade(TipoValorVertice u, TipoValorVertice Final, TipoGrafo *Grafo, FILE *saida);

//TAD Caminho mais curto: Dijkstra
void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos);
void Constroi(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos, TipoIndice *indice);
TipoItem RetiraMinInd(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos, TipoIndice *indice);
void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A, TipoPeso *P,  TipoValorVertice *Pos);
void Dijkstra(TipoValorVertice *Raiz, TipoValorVertice Final, TipoGrafo *Grafo, FILE *saida);
void ImprimeCaminho(TipoValorVertice Origem, TipoValorVertice v, long *Antecessor, FILE *saida);
