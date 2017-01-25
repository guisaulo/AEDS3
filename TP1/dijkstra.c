#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "busca.h"

//refaz a condição de heap
void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos){
    TipoIndice i = Esq;
    int j;
    TipoItem x;
    j = i * 2;
    x = A[i];
    while (j <= Dir){
        if (j < Dir){
            if (P[A[j].Peso] > P[A[j+1].Peso])
                j++;
        }
        if (P[x.Peso] <= P[A[j].Peso])
            goto L999;
        A[i] = A[j];
        Pos[A[j].Peso] = i;
        i = j;
        j = i * 2;
    }
    L999:  A[i] = x;
    Pos[x.Peso] = i;
}

//controi o heap
void Constroi(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos, TipoIndice *indice){

    TipoIndice n;
    n=*indice;
    TipoIndice Esq;
    Esq = n / 2 + 1;
    while (Esq > 1){
        Esq--;
        RefazInd(Esq, n, A, P, Pos);
    }
}

//obtém o vértice u com o caminho mais curto estimado até o momento
TipoItem RetiraMinInd(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos, TipoIndice *indice){

    TipoIndice n;
    n=*indice;
    TipoItem Result;
    if (n < 1){
        printf("Erro: heap vazio\n");
    return Result;
    }
    Result = A[1];
    A[1] = A[n];
    Pos[A[n].Peso] = 1;
    n--;
    *indice=n;
    RefazInd(1, n, A, P, Pos);
    return Result;
}

//implementa a operação de diminuir o valor da chave do item i:
void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A, TipoPeso *P,  TipoValorVertice *Pos){
    TipoItem x;
    if (ChaveNova > P[A[i].Peso]){
        printf("Erro: ChaveNova maior que a chave atual\n");
        return;
    }
    P[A[i].Peso] = ChaveNova;
    while (i > 1 && P[A[i / 2].Peso] > P[A[i].Peso]){
        x = A[i / 2];
        A[i / 2] = A[i];
        Pos[A[i].Peso] = i / 2;
        A[i] = x;
        Pos[x.Peso] = i;
        i /= 2;
    }
}

//calcula o caminnho mais curto usando heap
void Dijkstra(TipoValorVertice *Raiz, TipoValorVertice Final, TipoGrafo *Grafo, FILE *saida){

    TipoValorVertice Pos[MAXNUMVERTICES + 1], u, v;
    long Antecessor[MAXNUMVERTICES + 1];
    TipoPeso P[MAXNUMVERTICES + 1], Peso;
    short FimListaAdj;
    TipoApontador Aux;
    TipoVetor A;
    TipoItem temp;
    TipoIndice n;

    for(u=0; u<=Grafo->NumVertices; u++){  //Constroi o heap com todos os valores igual a INFINITO
        Antecessor[u]=-1; //para cada vertice v, antecessor[v] é o vertice u que forma o caminho mais curto
        P[u]=INFINITO; //é o caminho mais curto dos pesos, obtido de v ate a raiz
        A[u+1].Peso=u; //Heap a ser construido
        Pos[u]=u+1; //fornece a posição do vertice v dentro do heap
    }

    n=Grafo->NumVertices;
    P[1]=0; //sempre começa pela raiz
    Constroi(A, P, Pos, &n); //controi o heap

    while(n>=1){  //enquanto heap nao vazio

        temp=RetiraMinInd(A, P, Pos, &n); //retira o menor indice do heap
        u=temp.Peso;

        if(!ListaAdjVazia(&u, Grafo)){
            Aux=PrimeiroListaAdj(&u, Grafo);
            FimListaAdj=FALSE;
            
            while(!FimListaAdj){
                ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj);
                
                if(P[v] > (P[u] + Peso)){ //tecnica do relaxamento, atualizando o caminho estimado p[v] e o antecessor[v]
                    P[v] = P[u] + Peso;
                    Antecessor[v]=u;
                    DiminuiChaveInd(Pos[v], P[v], A, P, Pos);
                }
            }
        }
    }
    ImprimeCaminho(*(Raiz), Final, Antecessor, saida); //imprime o caminho mais curto utilizando o vetor antecessor
    fprintf(saida, "\n");
}

//imprime o caminho mais curto consultando o vetor antecessor
void ImprimeCaminho(TipoValorVertice Origem, TipoValorVertice v, long *Antecessor, FILE *saida){

    if(Origem==v){ //imprime o vertice inicial, no ultimo passo da recursao
        fprintf(saida, "%d ", Origem);
        return;
    }
    if(Antecessor[v]==-1)
        fprintf(saida, "%d ", v); //Caso especial nao implementado.

    else{
        ImprimeCaminho(Origem, Antecessor[v], Antecessor, saida);
        fprintf(saida, "%d ", v);
    }
}
