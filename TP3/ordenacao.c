/*==================================================================================================================
Trabalho Pr�tico 3 - Facilitando a corre��o                     
Algoritmos e Estruturas de Dados 3                               
Aluno: Guilherme Saulo Alves               
ordenacao.h: Ordena o conte�do de um arquivo utilizando arquivos auxiliares, pelo m�todo de Intercala��o Balanceada
===================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

//Fun��o para fazer a intercala��o entre as fitas.  M�todo Sele��o por substui��o
void Intercalacao(TipoHeap *Heap, FILE **ArqTemporario, char *NomeSaida, short NumDeBlocos1, short MaiorLinha){

    short QuantDeBlocos2, i, j, k;
    short FitaInicial, FitaFinal; //Armazena o n�mero da primeira fita a ser usada: 0 ou f.
    short IndiceFitas; //Armazena o �ndice da fita que ser� intercalada;
    short BlocosLidos; //Armzena quantos blocos j� foram lidos;
    short IndiceFitaFinal; //Armazena o �ndice da �ltima contendo todos o arquivo ordenado.
    char NomeArqTem[10];

    for(i = 0; i < Fitas; i++){  //Volta o cursos para o in�cio dos arquivos tempor�rios.
        rewind(ArqTemporario[i]);  //retorna a posicao corrente do arquivo para o inicio.
    }

    FitaInicial = 0;
    FitaFinal = Fitas;
    IndiceFitas = Fitas;
    BlocosLidos = 0;
    QuantDeBlocos2 = 0;

    while(NumDeBlocos1 != 1){
        
        while(NumDeBlocos1 != 0){
            
            k = 0; //Verifica quantas fitas est�o sendo utilizadas
            for(j = FitaInicial; j < FitaFinal; j++){  //Armazena a linha de cada tempor�rio no heap

                fgets(Heap[k+1].Linha, MaiorLinha, ArqTemporario[j]);
                if((Heap[k+1].Linha[0] != '\n') && (!feof(ArqTemporario[j]))){
                    Heap[k+1].NumDaFita = j;
                    k++;
                }
            }

            NumLinhasHeap = k;
            NumDeBlocos1 -= k;

            while(BlocosLidos < k){
                
                ConstroiHeap(Heap);
                NumDeLinhas = Fitas + 2; //Garanti a entrada no if no RetiraMinHeap
                RetiraMinHeap(Heap, ArqTemporario[Heap[1].NumDaFita], MaiorLinha);
                fputs(Heap[0].Linha, ArqTemporario[IndiceFitas]);

                if((Heap[1].Linha[0] == '\n') || (feof(ArqTemporario[IndiceFitas]))){
                    NumDeLinhas = Fitas;
                    RetiraMinHeap(Heap, ArqTemporario[Heap[0].NumDaFita], MaiorLinha);
                    BlocosLidos++;
                }
            }
            
            fprintf(ArqTemporario[IndiceFitas], "\n");
            IndiceFitaFinal = IndiceFitas;
            IndiceFitas++;

            if(FitaFinal == Fitas){  //Volta a fita inicial caso terminem as fitas f
                
                if(IndiceFitas == 2*Fitas) 
                    IndiceFitas = Fitas;
            }
            
            else{
                if(IndiceFitas == Fitas) 
                    IndiceFitas = 0;
            }

            QuantDeBlocos2++;  //Armazena a quantidade de blocos criados.
            BlocosLidos = 0;
        }

        for(i = FitaInicial; i < FitaFinal; i++){  //Limpa os arquivos tempor�rios de FitaInicial a FitaFinal
            sprintf(NomeArqTem, "Fita%d.txt", i);
            ArqTemporario[i] = fopen(NomeArqTem, "w+");
        }

        if(FitaFinal == Fitas){  //Inverte a ordem das fitas
            FitaInicial = Fitas;
            FitaFinal = 2 * Fitas;
            IndiceFitas = 0;
        }

        else{
            FitaInicial = 0;
            FitaFinal = Fitas;
            IndiceFitas = Fitas;
        }

        for(i = FitaInicial; i < FitaFinal; i++){  //Volta o cursor para o in�cio dos arquivos tempor�rios.
            rewind(ArqTemporario[i]);  //retorna a posicao corrente do arquivo para o inicio.
        }
	
        NumDeBlocos1 = QuantDeBlocos2;
        QuantDeBlocos2 = 0;
    }

    FILE *ArquivoSaida = fopen(NomeSaida, "w");
    if(ArquivoSaida == NULL){
        printf("Error: Arquivo %s n�o foi gerado!\n", NomeSaida);
        exit(1);
    }
    
    char LinhaSaida[MaiorLinha];

    fgets(LinhaSaida, MaiorLinha, ArqTemporario[IndiceFitaFinal]);
    fputs(LinhaSaida, ArquivoSaida);
    
    while(LinhaSaida[0] != '\n'){
    
        fgets(LinhaSaida, MaiorLinha, ArqTemporario[IndiceFitaFinal]);
            if(LinhaSaida[0] == '\n') 
                break;
        fputs(LinhaSaida, ArquivoSaida);
    }
    
    fclose(ArquivoSaida);
}

//Fun��o principal para ordenar o arquivo de entrada pelo m�todo de Intercala��o Balanceada por Substitui��o
void OrdenacaoExterna(FILE *ArqEntrada){

    short i, NumDeBlocos1, MaiorLinha = 0, TotalFitas;
    char Linha[1], *NomeSaida;
    
    NomeSaida=(char*)malloc(strlen("lista_ordenada.txt")*sizeof(char)); //nome arquivo de entrada da ordeca�ao
    strcpy(NomeSaida, "lista_ordenada.txt"); 
    
    NumDeLinhas = 0;
    Fitas = NUMFITAS; //quantidade de fitas iniciais, total de fitas = 2*fitas

    for(i = 0; !feof(ArqEntrada); i++){  //Verifica quantas linhas tem o arquivo e qual a quantidade de bytes da maior linha.       
        fscanf(ArqEntrada, "%c", &Linha[0]);
        
        if(Linha[0] == '\n'){
            if(i > MaiorLinha) 
                MaiorLinha = i;
            NumDeLinhas++; //Vai ser usada para garantir parada na retirada do m�nimo no heap
            i = -1;
        }
    }

    MaiorLinha += 3; //Para garantir as quebras de linhas
    rewind(ArqEntrada);  //retorna a posicao corrente do arquivo para o inicio.
    
    TotalFitas = 2 * Fitas;
    TipoHeap *Heap;  //trocar o nome para heap
    Heap = (TipoHeap *)malloc((Fitas+1)*sizeof(TipoHeap));
    
    Heap[0].Marcacao = 0;  //marca a primeira posicao do heap
    for(i = 1; i <= Fitas; i++){  //cria um heap de tamanho f, em que os elementos ser�o as linhas do arquivo de entrada.
        fgets(Heap[i].Linha, MaiorLinha, ArqEntrada);
        Heap[i].Marcacao = 0;
    }

    NumLinhasHeap = Fitas; //N�mero de linhas que a mem�ria principal ir� armazenar para auxiliar no heap
    
    ConstroiHeap(Heap);

    char NomeArqTem[10]; //Armazena o nome do arquivo temporario

    FILE *ArqTemporario[TotalFitas];

    for(i = 0; i < TotalFitas; i++){  //Cria os arquivos tempor�rios.
        sprintf(NomeArqTem, "Fita%d.txt", i);
        ArqTemporario[i] = fopen(NomeArqTem, "w+");
    }
    
    NumDeBlocos1 = CriaFitas(Heap, ArqEntrada, ArqTemporario, MaiorLinha);
    Intercalacao(Heap, ArqTemporario, NomeSaida, NumDeBlocos1, MaiorLinha);
    
    free(NomeSaida);
    free(Heap);
    RemoveArqTemporarios(ArqTemporario, TotalFitas);
}
