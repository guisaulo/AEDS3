#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readline.h"
#include "grafo.h"
#include "solucaootima.h"

int main(int argc, char *argv[]){

    int numInstancias, aluno, i, j, tamanho, conjuntoIndependente, *vetor;
    char *buf;
    TipoGrafo Grafo;
    FILE *entrada, *saida;
    
    /*============Diretrizes dos Arquivos============*/

    if(argc!=3){
        printf("Comando para executacao incorreto!\n");
        return 0;
    }

    entrada=fopen(argv[1],"r");//somente leitura
    saida=fopen(argv[2],"w");//somente escrita
    if(entrada==NULL || saida==NULL){
        printf("Nao foi posivel abrir os arquivos!\n");
        return 0;
    }

    /*===Lê cada linha do arquivo e armazena no buf===*/

    buf=(char*)fgetline(entrada);
    numInstancias=atoi(strtok(buf, " "));

    //printf("NumInstancias: %d\n\n", numInstancias);

    while(numInstancias!=0){ //enquanto existir instancias para execução
        buf=(char*)fgetline(entrada);
        Grafo.NumVertices=atoi(strtok(buf, " "));
        Grafo.NumArestas=atoi(strtok(NULL, "\0"));
        FGVazio(&Grafo); //Cria o grafo/matriz

        //printf("NumAlunos: %d NumAlternativas: %d\n\n", Grafo.NumVertices, Grafo.NumArestas);

        for(i=1; i<=Grafo.NumArestas; i++){
            //printf("Alternativa %d: ",i);
            buf=(char*)fgetline(entrada);
            tamanho=0;
            vetor=(int *)malloc(Grafo.NumVertices*sizeof(int)); //vetor de inteiros para os alunos de cada linha

            for(j=0; buf[j]!='\0'; j++){ //extrai os numeros de cada linha
                if(isalnum(buf[j])){
	                aluno=buf[j]-'0';
	                vetor[tamanho]=aluno;
	                //printf("%d ", vetor[tamanho]);
                    tamanho++;
                }
            }

            vetor[tamanho]='\0';
            //printf("\n\n");

            //insere os alunos do vetor no grafo
            Insere(&Grafo, vetor, tamanho);

            //ImprimeGrafo(&Grafo);
            //printf("\n");
        }
        
        conjuntoIndependente=ForcaBruta(&Grafo);
        //printf("\n\nMaximo Conjunto Independente: %d\n\n", conjuntoIndependente);
        fprintf(saida, "%d\n", conjuntoIndependente);
        numInstancias--;
    }

    free(vetor);
    free(buf);
    fclose(entrada);
    fclose(saida);
    return 0;
}
