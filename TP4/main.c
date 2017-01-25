/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
mainc.c: Arquivo principal do programa, contém a chamada de execução da função principal                              
====================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pds.h"
#include "pdpp.h"
#include "pdcpi.h"

int main(int argc, char *argv[]){

	short i, algoritmo, numThreads;
    char *respostas, *dicionario, *NomArqSaida;
      
    /*================================ Verifica argumentos de execução ========================*/
    
 	if(argc < 11){ 
        printf("Error: Faltando argumentos de execução!\n");
        return 0;
    }

    for(i=0; i < argc; i++){     
        if(strcmp(argv[i], "-a") == 0){
        	algoritmo = atoi(argv[i+1]);
        }
        if(strcmp(argv[i], "-t") == 0){
        	numThreads = atoi(argv[i+1]);
        }
        if(strcmp(argv[i], "-r") == 0){
        	respostas = (char*)malloc(strlen(argv[i+1])*sizeof(char));
        	strcpy(respostas, argv[i+1]);
        }
        if(strcmp(argv[i], "-d") == 0){
        	dicionario = (char*)malloc(strlen(argv[i+1])*sizeof(char)); 
        	strcpy(dicionario, argv[i+1]);
        }
        if(strcmp(argv[i], "-o") == 0){
        	NomArqSaida = (char*)malloc(strlen(argv[i+1])*sizeof(char));
        	strcpy(NomArqSaida, argv[i+1]);
        }
        //printf("%s ", argv[i]);    
    }

    //printf("\n");

    /*================================ Chama o algoritmo correspondente ========================*/

    switch(algoritmo){
    	case 1:
    		//Programação Dinâmica Sequencial
            PPSequencial(respostas, dicionario, NomArqSaida);
    	break;

    	case 2:
    		//Programação Dinâmica com Paralelização de Palavras
            PPPalavras(respostas, dicionario, NomArqSaida, numThreads);
    	break;

    	case 3:
    		//Programação Dinâmica com Computação Paralelas Internas
            PPCompInternas(respostas, dicionario, NomArqSaida, numThreads);
            break;

    	default:
    		printf("Algoritmo %d invalido!\n", algoritmo);
    	break;
    }

    return 0;
}
