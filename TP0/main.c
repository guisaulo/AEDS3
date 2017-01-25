#include <stdio.h>
#include <stdlib.h>
#include "busca.h"


int main (int argc, char *argv[]){

    int i, V1, V2, VInicial, VFinal, NumInstancias, NumConsultas;
    TipoGrafo Grafo;
    
   //Faz Leitura Arquivo de Entrada
    FILE *entrada;
    entrada=fopen("input.txt","r");
    if(entrada==NULL)
	return 0;

    //Lê o numero de instancias no arquivo
    fscanf(entrada, "%d", &NumInstancias);
   
    //Enquanto o arquivo não chegou o fim do arquivo
    while(!feof(entrada)){

        for(i=1; i<=NumInstancias; i++){ 
            //lê o número de vertices e de arestas no arquivo
            fscanf(entrada, "%d", &Grafo.NumVertices);
            fscanf(entrada, "%d", &Grafo.NumArestas);
            FGVazio(&Grafo);

            for(i=1; i<=Grafo.NumArestas; i++){
                //lê os vértices                
		fscanf(entrada, "%d %d", &V1, &V2);
                InsereAresta(&V1, &V2, &Grafo);
            }
	    
	    //lê o numero de consultas de busca
            fscanf(entrada, "%d", &NumConsultas);
            for(i=1; i<=NumConsultas; i++){
		//lê o vertice inicial e final para busca
                fscanf(entrada, "%d %d", &VInicial, &VFinal);
                BuscaEmProfundidade(&Grafo, &VInicial, &VFinal);
            }
        }
    }
 
    fclose(entrada);
    return 0;
}
