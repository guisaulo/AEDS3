all: comp1 comp2 exec clean

#compila cabecalho e funcoes (gera .o)
comp1:
	gcc -c main.c buscalargura.c buscaprofundidade.c dijkstra.c grafo.c 

#compila programa principal, com o .o gerado
comp2: 
	gcc main.o buscalargura.o buscaprofundidade.o dijkstra.o grafo.o -o tp1

#executa o programa principal
exec:  
	./tp1 input.txt output.txt

#deleta arquivos .o gerados
clean:
	rm -rf *.o
