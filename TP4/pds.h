/*==================================================================================================================
Trabalho Prático 4 - Erros de Português                 
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
pds.h: Possue as declarações da Implementação sequencial do algoritmo                   
====================================================================================================================*/

#ifndef PDS_H_INCLUDED
#define PDS_H_INCLUDED

#define TRUE 1
#define FALSE 0

/*============================================= Funções ============================================================*/

//Lê as palavras dos arquivos caracter por caracter e passa-as a função levenshtein
void PPSequencial(char *NomArqRespostas, char *NomArqDicionario, char *NomArqSaida);

//Retorna a menor distancia de edição entre duas strings
float Levenshtein(const char *palavra1, const char *palavra2);

#endif // PDS_H_INCLUDED