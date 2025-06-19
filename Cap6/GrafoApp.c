#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    // Implementação alternativa do getch para sistemas Unix-like
    int getch(void) {
        struct termios old, new;
        int ch;
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return ch;
    }
#endif

#include "Grafo.h"
#include "../Cap3/Utils.h"

// Códigos de cores ANSI
#define RESET   "\x1b[0m"
#define VERMELHO "\x1b[31m"
#define VERDE   "\x1b[32m"
#define AMARELO "\x1b[33m"
#define AZUL    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define BRANCO  "\x1b[37m"
#define NEGRITO "\x1b[1m"

int comparaVertice(void *info1, void *info2){

    int *id1 = (int *) info1;
    int *id2 = (int *) info2;

    return *id2 - *id1;
}

/* ----------------------------- */
void imprimeAdjacencia(void *info1){
    pVertice v = (pVertice) info1;
    printf("%d - " , *((int *)(v->info)));
}

/* ----------------------------- */
void imprimeVertice(void *info1){
    pVertice v = (pVertice) info1;
    printf("\nVertice %d - Adjacencias [", *((int *)v->info));

    imprimirLista(v->listaAdjacencias, imprimeAdjacencia);
    printf("]\n");
}

/* ----------------------------- */
void imprimeVerticeSemAdjacencias(void *info1){
    pVertice v = (pVertice) info1;
    printf("\nVertice %d - ", *((int *)v->info));
}

/* ---------------------------------------- */
void* alocaInfoVertice(void *info){
   pVertice pv = (pVertice) malloc(sizeof(Vertice));
   pv->info = alocaInfoInt(((pVertice)info)->info);
   return pv;
}

/* ----------------------------- */
void criarGrafoHamiltoniano(pDGrafo grafo) {
    // Cria um grafo hamiltoniano (ciclo simples)
    int vertices[] = {1, 2, 3, 4, 5};
    int numVertices = 5;
    
    // Inclui vértices
    for (int i = 0; i < numVertices; i++) {
        incluirVertice(grafo, &vertices[i], comparaVertice);
    }
    
    // Cria um ciclo hamiltoniano: 1-2-3-4-5-1
    for (int i = 0; i < numVertices; i++) {
        int proximo = (i + 1) % numVertices;
        incluirAresta(grafo, &vertices[i], &vertices[proximo], comparaVertice);
    }
    
    imprimirMensagemSucesso("Grafo Hamiltoniano criado com sucesso!");
    imprimirMensagemInfo("Estrutura: Ciclo hamiltoniano 1->2->3->4->5->1");
}

/* ----------------------------- */
void criarGrafoEuleriano(pDGrafo grafo) {
    // Cria um grafo euleriano (todos os vértices com grau par)
    int vertices[] = {1, 2, 3, 4};
    int numVertices = 4;
    
    // Inclui vértices
    for (int i = 0; i < numVertices; i++) {
        incluirVertice(grafo, &vertices[i], comparaVertice);
    }
    
    // Cria arestas para formar um quadrado (todos vértices com grau 2)
    incluirAresta(grafo, &vertices[0], &vertices[1], comparaVertice);
    incluirAresta(grafo, &vertices[1], &vertices[2], comparaVertice);
    incluirAresta(grafo, &vertices[2], &vertices[3], comparaVertice);
    incluirAresta(grafo, &vertices[3], &vertices[0], comparaVertice);
    
    imprimirMensagemSucesso("Grafo Euleriano criado com sucesso!");
    imprimirMensagemInfo("Estrutura: Quadrado com todos os vértices de grau par");
}

/* ----------------------------- */
void criarGrafoConexo(pDGrafo grafo) {
    // Cria um grafo conexo em forma de estrela
    int vertices[] = {1, 2, 3, 4, 5, 6};
    int numVertices = 6;
    
    // Inclui vértices
    for (int i = 0; i < numVertices; i++) {
        incluirVertice(grafo, &vertices[i], comparaVertice);
    }
    
    // Conecta vértice 1 com todos os outros (estrela)
    for (int i = 1; i < numVertices; i++) {
        incluirAresta(grafo, &vertices[0], &vertices[i], comparaVertice);
    }
    
    // Adiciona algumas arestas extras para tornar mais interessante
    incluirAresta(grafo, &vertices[1], &vertices[2], comparaVertice);
    incluirAresta(grafo, &vertices[3], &vertices[4], comparaVertice);
    
    imprimirMensagemSucesso("Grafo Conexo criado com sucesso!");
    imprimirMensagemInfo("Estrutura: Estrela modificada garantindo conectividade");
}

/* ----------------------------- */
void criarGrafoAleatorio(pDGrafo grafo) {
    int numVertices;
    printf("Quantos vértices deseja no grafo aleatório? ");
    scanf("%d", &numVertices);
    
    if (numVertices <= 0) {
        printf("Número de vértices deve ser positivo!\n");
        return;
    }
    
    // Aloca array de vértices
    int *vertices = (int *)malloc(numVertices * sizeof(int));
    
    // Inicializa gerador de números aleatórios
    srand(time(NULL));
    
    // Cria vértices (1, 2, 3, ..., numVertices)
    for (int i = 0; i < numVertices; i++) {
        vertices[i] = i + 1;
        incluirVertice(grafo, &vertices[i], comparaVertice);
    }
    
    // Calcula número de arestas aleatório (entre numVertices-1 e numVertices*(numVertices-1)/4)
    int minArestas = numVertices - 1; // Para garantir conectividade mínima
    int maxArestas = (numVertices * (numVertices - 1)) / 4; // Não muito denso
    int numArestas = minArestas + rand() % (maxArestas - minArestas + 1);
    
    // Primeiro, conecta em cadeia para garantir conectividade
    for (int i = 0; i < numVertices - 1; i++) {
        incluirAresta(grafo, &vertices[i], &vertices[i + 1], comparaVertice);
    }
    
    // Adiciona arestas aleatórias restantes
    int arestasAdicionadas = numVertices - 1;
    while (arestasAdicionadas < numArestas) {
        int origem = rand() % numVertices;
        int destino = rand() % numVertices;
        
        if (origem != destino) {
            incluirAresta(grafo, &vertices[origem], &vertices[destino], comparaVertice);
            arestasAdicionadas++;
        }
    }
    
    free(vertices);
    imprimirMensagemSucesso("Grafo Aleatorio criado com sucesso!");
    printf("  %s> %sEstrutura: %d vertices, %d arestas geradas%s\n", AZUL, RESET, numVertices, numArestas, RESET);
}

/* ----------------------------- */
void imprimirLinhaDupla(int tamanho) {
    printf("+");
    for (int i = 0; i < tamanho - 2; i++) {
        printf("=");
    }
    printf("+\n");
}

/* ----------------------------- */
void imprimirLinhaSimples(int tamanho) {
    printf("+");
    for (int i = 0; i < tamanho - 2; i++) {
        printf("-");
    }
    printf("+\n");
}

/* ----------------------------- */
void imprimirRodape(int tamanho) {
    printf("+");
    for (int i = 0; i < tamanho - 2; i++) {
        printf("=");
    }
    printf("+\n");
}

/* ----------------------------- */
void imprimirTituloDecorado(const char* titulo) {
    int tamanho = 60;
    int tamanhoTitulo = strlen(titulo);
    int padding = (tamanho - tamanhoTitulo - 4) / 2;
    
    printf("\n");
    imprimirLinhaDupla(tamanho);
    printf("|");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s%s%s", NEGRITO CIANO, titulo, RESET);
    for (int i = 0; i < tamanho - tamanhoTitulo - padding - 3; i++) printf(" ");
    printf("|\n");
    imprimirRodape(tamanho);
    printf("\n");
}

/* ----------------------------- */
void imprimirOpcaoMenu(int numero, const char* descricao, const char* detalhes) {
    if (detalhes != NULL) {
        printf("  %s%2d%s | %s%-25s%s | %s%s%s\n", 
               NEGRITO AMARELO, numero, RESET,
               VERDE, descricao, RESET,
               AZUL, detalhes, RESET);
    } else {
        printf("  %s%2d%s | %s%s%s\n", 
               NEGRITO AMARELO, numero, RESET,
               VERDE, descricao, RESET);
    }
}

/* ----------------------------- */
void imprimirSeparadorSecao(const char* nomeSecao) {
    printf("\n  %s+-- %s --+%s\n", CIANO, nomeSecao, RESET);
}

/* ----------------------------- */
void imprimirMensagemSucesso(const char* mensagem) {
    printf("\n%s[OK] %s%s\n", VERDE NEGRITO, mensagem, RESET);
}

/* ----------------------------- */
void imprimirMensagemErro(const char* mensagem) {
    printf("\n%s[ERRO] %s%s\n", VERMELHO NEGRITO, mensagem, RESET);
}

/* ----------------------------- */
void imprimirMensagemInfo(const char* mensagem) {
    printf("  %s> %s%s\n", AZUL, mensagem, RESET);
}

/* ----------------------------- */
void imprimirStatusGrafo(pDGrafo grafo) {
    printf("\n  %s+-- STATUS DO GRAFO --+%s\n", MAGENTA, RESET);
    
    if (grafo != NULL && grafo->listaVertices != NULL) {
        printf("  %s|%s Vertices: %s%d%s\n", MAGENTA, RESET, NEGRITO, grafo->listaVertices->quantidade, RESET);
        
        // Conta arestas
        int totalArestas = 0;
        pNoh atual = grafo->listaVertices->primeiro;
        while (atual != NULL) {
            pVertice v = (pVertice)atual->info;
            if (v->listaAdjacencias != NULL) {
                totalArestas += v->listaAdjacencias->quantidade;
            }
            atual = atual->prox;
        }
        
        printf("  %s|%s Arestas: %s%d%s\n", MAGENTA, RESET, NEGRITO, totalArestas, RESET);
        
        if (grafo->listaVertices->quantidade == 0) {
            printf("  %s|%s %sGrafo vazio%s\n", MAGENTA, RESET, AMARELO, RESET);
        }
    } else {
        printf("  %s|%s %sGrafo nao inicializado%s\n", MAGENTA, RESET, VERMELHO, RESET);
    }
    
    printf("  %s+---------------------+%s\n", MAGENTA, RESET);
}

/* ----------------------------- */
void aguardarTecla() {
    printf("\n%sPressione qualquer tecla para continuar...%s", AMARELO, RESET);
    getch();
    printf("\n");
}

/* ----------------------------- */
int main(){

    int vertices[] = {1,2,3,4,5};

    int opcao, vOrigem, vDestino;
    int *pv;

    pDGrafo grafo = criarGrafo();

    do{
        // Limpar tela (funciona na maioria dos terminais)
        printf("\033[2J\033[H");
        
        imprimirTituloDecorado("SISTEMA DE GRAFOS COMPLETO");
        
        // Mostrar status do grafo
        imprimirStatusGrafo(grafo);
        
        printf("\n");
        imprimirSeparadorSecao("OPERACOES BASICAS");
        imprimirOpcaoMenu(0, "Criar Grafo Exemplo", "Hamiltoniano, Euleriano, etc.");
        imprimirOpcaoMenu(1, "Incluir Vertice", "Adicionar novo vertice");
        imprimirOpcaoMenu(2, "Incluir Aresta", "Conectar dois vertices");
        imprimirOpcaoMenu(3, "Excluir Vertice", "Remover vertice existente");
        imprimirOpcaoMenu(4, "Excluir Aresta", "Remover conexao");
        imprimirOpcaoMenu(5, "Mostrar Grafo", "Visualizar estrutura atual");
        
        imprimirSeparadorSecao("ALGORITMOS DE BUSCA");
        imprimirOpcaoMenu(6, "Busca em Profundidade", "DFS - Depth First Search");
        imprimirOpcaoMenu(7, "Busca em Amplitude", "BFS - Breadth First Search");
        imprimirOpcaoMenu(8, "Existe Caminho?", "Verificar conectividade");
        imprimirOpcaoMenu(9, "Encontrar Caminho", "Mostrar rota entre vertices");
        
        imprimirSeparadorSecao("PROPRIEDADES DO GRAFO");
        imprimirOpcaoMenu(11, "Verificar Conexidade", "Grafo conexo/desconexo");
        imprimirOpcaoMenu(12, "Verificar Euleriano", "Caminho euleriano");
        imprimirOpcaoMenu(13, "Verificar Hamiltoniano", "Caminho hamiltoniano");
        imprimirOpcaoMenu(14, "Colorir Grafo", "Coloracao de vertices");
        imprimirOpcaoMenu(15, "Verificar Bipartido", "Grafo bipartido");
        
        imprimirSeparadorSecao("SISTEMA");
        imprimirOpcaoMenu(10, "Sair", "Encerrar programa");
        
        printf("\n%s+-------------------------------------------------+%s\n", CIANO, RESET);
        printf("%s|%s Digite sua opcao: ", CIANO, RESET);
        scanf("%d", &opcao);
        printf("%s+-------------------------------------------------+%s\n", CIANO, RESET);

        switch (opcao){

         case 0 :
            printf("\033[2J\033[H");
            imprimirTituloDecorado("CRIADOR DE GRAFOS EXEMPLOS");
            
            printf("\n");
            imprimirSeparadorSecao("TIPOS DE GRAFOS DISPONIVEIS");
            imprimirOpcaoMenu(0, "Grafo Hamiltoniano", "Ciclo que visita todos os vertices");
            imprimirOpcaoMenu(1, "Grafo Euleriano", "Permite percorrer todas as arestas");
            imprimirOpcaoMenu(2, "Grafo Conexo", "Estrutura em estrela modificada");
            imprimirOpcaoMenu(3, "Grafo Aleatorio", "Geracao personalizada");
            imprimirOpcaoMenu(4, "Voltar", "Retornar ao menu principal");
            
            printf("\n%s+-------------------------------------------------+%s\n", CIANO, RESET);
            printf("%s|%s Digite sua opcao: ", CIANO, RESET);
            int subOpcao;
            scanf("%d", &subOpcao);
            printf("%s+-------------------------------------------------+%s\n", CIANO, RESET);

            switch (subOpcao) {
                case 0:
                    printf("\n");
                    imprimirMensagemInfo("Criando grafo hamiltoniano...");
                    criarGrafoHamiltoniano(grafo);
                    printf("\n");
                    imprimirTituloDecorado("ESTRUTURA DO GRAFO HAMILTONIANO");
                    mostrarGrafo(grafo, imprimeVertice);
                    aguardarTecla();
                    break;
                case 1:
                    printf("\n");
                    imprimirMensagemInfo("Criando grafo euleriano...");
                    criarGrafoEuleriano(grafo);
                    printf("\n");
                    imprimirTituloDecorado("ESTRUTURA DO GRAFO EULERIANO");
                    mostrarGrafo(grafo, imprimeVertice);
                    aguardarTecla();
                    break;
                case 2:
                    printf("\n");
                    imprimirMensagemInfo("Criando grafo conexo...");
                    criarGrafoConexo(grafo);
                    printf("\n");
                    imprimirTituloDecorado("ESTRUTURA DO GRAFO CONEXO");
                    mostrarGrafo(grafo, imprimeVertice);
                    aguardarTecla();
                    break;
                case 3:
                    printf("\n");
                    imprimirMensagemInfo("Iniciando criação de grafo aleatório...");
                    criarGrafoAleatorio(grafo);
                    printf("\n");
                    imprimirTituloDecorado("ESTRUTURA DO GRAFO ALEATÓRIO");
                    mostrarGrafo(grafo, imprimeVertice);
                    aguardarTecla();
                    break;
                case 4:
                    imprimirMensagemInfo("Retornando ao menu principal...");
                    break;
                            default:
                imprimirMensagemErro("Opcao invalida! Tente novamente.");
                    aguardarTecla();
                    break;
            }
            break;

        case 1 :
            printf("\n");
            imprimirTituloDecorado("INCLUIR NOVO VERTICE");
            
            pv = (int *)malloc(sizeof(int));
            printf("\n%s+-------------------------------------------------+%s\n", CIANO, RESET);
            printf("%s|%s Digite o ID do vertice: ", CIANO, RESET);
            scanf("%d", pv);
            printf("%s+-------------------------------------------------+%s\n", CIANO, RESET);
            
            incluirVertice(grafo, pv, comparaVertice);
            imprimirMensagemSucesso("Vertice incluido com sucesso!");
            printf("  %s> %sVertice ID: %s%d%s\n", AZUL, RESET, NEGRITO, *pv, RESET);
            
            printf("\n");
            imprimirTituloDecorado("ESTRUTURA ATUAL DO GRAFO");
            mostrarGrafo(grafo, imprimeVertice);
            aguardarTecla();
            break;

        case 2 :
            printf("\nID do vertice origem: ");
            scanf("%d", &vOrigem);
            printf("ID do vertice destino: ");
            scanf("%d", &vDestino);
            incluirAresta(grafo, &vOrigem, &vDestino, comparaVertice);

            printf("Aresta %d-%d incluida com sucesso!\n", vOrigem, vDestino);
            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 3 :
            printf("\nID do vertice a ser excluido: ");
            scanf("%d", &vOrigem);
            excluirVertice(grafo, &vOrigem, comparaVertice);

            printf("Vertice %d excluido com sucesso!\n", vOrigem);
            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 4 :
            printf("\nID do vertice origem: ");
            scanf("%d", &vOrigem);
            printf("ID do vertice destino: ");
            scanf("%d", &vDestino);
            excluirAresta(grafo, &vOrigem, &vDestino, comparaVertice);

            printf("Aresta %d-%d excluida com sucesso!\n", vOrigem, vDestino);
            mostrarGrafo(grafo, imprimeVertice);
            getch();
            break;

        case 5 :
            printf("\033[2J\033[H");
            imprimirTituloDecorado("VISUALIZAÇÃO COMPLETA DO GRAFO");
            
            // Mostrar estatísticas
            imprimirStatusGrafo(grafo);
            
            printf("\n");
            imprimirSeparadorSecao("ESTRUTURA DE ADJACENCIAS");
            
            if (grafo != NULL && grafo->listaVertices != NULL && grafo->listaVertices->quantidade > 0) {
                mostrarGrafo(grafo, imprimeVertice);
            } else {
                imprimirMensagemInfo("Grafo vazio - nenhum vertice encontrado");
                imprimirMensagemInfo("Use a opcao 0 para criar um grafo exemplo");
                imprimirMensagemInfo("Ou use a opcao 1 para adicionar vertices manualmente");
            }
            
            aguardarTecla();
            break;

        case 6 :
            printf("\n=== BUSCA EM PROFUNDIDADE ===\n");
            buscaEmProfundidade(grafo, comparaVertice, imprimeVerticeSemAdjacencias);
            printf("\n");
            getch();
            break;

        case 7 :
            printf("\n=== BUSCA EM AMPLITUDE ===\n");
            buscaAmplitude(grafo, comparaVertice, imprimeVerticeSemAdjacencias);
            printf("\n");
            getch();
            break;

        case 8 :
            printf("\nID do vertice origem: ");
            scanf("%d", &vOrigem);
            printf("ID do vertice destino: ");
            scanf("%d", &vDestino);

            int result = existeCaminho(grafo, &vOrigem, &vDestino, comparaVertice);
            if (result != 0)
                printf("+ Existe caminho de %d para %d!\n", vOrigem, vDestino);
            else
                printf("- Nao existe caminho de %d para %d.\n", vOrigem, vDestino);

            getch();
            break;

        case 9 :
            printf("\nID do vertice origem: ");
            scanf("%d", &vOrigem);
            printf("ID do vertice destino: ");
            scanf("%d", &vDestino);

            pDLista caminho = getCaminho(grafo, &vOrigem, &vDestino, comparaVertice, alocaInfoVertice);
            if (caminho->quantidade > 0){
                printf("\n+ Caminho encontrado: ");
                imprimirLista(caminho, imprimeVerticeSemAdjacencias);
                printf("\n");
            }
            else
                printf("\n- Nao existe caminho entre os vertices.\n");

            getch();
            break;

        case 11 :
            printf("\n=== VERIFICACAO: GRAFO CONEXO ===\n");
            if (grafoConexo(grafo, comparaVertice)) {
                printf("+ O grafo eh CONEXO\n");
                printf("  (Existe caminho entre todos os pares de vertices)\n");
            } else {
                printf("- O grafo eh DESCONEXO\n");
                printf("  (Existem vertices sem caminho entre eles)\n");
            }
            getch();
            break;

        case 12 :
            printf("\n=== VERIFICACAO: CAMINHO EULERIANO ===\n");
            if (existeCaminhoEuleriano(grafo, comparaVertice)) {
                printf("+ O grafo possui CAMINHO EULERIANO\n");
                printf("  (Eh possivel percorrer todas as arestas exatamente uma vez)\n");
            } else {
                printf("- O grafo NAO possui caminho euleriano\n");
                printf("  (Nao eh possivel percorrer todas as arestas uma unica vez)\n");
            }
            getch();
            break;

        case 13 :
            printf("\n=== VERIFICACAO: CAMINHO HAMILTONIANO ===\n");
            if (existeCaminhoHamiltoniano(grafo, comparaVertice)) {
                printf("+ O grafo possui CAMINHO HAMILTONIANO\n");
                printf("  (Eh possivel visitar todos os vertices exatamente uma vez)\n");
            } else {
                printf("- O grafo NAO possui caminho hamiltoniano\n");
                printf("  (Nao eh possivel visitar todos os vertices uma unica vez)\n");
            }
            getch();
            break;

        case 14 :
            printf("\n=== COLORACAO DO GRAFO ===\n");
            int numCores = coloracao(grafo, comparaVertice);
            if (numCores > 0) {
                printf("+ Coloracao realizada com sucesso!\n");
                printf("  Numero minimo de cores necessarias: %d\n", numCores);
                printf("  (Vertices adjacentes tem cores diferentes)\n");
            } else {
                printf("- Nao foi possivel colorir o grafo (grafo vazio?)\n");
            }
            getch();
            break;

        case 15 :
            printf("\n=== VERIFICACAO: GRAFO BIPARTIDO ===\n");
            if (grafoBipartido(grafo, comparaVertice)) {
                printf("+ O grafo eh BIPARTIDO\n");
                printf("  (Vertices podem ser divididos em dois conjuntos independentes)\n");
            } else {
                printf("- O grafo NAO eh bipartido\n");
                printf("  (Nao pode ser dividido em dois conjuntos independentes)\n");
            }
            getch();
            break;

        case 10 :
            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
            getch();
            break;
        }

    }while (opcao != 10);

    printf("Sistema encerrado.\n");
    return 0;
}
