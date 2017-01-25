######################################################################
# TRABALHO PRÁTICO 3 - Facilitando a correção						 #
# Algoritmos e Estruturas de Dados III					             #
# Guilherme Saulo Alves   											 #
######################################################################

# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -g

# Comando terminal para limpar sem confirmação
RM = rm -f

# Lista dos ficheiros (arquivos) objetos necessários para o programa final
OBJS = main.o io.o ordenacao.o heap.o indice.o

# Nome do executável
MAIN = tp3

# Compilação do programa e passos das ligações de dependências
$(MAIN): $(OBJS)
	@echo ""
	@echo "Compilando Programa .."
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $(MAIN)
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
