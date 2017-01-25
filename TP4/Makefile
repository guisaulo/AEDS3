######################################################################
# TRABALHO PRÁTICO 4 - Erros de Português							 #
# Algoritmos e Estruturas de Dados III					             #
# Guilherme Saulo Alves   											 #
######################################################################

# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -pg -g3

# Comando terminal para limpar sem confirmação
RM = rm -f

# Lista dos ficheiros (arquivos) objetos necessários para o programa final
OBJS = main.o pds.o pdpp.o pdcpi.o lista.o

# Nome do executável
MAIN = tp4

# Compilação do programa e passos das ligações de dependências
$(MAIN): $(OBJS)
	@echo ""
	@echo "Compilando Programa .."
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $(MAIN) -lpthread 
	@echo ""

%.o: %.c %.h
	@echo ""
	@echo "Compilando objeto \"$@\""
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o
	$(RM) output_*
	clear

run: $(MAIN)
	./$(MAIN)
