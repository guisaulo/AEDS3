/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
pdpp.h: Possue as declarações da Implementação paralela do algoritmo                     
====================================================================================================================*/

#ifndef PDPP_H_INCLUDED
#define PDPP_H_INCLUDED

//Lê as palavras dos arquivos caracter por caracter e passa-as a função levenshtein
void PPPalavras(char *NomArqRespostas, char *NomArqDicionario, char *NomArqSaida, int numThreads);

#endif // PDPP_H_INCLUDED