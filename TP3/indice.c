/*==================================================================================================================
Trabalho Prático 3 - Facilitando a correção                     
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
indice.c: Produz o  ́ındice invertido a partir do arquivo ordenado de lista                            
====================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "biblioteca.h"

//Produz o ́ındice invertido dos termos nas respostas dos alunos
void IndiceInvertido(FILE *lista_ordenada, char *ArgvArqSaida){
    
    int aluno, alunoAnterior=-1;
    char *termo, *termoAnterior, *CharAluno;
    
    FILE *ArqSaida = fopen(ArgvArqSaida, "w");

    termo=(char*)malloc(TAMMAXTERMO*sizeof(char));
    termoAnterior=(char*)malloc(TAMMAXALUNO*sizeof(char));
    CharAluno=(char*)malloc(TAMMAXALUNO*sizeof(char));

	while(fscanf(lista_ordenada, "%s %s", termo, CharAluno) != EOF){ //enquanto existir tuplas no arquivo lista ordenada
    	aluno=atoi(CharAluno); //pega o valor do aluno como um numero inteiro

    	if((strcmp(termo, termoAnterior) != 0) || (aluno != alunoAnterior)){  //se a tupla atual é diferente da anterior	
    		if(strcmp(termo, termoAnterior) != 0){  //se a tupla nao pertence ao ao vocabulario do ındice invertido
    			if(alunoAnterior == -1)
    				fprintf(ArqSaida, "%s", termo);  //escreve o termo no indice invertido 
    			else
    				fprintf(ArqSaida, "\n%s", termo);
    		}  //escreve o termo no indice invertido			
       		fprintf(ArqSaida, " %d", aluno);  //escreve o aluno no indice invertido
     	}

    	alunoAnterior=aluno;
    	strcpy(termoAnterior, termo);
	}

    if(ArqSaida == NULL){
        printf("Error: Arquivo %s não foi gerado!\n", ArgvArqSaida);
        exit(1);
    }
    else

    	printf("Indice Invertido gerado com sucesso!\n");
	
	fclose(ArqSaida);
	free(termo);
	free(termoAnterior);
	free(CharAluno);

}