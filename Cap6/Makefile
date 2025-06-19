# Makefile para Projeto de Grafos Avançados
# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Diretórios
SRC_DIR = .
CAP3_DIR = ../Cap3
CAP4_DIR = ../Cap4

# Arquivos principais
MAIN_APP = GrafoApp.c
TESTE_APP = TesteGrafosAvancados.c

# Headers necessários
HEADERS = Grafo.h TAD_Grafo.h $(CAP3_DIR)/Lista.h $(CAP4_DIR)/Pilha.h

# Arquivos objeto
OBJS = 

# Executáveis
EXEC_MAIN = grafo_app
EXEC_TESTE = teste_grafos

# Regra padrão
all: $(EXEC_MAIN) $(EXEC_TESTE)

# Compilar aplicação principal
$(EXEC_MAIN): $(MAIN_APP) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXEC_MAIN) $(MAIN_APP)

# Compilar aplicação de teste
$(EXEC_TESTE): $(TESTE_APP) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXEC_TESTE) $(TESTE_APP)

# Executar aplicação principal
run-main: $(EXEC_MAIN)
	./$(EXEC_MAIN)

# Executar testes
run-test: $(EXEC_TESTE)
	./$(EXEC_TESTE)

# Limpar arquivos compilados
clean:
	rm -f $(EXEC_MAIN) $(EXEC_TESTE) *.o

# Limpar e recompilar
rebuild: clean all

# Verificar sintaxe
check: $(MAIN_APP) $(TESTE_APP)
	$(CC) $(CFLAGS) -fsyntax-only $(MAIN_APP)
	$(CC) $(CFLAGS) -fsyntax-only $(TESTE_APP)

# Mostrar informações
info:
	@echo "=== PROJETO GRAFOS AVANÇADOS ==="
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Executáveis: $(EXEC_MAIN), $(EXEC_TESTE)"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make all        - Compilar tudo"
	@echo "  make run-main   - Executar aplicação principal"
	@echo "  make run-test   - Executar testes"
	@echo "  make clean      - Limpar arquivos compilados"
	@echo "  make rebuild    - Limpar e recompilar"
	@echo "  make check      - Verificar sintaxe"
	@echo "  make info       - Mostrar estas informações"

# Regras que não criam arquivos
.PHONY: all run-main run-test clean rebuild check info 