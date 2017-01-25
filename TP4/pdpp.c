/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
pdpp.c: Implementação em que mais de um par de palavras possa ser comparado em paralelo.                  
====================================================================================================================*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> //INT_MAX
#include <ctype.h> //isalpha
#include "lista.h"
#include "pdpp.h"
#include "pds.h"

//OBS: O MESMO CODIGO DO ALGORIMO SEQUENCIAL, PORÉM COMO NAO DEU TEMPO PRA FAZER, DEIXEI AS OPERACOES PARALELAS COMO COMENTARIO

//Lê as palavras dos arquivos caracter por caracter e passa-as a função levenshtein
void PPPalavras(char *NomArqRespostas, char *NomArqDicionario, char *NomArqSaida, int numThreads){
   
    short i , pos = 0;
    short lock1 = FALSE, lock2 = FALSE;
    short FimDaLinha = FALSE; 
    int NumRespostas = 0; 
    float Distancia, MenorDistancia, DistanciaTotal;  
	char ch1, ch2; 
    char *strErrada, *strCerta, *Aux; 
    TipoLista lista; 
    TipoResposta Resposta; 
    
    //pthread_t threads[numThreads]; //cria numThreads threads

	FILE *ArqRespostas = fopen (NomArqRespostas, "r"); 
    if(ArqRespostas == NULL){
        printf("Erro, nao foi possivel abrir o arquivo %s!\n", NomArqRespostas);
        return;
    }

    FILE *ArqSaida = fopen (NomArqSaida, "w");  
    if(ArqSaida == NULL){
        printf("Erro, nao foi possivel abrir o arquivo %s!\n", NomArqSaida);
        return;
    }    

    FazListaVazia(&lista); 
    strErrada = (char *)malloc(sizeof(char));  
    
    while((ch1=fgetc(ArqRespostas)) != EOF){ 

        if(ch1 == '\n'){ 
            strErrada[strlen(strErrada)+1] = '\0';
            FimDaLinha = TRUE; 
            lock1 = TRUE; 
            pos = 0; 
        }
        
        if(ch1 == ' '){ 
            strErrada[strlen(strErrada)+1]= '\0';
            lock1 = TRUE; 
            pos = 0;
        }
       
        if(lock1){ 
            
            FILE *ArqDicionario = fopen (NomArqDicionario, "r");  
            if(ArqDicionario == NULL){
                printf("Erro, nao foi possivel abrir o arquivo %s!\n", NomArqDicionario);
                return;
            }

            MenorDistancia = INT_MAX; 
            strCerta = (char *)malloc(sizeof(char)); 
            
            while((ch2=fgetc(ArqDicionario)) != EOF){  

                if(ch2 == '\n'){ 
                    strCerta[strlen(strCerta)+1] = '\0';
                    lock2 = TRUE; 
                    pos = 0;
                }
                
                if(lock1 && lock2){ 
                    //pthread_create(&threads[i], NULL, PPPalavras, (void *));  //aqui ocorreria a distribuição de threads
                    Distancia = Levenshtein(strCerta, strErrada); 
                    if(Distancia < MenorDistancia){ 
                        MenorDistancia = Distancia;
                        Aux = (char *)malloc(strlen(strCerta)*sizeof(char));
                        strcpy(Aux, strCerta); 
                    }
                    strCerta = (char *)malloc(sizeof(char)); 
                    lock2 = FALSE;
                    //thread_join(thread[i], NULL); //espera thread
                    //pthread_exit(NULL); //fim thread
                }

                else if(isalpha(ch2)){
                    strCerta[pos]=ch2;
                    pos++;
                }  
            }   
            
            if(!FimDaLinha){  
                DistanciaTotal += MenorDistancia;
                Resposta.Distancia = MenorDistancia;
                Resposta.Palavra = (char *)malloc(strlen(Aux)*sizeof(char));
                strcpy(Resposta.Palavra, Aux);
                InsereResposta(Resposta, &lista);
                NumRespostas++;    
            }
            
            else if(FimDaLinha){ 
                DistanciaTotal += MenorDistancia;
                Resposta.Distancia = MenorDistancia;
                Resposta.Palavra = (char *)malloc(strlen(Aux)*sizeof(char));
                strcpy(Resposta.Palavra, Aux);
                InsereResposta(Resposta, &lista); 
                NumRespostas++;
                fprintf(ArqSaida, "%.1f: ", DistanciaTotal);
                ImprimeRespostaAluno(lista, ArqSaida);
                fprintf(ArqSaida, "\n");
                
                for(i = 1; i <= NumRespostas; i++)  
                    RetiraResposta(lista.Primeiro, &lista);
                
                NumRespostas = 0;
                DistanciaTotal = 0;
            }

            lock1 = FALSE;
            free(strCerta);
            fclose(ArqDicionario);
            strErrada = (char *)malloc(sizeof(char));
        }

        else if(isalpha(ch1)){ 
            strErrada[pos] = ch1; 
            pos++;
        }
    
        FimDaLinha = FALSE;
    }

    free(Aux);
    free(strErrada);
    fclose(ArqSaida);
    fclose(ArqRespostas);   	
}
