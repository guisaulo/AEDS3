/*==================================================================================================================
Trabalho Prático 3 - Facilitando a correção                     
Algoritmos e Estruturas de Dados 3                               
Aluno: Guilherme Saulo Alves               
heap.c: Define as estruturas e o cabeçalho das funções de um Heap mínimo.
====================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "biblioteca.h"

//Constrói um Heap com os termos das linhas do arquivo
void ConstroiHeap(TipoHeap *A){
     
     Indice Esq;
     Esq = (NumLinhasHeap / 2) + 1;  //Posição a partir de onde o Heap já é formado.

     while(Esq > 1){
         Esq--;
         RefazHeap(Esq, NumLinhasHeap, A); //Chamada de função para refazer o Heap
     }
}

//Função para refazer a condição de Heap
void RefazHeap(Indice Esq, Indice Dir, TipoHeap *A){

    short j;      
    Indice i = Esq; //Posição que será tomada como base para verificar se os i*2 e (i*2)+1 são menores que ele.
    TipoHeap x;

    j = i * 2;
    x = A[i];  //Elemento a ser comparado

    while(j <= Dir){

        if(j < Dir){

            if((A[j].Marcacao != 0) && (A[j+1].Marcacao != 0)) 
                break;

            if((strcmp(A[j].Linha, A[j+1].Linha) > 0) && (A[j+1].Marcacao == 0))
                j++;

            else if((strcmp(A[j].Linha, A[j+1].Linha) < 0) && (A[j].Marcacao != 0))
                    j++;
        }

        if((strcmp(x.Linha, A[j].Linha) <= 0) && (x.Marcacao == 0))
            break;
        
        A[i] = A[j];
        i = j;
        j = i * 2;
    }

    A[i] = x; 
}

//Função para retirar o menor elemento do Heap e substituir pelo proximo elemento do arquivo.
void RetiraMinHeap(TipoHeap *A, FILE *ArquivoEntrada, short MaiorLinha){

    A[0] = A[1];  //Armazena o primeiro arquivo na Posição 0

    if((NumDeLinhas > Fitas+1) && (!feof(ArquivoEntrada))){
        fgets(A[1].Linha, MaiorLinha, ArquivoEntrada);  //Copia o próximo item para o Heap
        NumDeLinhas--;
    }
    
    else{
        A[1] = A[NumLinhasHeap]; //Copia o último elemento para a primeira posiçao.
        NumLinhasHeap--;
    }
}
