#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"

//retorna uma string para cada linha do arquivo para ser tratada no main
char *fgetline(FILE *file){

    char *line=0;
    fpos_t fpos;
    int size=0, read=0;

    if(feof(file))
        return 0;
    //Guardo a posicao atual no arquivo
    fgetpos(file, &fpos);

    //Vejo o tamanho da linha.
    read=fscanf(file, "%*[^\n]%n", &size);

    //Verifico se o fscanf() nao falhou ao ler o arquivo.
    if(read < 0 || read == EOF)
        return 0;
    if(!size) /* Linha em branco. */{
        fsetpos(file, &fpos);
        fgetc(file); /* Engole a linha em branco. */
        //Nada melhor para representar uma linha em branco que um calloc(1) :D
        return calloc(1, 1);
    }

    //Tudo certo! Hora de alocar o retorno, reler a linha e retornar para o usuario
    line = malloc(size + 1);
    if(!line) return 0;
    fsetpos(file, &fpos);
    //Ja sei o quanto preciso ler, posso usar fread().
    read=fread(line, 1, size, file);
    if(read != size){
        //fread() falhou!
        free(line);
        return 0;
    }
    //Elimina o '\n' do final da linha.
    fgetc(file);
    //Fecha a string.
    line[size] = '\0';
    return line;
}

