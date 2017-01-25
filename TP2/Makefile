# TRABALHO PRÁTICO 2 - SURPRESA NA PROVA
# Algoritmos e Estruturas de Dados III - Aluno: Guilherme Saulo Alves

# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -g

# Comando terminal para limpar sem confirmação
RM = rm -f

# Lista dos ficheiros (arquivos) objetos necessários para o programa final
OBJS = main.o grafo.o solucaootima.o readline.o 

# Nome do executável
MAIN = tp2e

# Compilação do programa e passos das ligações de dependências
$(MAIN): $(OBJS)
	@echo ""
	@echo " --- Compilando programa ---"
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $(MAIN)
	@echo ""

%.o: %.c %.h
	@echo ""
	@echo " --- Compilando objeto \"$@\""
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o
	clear

run: $(MAIN)
	./$(MAIN)
