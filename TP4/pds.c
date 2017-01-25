/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
pds.c: Implementação sequencial do algoritmo por meio do uso de técnicas de programação dinamica                    
====================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> //INT_MAX
#include <ctype.h> //isalpha
#include "lista.h"
#include "pds.h"

//Lê as palavras dos arquivos caracter por caracter e passa-as a função levenshtein
void PPSequencial(char *NomArqRespostas, char *NomArqDicionario, char *NomArqSaida){

    short i , pos = 0; //indice das posisoes das strings
    short lock1 = FALSE, lock2 = FALSE; //chaves para liberar as strings prontas ao algoritmo levenshtein
    short FimDaLinha = FALSE; //chave q indica o fim de cada linha do arquivo de respostas
    int NumRespostas = 0; //guarda o numero de respostas de cada aluno
    float Distancia, MenorDistancia, DistanciaTotal;  //variaveis para gravar as distancias do algoritmo levenshtein
	char ch1, ch2; //variaveis usadas para ler cada caracter dos arquivos respostas e dicionario 
    char *strErrada, *strCerta, *Aux; //contem as strings para as palavras erradas, certas e auxiliares
    TipoLista lista; //lista para os itens de cada aluno, usada uma vez para imprimir corretamente
    TipoResposta Resposta; //contem uma reposta e a distancia
    
	FILE *ArqRespostas = fopen (NomArqRespostas, "r"); //Abre arquivo de texto com as respostas
    if(ArqRespostas == NULL){
        printf("Erro, nao foi possivel abrir o arquivo %s!\n", NomArqRespostas);
        return;
    }

    FILE *ArqSaida = fopen (NomArqSaida, "w");  //Abre arquivo de texto para escrever saida
    if(ArqSaida == NULL){
        printf("Erro, nao foi possivel abrir o arquivo %s!\n", NomArqSaida);
        return;
    }    

    FazListaVazia(&lista); //cria lista vazia
    strErrada = (char *)malloc(sizeof(char));  //aloca memoria para a string palavra errada
    
    while((ch1=fgetc(ArqRespostas)) != EOF){ //lê caracter por caracter e forma a string de resposta

        if(ch1 == '\n'){ //indica que as respostas de um aluno acabaram
            strErrada[strlen(strErrada)+1] = '\0';
            FimDaLinha = TRUE; //abre chave para inserir as palavras do aluno em uma lista
            lock1 = TRUE; //abre chave para liberar string à função levenshtein
            pos = 0; //volta ao estado inicial
        }
        
        if(ch1 == ' '){ //indica que uma palavra chegou ao fim
            strErrada[strlen(strErrada)+1]= '\0';
            lock1 = TRUE; //abre chave para liberar string errada à função levenshtein
            pos = 0;
        }
       
        if(lock1){ //só é liberado quando uma palavra já esta formada 
            
            FILE *ArqDicionario = fopen (NomArqDicionario, "r");  //Abre arquivo de texto com o dicionario
            if(ArqDicionario == NULL){
                printf("Erro, nao foi possivel abrir o arquivo %s!\n", NomArqDicionario);
                return;
            }

            MenorDistancia = INT_MAX; //maior inteiro
            strCerta = (char *)malloc(sizeof(char)); 
            
            while((ch2=fgetc(ArqDicionario)) != EOF){  //lê caracter por caracter e forma a string do dicionario

                if(ch2 == '\n'){ //fim da palavra do dicionario
                    strCerta[strlen(strCerta)+1] = '\0';
                    lock2 = TRUE; //abre chave para liberar string do dicionario à função levenshtein
                    pos = 0;
                }
                
                if(lock1 && lock2){ //só é liberado quando as 2 palavras estao formadas
                    Distancia = Levenshtein(strCerta, strErrada); //calcula a distancia de edicao
                    if(Distancia < MenorDistancia){ //armazena a menor distacia e a palavra correta
                        MenorDistancia = Distancia;
                        Aux = (char *)malloc(strlen(strCerta)*sizeof(char));
                        strcpy(Aux, strCerta); //copia a palavra correta para Aux
                    }
                    strCerta = (char *)malloc(sizeof(char)); //uma nova palavra vai ser lida
                    lock2 = FALSE; //fecha chave
                }

                else if(isalpha(ch2)){
                    strCerta[pos]=ch2;
                    pos++;
                }  
            }   
            
            if(!FimDaLinha){  //Insere uma resposta e distancia de uma aluno na lista
                DistanciaTotal += MenorDistancia;
                Resposta.Distancia = MenorDistancia;
                Resposta.Palavra = (char *)malloc(strlen(Aux)*sizeof(char));
                strcpy(Resposta.Palavra, Aux);
                InsereResposta(Resposta, &lista);
                NumRespostas++;    
            }
            
            else if(FimDaLinha){ //Imprime a lista no arquivo e retira todas as respostas da lista
                DistanciaTotal += MenorDistancia;
                Resposta.Distancia = MenorDistancia;
                Resposta.Palavra = (char *)malloc(strlen(Aux)*sizeof(char));
                strcpy(Resposta.Palavra, Aux);
                InsereResposta(Resposta, &lista); //insere a ultima resposta do aluno na lista
                NumRespostas++;
                fprintf(ArqSaida, "%.1f: ", DistanciaTotal);
                ImprimeRespostaAluno(lista, ArqSaida);
                fprintf(ArqSaida, "\n");
                
                for(i = 1; i <= NumRespostas; i++)  //retira todas respostas
                    RetiraResposta(lista.Primeiro, &lista);
                
                NumRespostas = 0;
                DistanciaTotal = 0;
            }

            lock1 = FALSE;
            free(strCerta);
            fclose(ArqDicionario);
            strErrada = (char *)malloc(sizeof(char));
        }

        else if(isalpha(ch1)){ //continua lendo caracter por caracter
            strErrada[pos] = ch1; //junta os caracteres numa string
            pos++;
        }
    
        FimDaLinha = FALSE;
    }

    free(Aux);
    free(strErrada);
    fclose(ArqSaida);
    fclose(ArqRespostas);
}

//Retorna a menor distancia de edição entre duas strings
float Levenshtein(const char *palavra1, const char *palavra2){

	int i, j, tam1, tam2;
	float insercao, remocao, substituicao, troca, min;
	char c1, c2;

	tam1 = strlen(palavra1);
    tam2 = strlen(palavra2);
    
    float matriz[tam1+1][tam2+1];

	for (i = 0; i <= tam1; i++) {
        matriz[i][0] = i;
    }
    for (j = 0; j <= tam2; j++) {
       matriz[0][j] = j;
    }
    for (i = 1; i <= tam1; i++) {
        c1 = palavra1[i-1];
        for (j = 1; j <= tam2; j++) {
            c2 = palavra2[j-1];
            if (c1 == c2) {	//caso o caracteres forem iguais o custo é 0
                matriz[i][j] = matriz[i-1][j-1];
            }
            else {	//Se forem diferentes, então existe um custo
                insercao = matriz[i][j-1] + 1;
                remocao = matriz[i-1][j] + 1;
                substituicao = matriz[i-1][j-1] + 1.5;  
                troca = (matriz[i][j-1] + 1) + (matriz[i-1][j] + 1);
                min = insercao;
                if (remocao < min) {
                    min = remocao;
                }
                if (substituicao < min) {
                    min = substituicao;
                }
                if(troca < min){
                    min = troca;  
                }
                matriz[i][j] = min;
            }
        }
    }
    return matriz[tam1][tam2];
}
