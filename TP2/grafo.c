#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "solucaootima.h"

//Faz um grafo de matriz de adjacencia vazio
void FGVazio(TipoGrafo *Grafo){
    
    short i, j;
    
    for(i=0; i<=Grafo->NumVertices; i++){
        for(j=0; j<=Grafo->NumVertices; j++)
            Grafo->Mat[i][j]=0;
    }
}

//Insere os alunos do vetor no grafo matriz
void Insere(TipoGrafo *Grafo, int *vetor, int tamanho){

    int r, i, j, *num;

    //Inicio do algoritmo para gerar permutacoes
    r=2;
    num=(int *)malloc(r+1*sizeof(int)) ;
    num[r]=0;

    while (num[r]==0){
        for(i=0; i<tamanho; i++) {
        //Mostra a permutacao na tela se e somente se `num' nao contem algarismos repetidos
            if(EhSemRepeticao(num, r)){
                for(j=0; j <r-1; j++) {
                    InsereAresta(vetor[num[j]], vetor[num[j+1]], Grafo) ;
                }
            }
            /* incrementa o algarismo menos significativo. */
            num[0]++;
        }
        /* distribui os vai-uns. */
        for(i=0; i < r; i++) {
            if(num[i] == tamanho) {
                num[i] = 0;
                num[i+1]++ ;
            }
        }
    }
    free(num) ;
}

//Insere uma aresta entre dois vertices
void InsereAresta(int V1, int V2, TipoGrafo *Grafo){
    
    Grafo->Mat[V1][V2]++;
}

//Verifica se existe aresta entre dois vertices
int ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo){
    
    return (Grafo->Mat[Vertice1][Vertice2] > 0);
}

//Imprime o grafo de Matriz de Adjacencia
void ImprimeGrafo(TipoGrafo *Grafo){

    short i, j;
    printf("   ");
    
    for(i=1; i<=Grafo->NumVertices; i++)
        printf("%3d", i);
    printf("\n");
    
    for(i=1; i<=Grafo->NumVertices; i++){
        printf("%3d", i);
        for(j=1;j<=Grafo->NumVertices; j++)
            printf("%3d", Grafo->Mat[i][j]);
        printf("\n");
    }
}


