/*==================================================================================================================
Trabalho Pr�tico 3 - Facilitando a corre��o                     
Algoritmos e Estruturas de Dados 3                               
Aluno: Guilherme Saulo Alves               
heap.c: Define as estruturas e o cabe�alho das fun��es de um Heap m�nimo.
====================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "biblioteca.h"

//Constr�i um Heap com os termos das linhas do arquivo
void ConstroiHeap(TipoHeap *A){
     
     Indice Esq;
     Esq = (NumLinhasHeap / 2) + 1;  //Posi��o a partir de onde o Heap j� � formado.

     while(Esq > 1){
         Esq--;
         RefazHeap(Esq, NumLinhasHeap, A); //Chamada de fun��o para refazer o Heap
     }
}

//Fun��o para refazer a condi��o de Heap
void RefazHeap(Indice Esq, Indice Dir, TipoHeap *A){

    short j;      
    Indice i = Esq; //Posi��o que ser� tomada como base para verificar se os i*2 e (i*2)+1 s�o menores que ele.
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

//Fun��o para retirar o menor elemento do Heap e substituir pelo proximo elemento do arquivo.
void RetiraMinHeap(TipoHeap *A, FILE *ArquivoEntrada, short MaiorLinha){

    A[0] = A[1];  //Armazena o primeiro arquivo na Posi��o 0

    if((NumDeLinhas > Fitas+1) && (!feof(ArquivoEntrada))){
        fgets(A[1].Linha, MaiorLinha, ArquivoEntrada);  //Copia o pr�ximo item para o Heap
        NumDeLinhas--;
    }
    
    else{
        A[1] = A[NumLinhasHeap]; //Copia o �ltimo elemento para a primeira posi�ao.
        NumLinhasHeap--;
    }
}
