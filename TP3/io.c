/*==================================================================================================================
Trabalho Prático 3 - Facilitando a correção                     
Algoritmos e Estruturas de Dados 3                               
Aluno: Guilherme Saulo Alves               
io.c: Realiza a comunicação do programa com o ambiente, lendo o arquivo de entrada, armazenando as informações lidas na memória e escrevendo nos arquivos de saída.                            
====================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "biblioteca.h"

//Lê todos os arquivos de entradas e escreve as tuplas no arquivo lista retornando a quantidade de termos
int CriaLista(short inicio, short fim, char *argv[]){

    int aluno, numTermos;
    short i;
    char *termo;
    termo=(char*)malloc(TAMMAXTERMO*sizeof(char));  //tamanho maximo do termo + aluno

    FILE *lista = fopen("lista.txt", "w");  //cria arquivo para escrever a lista de tuplas
    if(lista == NULL) {
        printf("Error: Arquivo lista.txt não foi gerado!\n");
        exit(1);
    }

    numTermos=0;

    for(i=inicio; i<=fim; i++){  //lê todos os arquivos de entradas e escreve as tuplas no arquivo lista.txt        

        FILE *entradas = fopen(argv[i],"r");  //somente leitura
        if(entradas==NULL){
            printf("Nao foi posivel abrir arquivo de entrada %s!\n", argv[i]);
            exit(1);
        }
        
        while(fscanf(entradas, "%s", termo) != EOF){     
            
            if(isdigit(termo[0])!=0)  //indica que é um aluno
                aluno=atoi(termo);

            if(isdigit(termo[0])==0){ //indica que é um termo
                fprintf(lista, "%s %d\n", termo, aluno);
                numTermos++;
            }
        }

        printf("Arquivo %s lido!\n", argv[i]);
        fclose(entradas);
    }

    if(lista == NULL) {
        printf("Error: Arquivo lista.txt não foi gerado!\n");
        exit(1);
    }  
    else
        printf("Arquivo lista.txt foi gerado!\n");
    
    free(termo);
    fclose(lista); //fecha o arquivo de lista para ser lido no main
    
    return numTermos;
}

//Faz a primeira passada no arquivo, substitui o menor elemento do heap pelo proximo item do arquivo e salva o item retirado nas "fitas"
short CriaFitas(TipoHeap *Heap, FILE *ArqEntrada, FILE **ArqTemporario, short MaiorLinha){

    short NumDeBlocos1, i, j, k;

    NumDeBlocos1 = 0;

    k = 0; //Número da fita.

    while(NumDeLinhas > Fitas + 1){

        while((Heap[1].Marcacao == 0) && (NumDeLinhas > Fitas+1)){

            RetiraMinHeap(Heap, ArqEntrada, MaiorLinha);
            fputs(Heap[0].Linha, ArqTemporario[k]);

            if(strcmp(Heap[1].Linha, Heap[0].Linha) < 0) 
                Heap[1].Marcacao = 1;
            
            ConstroiHeap(Heap);
        }
        
        if(NumDeLinhas != Fitas+1) 
            fprintf(ArqTemporario[k], "\n");
        k++;
        NumDeBlocos1++;

        if(k == Fitas) 
            k = 0;

        if(NumDeLinhas == Fitas+1){
            
            for(i = 0; i < Fitas; i++){
            
                if(Heap[1].Marcacao == 0){
            
                    if((k-1) < 0) 
                        k = Fitas;
                    
                    fputs(Heap[1].Linha,ArqTemporario[k-1]);
                    RetiraMinHeap(Heap, ArqEntrada, MaiorLinha);
                    ConstroiHeap(Heap);
                }
                
                else{
                    for(j = 0; j <= Fitas; j++){  //Zera todos as "marcas" do heap
                        Heap[j].Marcacao = 0;
                    }
                    i--;
                    fprintf(ArqTemporario[k-1], "\n");
                    k++;
                    NumDeBlocos1++;
                    if((k-1) == Fitas) 
                        k = 1;
                    ConstroiHeap(Heap);
                }
            }
            fprintf(ArqTemporario[k-1], "\n");
            break;
        }

        for(i = 0; i <= Fitas; i++){  //Zera todos as "marcas" do Heap
            Heap[i].Marcacao = 0;
        }
        ConstroiHeap(Heap);
     }

     return NumDeBlocos1;
 }

//Fecha e remove os arquivos temporários
void RemoveArqTemporarios(FILE** ArqTemporario, short TotalFitas){
    
    short i;
    //retirar comentario para remover arquivos temporarios
    //char NomeArqTem[10];

    for(i = 0; i < TotalFitas; i++){  //Fecha e depois exclui os arquivos temporarios.
        //sprintf(NomeArqTem, "Fita%d.txt", i);
        fclose(ArqTemporario[i]);
        //remove(NomeArqTem);
    }
}
