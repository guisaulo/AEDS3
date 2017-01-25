/*==================================================================================================================
Trabalho Prático 3 - Facilitando a correção                     
Algoritmos e Estruturas de Dados 3                            
Aluno: Guilherme Saulo Alves               
biblioteca.h: Possue os TADs e as declarações de todas funções usadas no programa                   
====================================================================================================================*/

#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#define TAMMAXTERMO 50
#define TAMMAXALUNO 30
#define NUMFITAS 4

/* =========================================== TAD Heap ================================================= */

typedef int Indice;

typedef struct{
	char Linha[TAMMAXTERMO+TAMMAXALUNO];  //Armaze as linhas lidas do arquivo de entrada
    short Marcacao; //Marca os membros do proximo bloco.
    short NumDaFita; //Armazena o número das fitas (arquivos temporários)
}TipoHeap;

int NumLinhasHeap, NumDeLinhas, Fitas;  //Quantidade de linhas do heap e de fitas ao decorrer do programa

/* =================================== Funções io.c ================================================== */

//Lê todos os arquivos de entradas e escreve as tuplas no arquivo lista retornando a quantidade de termos
int CriaLista(short inicio, short fim, char *argv[]);
//Faz a primeira passada no arquivo, substitui o menor elemento do heap pelo proximo item do arquivo e salva o item retirado nas "fitas"
short CriaFitas(TipoHeap *Heap, FILE *ArqEntrada, FILE **ArqTemporario, short MaiorLinha);
//Fecha e remove os arquivos temporários
void RemoveArqTemporarios(FILE** ArqTemporario, short TotalFitas);

/* =================================== Funções ordenacao.c ======================================== */

//Função para fazer a intercalação entre as fitas pelo método Seleção por substuição
void Intercalacao(TipoHeap *Heap, FILE **ArqTemporario, char *NomeSaida, short NumDeBlocos1, short MaiorLinha);
//Função principal para ordenar o arquivo de entrada pelo método de Intercalação Balanceada por Substituição
void OrdenacaoExterna(FILE *ArqEntrada);

/* =================================== Funções heap.c ================================================ */

//Constrói um Heap com os termos das linhas do arquivo
void ConstroiHeap(TipoHeap *A);
//Função para refazer a condição de Heap
void RefazHeap(Indice Esq, Indice Dir, TipoHeap *A);
//Função para retirar o menor elemento do Heap e substituir pelo proximo elemento do arquivo.
void RetiraMinHeap(TipoHeap *A, FILE *ArquivoEntrada, short MaiorLinha);

/* =================================== Funções indice.c ============================================== */

//Produz o ́ındice invertido dos termos nas respostas dos alunos
void IndiceInvertido(FILE *lista_ordenada, char *ArgvArqSaida);

#endif // BIBLIOTECA_H_INCLUDED