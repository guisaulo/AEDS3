/*==================================================================================================================
Trabalho Prático 3 - Facilitando a correção                     
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
mainc.c: Arquivo principal do programa, contém a chamada de execução da função principal                              
====================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

int main(int argc, char *argv[]){

    int tamMemoria, numTermos;
    short inicioEntrada, fimEntrada, ArgvArqSaida, i;
    
    /*================================ Verifica argumentos de execução ========================*/
    if(argc < 6){ 
        printf("Error: Faltando argumentos de execução!\n");
        return 0;
    }

    for(i=0; i < argc; i++){   
        if(strcmp(argv[i], "-o") == 0){
            ArgvArqSaida=i+1; //indica o argumento do arquivo de saida
            if(i==1)
                fimEntrada = argc-1;
            else
                fimEntrada = i-1;
        }
        if(strcmp(argv[i], "-m") == 0){
            tamMemoria = atoi(argv[i+1]);  //tamanho da memoria principal disponivel 
            inicioEntrada = i+2;
        }
        printf("%s ", argv[i]);    
    }

    printf("\n");
    printf("tamMemoria: %d\ninicioEntrada: %d\nfimEntrada: %d\nArgvArqSaida: %d\n", tamMemoria, inicioEntrada, fimEntrada, ArgvArqSaida);

    /*================================ Cria Arquivo de Lista de Tuplas ========================*/

    numTermos = CriaLista(inicioEntrada, fimEntrada, argv);  //cria um arquivo com a lista de tuplas e retorna a quantidade de termos
    
    printf("numTermos: %d\n", numTermos);

    /*=================================== Ordena Lista de Tuplas ==============================*/
    
    FILE *ArquivoEntrada = fopen("lista.txt", "r");
    if(ArquivoEntrada == NULL) {
        printf("Error: Arquivo lista.txt não foi gerado!\n");
        return 0;
    }
    
    OrdenacaoExterna(ArquivoEntrada);

    fclose(ArquivoEntrada);

    /*=================================== Indice Invertido ==================================*/

    FILE *lista_ordenada = fopen("lista_ordenada.txt","r");
    if(lista_ordenada == NULL) {
        printf("Error: Arquivo lista.txt não foi gerado!\n");
        return 0;
    }

    IndiceInvertido(lista_ordenada, argv[ArgvArqSaida]);
    
    fclose(lista_ordenada);

    return 0;
 }
