#include<stdio.h>
#include<stdlib.h>
#include "busca.h"

int main (int argc, char *argv[]){

    int i, NumInstancias, NumConsultas, peso, teste;
    TipoValorVertice V1, V2, VInicial, VFinal;
    TipoGrafo Grafo;

   //Faz Leitura dos Arquivos
    FILE *entrada, *saida;
    entrada=fopen("input.txt","r");//somente leitura
    saida=fopen("output.txt","w");//somente escrita
    if(entrada==NULL)
        return 0;

    //Lê o numero de instancias no arquivo enquanto o arquivo não chegou o fim do arquivo
    while(fscanf(entrada, "%d", &NumInstancias)!=EOF){

        for(i=1; i<=NumInstancias; i++){ //lê o número de vertices e de arestas no arquivo
            fscanf(entrada, "%d", &Grafo.NumVertices);
            fscanf(entrada, "%d", &Grafo.NumArestas);
            FGVazio(&Grafo); //cria o grafo

            for(i=1; i<=Grafo.NumArestas; i++){ //lê os vértices e pesos e insere no grafo
                fscanf(entrada, "%d %d  %d\n", &V1, &V2, &peso);
                InsereAresta(&V1, &V2, &peso, &Grafo);
            }

            fscanf(entrada, "%d", &NumConsultas); //lê o numero de consultas de busca

            for(i=1; i<=NumConsultas; i++){ //lê o vertice inicial e final para busca
                fscanf(entrada, "%d %d %d", &teste, &VInicial, &VFinal);
                
                switch(teste){
                    case 1:
                        BuscaEmLargura(VInicial, VFinal, &Grafo, saida);
                        fprintf(saida, "\n");
                        break;
                    case 2:
                        BuscaEmProfundidade(VInicial, VFinal, &Grafo, saida);
                        fprintf(saida, "\n");
                        break;
                    break;
                    case 3:
                        Dijkstra(&VInicial, VFinal, &Grafo, saida);
                        fprintf(saida, "\n");
                        break;
                    default:
                        printf("invalid number\n");
                        break;
                }
            }
        }
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}
