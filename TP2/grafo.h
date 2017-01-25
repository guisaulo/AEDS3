#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#define MAXNUMVERTICES 100
#define MAXNUMARESTAS 4500

/*================Estrutura do TAD Grafo de matriz de adjacencia==============*/

typedef int TipoValorVertice;
typedef struct TipoGrafo {
    TipoValorVertice Mat[MAXNUMVERTICES+1][MAXNUMVERTICES+1];
    int NumVertices;
    int NumArestas;
} TipoGrafo ;
typedef int TipoApontador;

/*================Funções do TAD Grafo de matriz de adjacencia===============*/

//Faz um grafo de matriz de adjacencia vazio
void FGVazio(TipoGrafo *Grafo);
//Insere os alunos do vetor no grafo matriz
void Insere(TipoGrafo *Grafo, int *vetor, int tamanho);
//Insere uma aresta entre dois vertices
void InsereAresta(int V1, int V2, TipoGrafo *Grafo);
//Verifica se existe aresta entre dois vertices
int ExisteAresta (TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo);
//Imprime o grafo de Matriz de Adjacencia
void ImprimeGrafo(TipoGrafo *Grafo);

#endif // GRAFO_H_INCLUDED
