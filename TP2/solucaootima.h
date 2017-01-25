#ifndef SOLUCAOOTIMA_H_INCLUDED
#define SOLUCAOOTIMA_H_INCLUDED

/*================Funções da solucao otima====================*/

//Cria o primeiro conjunto com todos os vertices do grafo
int ForcaBruta(TipoGrafo *Grafo);
//Gera todas as combinação de no minimo 2 alunos por subconjuntos
int GeraSubConjuntos(TipoGrafo *Grafo, int *input);
//Gera pares de alunos e testa se possue arestas entre eles em um dado subconjunto
int TestaIndependencia(TipoGrafo *Grafo, int *str, int tamanho);
//Verifica se o vetor num nao contem algarismos repetidos
int EhSemRepeticao(int *num, int r);

#endif // SOLUCAOOTIMA_H_INCLUDED
