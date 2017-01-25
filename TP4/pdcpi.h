/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
pdcpi.h: Possue as declarações da Implementação paralela do algoritmo                     
====================================================================================================================*/          

#ifndef PDCPI_H_INCLUDED
#define PDCPI_H_INCLUDED

#define TRUE 1
#define FALSE 0

//Lê as palavras dos arquivos caracter por caracter e passa-as a função levenshtein
void PPCompInternas(char *NomArqRespostas, char *NomArqDicionario, char *NomArqSaida, int numThreads);

//Retorna a menor distancia de edição entre duas strings
float LevenshteinParalelo(const char *palavra1, const char *palavra2);

#endif // PDCPI_H_INCLUDED