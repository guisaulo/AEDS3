#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "solucaootima.h"

//Cria o primeiro conjunto com todos os vertices do grafo
int ForcaBruta(TipoGrafo *Grafo){

    int i, tamanhoSet;
    int input[Grafo->NumVertices];

    for(i=0; i<Grafo->NumVertices; i++)
        input[i]=i+1;

    tamanhoSet=GeraSubConjuntos(Grafo, input); //obtem o tamanho do maior subconjunto independente

    return tamanhoSet;
}

//Gera todas as combinação de no minimo 2 alunos por subconjuntos
int GeraSubConjuntos(TipoGrafo *Grafo, int *input){

    int MAX, MASK, NUM, i, j, contador,tamanho, maiorSet=0;
    int str[Grafo->NumVertices];

    MAX=~(1<<Grafo->NumVertices); //Manda o bit 1 para a n-ésima posição. Os bits são invertidos para que a posição n esteja com o bit zero, a fim de marcar o final do processo.
    NUM=1; //Primeiro número é o 1.

    while(MAX&NUM){ //Quando o número alcançar MAX, o loop será encerrado.
        MASK=1;
        i=j=0;

        while(MAX&MASK){
            if(NUM&MASK){ //Verdadeiro se NUM tem um bit 1 na posição indicada por MASK.
                str[i]=input[j]; //Gera a combinação em str
                i++;
            }
            j++;
            MASK=MASK<<1;//Desloca a máscara
        }
        //aqui pegamos o tamanho do vetor que representa um subconjunto
        str[i]='\0' ;
        tamanho=0;

        while(str[tamanho]!='\0'){
            tamanho++;
        }

        //comparamos se existe aresta entre dois alunos somente somente se o subconjunto for maior ou igual a 2
        if(tamanho>=1){
            
            /*printf("\nSubSet: ");

            for(i=0; i<tamanho; i++){
                printf("%d ", str[i]) ;
            }*/

            //contador recebe 0 se o subconjunto é independente ou >0 para ser for dependente
            contador=TestaIndependencia(Grafo, str, tamanho);

            //printf("cont:%dtam:%d ", contador, tamanho);
            if(contador==0){ //caso o subconjunto seja independente
                if(tamanho>maiorSet)
                    maiorSet=tamanho; //quantidade de alunos do maior conjunto independente
            }
        }
        NUM++ ;
    }
    return maiorSet;
}

//Gera pares de alunos e testa se possue arestas entre eles em um dado subconjunto
int TestaIndependencia(TipoGrafo *Grafo, int *str, int tamanho){

    int r, i, j, contador, *num;

    r=2;
    num=(int *)malloc(r+1*sizeof(int)) ;
    num[r]=0;
    contador=0;

    while(num[r]==0){
        for(i=0; i<tamanho; i++) {
            //Mostra a permutacao na tela se e somente se `num' nao contem algarismos repetidos
            if(EhSemRepeticao(num, r)){
                for(j=0; j<r-1; j++) {
                    //printf("[%d %d]",str[num[j]], str[num[j+1]]);
                        if(ExisteAresta(str[num[j]], str[num[j+1]], Grafo))
                            contador++;
                }
            }
            /* incrementa o algarismo menos significativo. */
            num[0]++;
        }

        /* distribui os vai-uns. */
        for(i=0; i < r; i++) {
            if(num[i] == tamanho) {
                num[i] = 0;
                num[i+1]++ ;
            }
        }
    }
    free(num);
    return contador;
}

//Verifica se o vetor num nao contem algarismos repetidos
int EhSemRepeticao(int *num, int r) {
    int i, j;

    for(i=0; i<r; i++) {
        for(j=0; j < r && i != j; j++) {
            if(num[i] == num[j]) {
                return 0;
            }
        }
    }
    return 1 ;
}
