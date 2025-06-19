# Instruções de Uso - Grafos Avançados

## Visão Geral

Este projeto implementa 4 funcionalidades avançadas para o TAD Grafo:

1. **Verificar se um grafo é hamiltoniano** - Encontra caminhos que visitam cada vértice uma vez
2. **Verificar se um grafo é euleriano** - Encontra caminhos que usam cada aresta uma vez
3. **Verificar se um grafo é conexo** - Verifica se há caminho entre todos os vértices
4. **Colorir grafo** - Atribui cores aos vértices sem conflitos adjacentes

## Como Compilar

### Opção 1: Usando Makefile (Recomendado)

```bash
cd Cap6
make info    # Ver opções disponíveis
make all     # Compilar tudo
```

### Opção 2: Compilação Manual

```bash
cd Cap6
gcc -o teste_grafos TesteGrafosAvancados.c
gcc -o grafo_app GrafoApp.c
```

## Como Executar

### Teste Automático das Funcionalidades

```bash
make run-test
# ou
./teste_grafos
```

### Aplicação Original do Grafo

```bash
make run-main
# ou
./grafo_app
```

## Como Usar as Funções

### 1. Verificar Grafo Hamiltoniano

```c
#include "Grafo.h"

// Criar e popular grafo
pDGrafo grafo = criarGrafo();
// ... adicionar vértices e arestas ...

// Verificar se é hamiltoniano
int resultado = existeCaminhoHamiltoniano(grafo, funcaoComparacao);
if (resultado) {
    printf("Grafo possui caminho hamiltoniano!\n");
} else {
    printf("Grafo NÃO possui caminho hamiltoniano.\n");
}
```

**Quando usar:** Problemas de roteamento, caixeiro viajante, planejamento de rotas.

### 2. Verificar Grafo Euleriano

```c
// Verificar se é euleriano
int resultado = existeCaminhoEuleriano(grafo, funcaoComparacao);
if (resultado) {
    printf("Grafo possui caminho euleriano!\n");
} else {
    printf("Grafo NÃO possui caminho euleriano.\n");
}
```

**Quando usar:** Problemas de percorrer todas as arestas (pontes de Königsberg), desenho de figuras sem levantar o lápis.

### 3. Verificar Grafo Conexo

```c
// Verificar se é conexo
int resultado = grafoConexo(grafo, funcaoComparacao);
if (resultado) {
    printf("Grafo é conexo!\n");
} else {
    printf("Grafo NÃO é conexo.\n");
}
```

**Quando usar:** Verificar conectividade de redes, integridade de sistemas distribuídos.

### 4. Colorir Grafo

```c
// Colorir grafo
int numCores = coloracao(grafo);
printf("Número mínimo de cores necessárias: %d\n", numCores);
```

**Quando usar:** Alocação de recursos, scheduling, atribuição de frequências.

## Exemplos Práticos

### Exemplo 1: Rede Social

```c
// Verificar se todos os usuários estão conectados
if (grafoConexo(redeSocial, comparaUsuario)) {
    printf("Todos os usuários podem se comunicar!\n");
}
```

### Exemplo 2: Planejamento de Rotas

```c
// Verificar se é possível visitar todas as cidades
if (existeCaminhoHamiltoniano(mapaRegioes, comparaCidade)) {
    printf("É possível fazer o tour completo!\n");
}
```

### Exemplo 3: Inspeção de Ruas

```c
// Verificar se é possível inspecionar todas as ruas
if (existeCaminhoEuleriano(mapaRuas, comparaRua)) {
    printf("Pode inspecionar todas as ruas em uma única viagem!\n");
}
```

### Exemplo 4: Alocação de Salas

```c
// Determinar quantas salas diferentes são necessárias
int salas = coloracao(grafoConflitos);
printf("Mínimo de %d salas necessárias para evitar conflitos\n", salas);
```

## Estrutura do Menu Interativo

Quando executar `./teste_grafos`, você verá:

```
=== SISTEMA DE GRAFOS AVANÇADOS ===
1 - Executar Testes Automáticos
2 - Criar Grafo Personalizado
3 - Verificar se Grafo é Conexo
4 - Verificar Caminho Euleriano
5 - Verificar Caminho Hamiltoniano
6 - Colorir Grafo
0 - Sair
```

**Recomendação:** Comece com a opção 1 para ver exemplos de funcionamento.

## Interpretação dos Resultados

### Grafo Hamiltoniano

- **Retorna 1:** Existe caminho que visita cada vértice uma vez
- **Retorna 0:** Não existe tal caminho
- **Complexidade:** O(n!) - muito lento para grafos grandes

### Grafo Euleriano

- **Retorna 1:** Existe caminho que usa cada aresta uma vez
- **Retorna 0:** Não existe tal caminho
- **Teoria:** Funciona se 0 ou 2 vértices têm grau ímpar

### Grafo Conexo

- **Retorna 1:** Existe caminho entre qualquer par de vértices
- **Retorna 0:** Grafo tem componentes desconectados

### Coloração

- **Retorna N:** Número mínimo de cores necessárias
- **Valor baixo:** Grafo tem poucos conflitos
- **Valor alto:** Grafo tem muitos conflitos adjacentes

## Limitações Importantes

1. **Performance:** Algoritmo hamiltoniano é exponencial
2. **Memória:** Limitado a MAX_CORES (100) para coloração
3. **Tipos:** Funciona com vértices que têm IDs inteiros
4. **Compilação:** Pode haver warnings devido à estrutura do TAD

## Troubleshooting

### Erro de Compilação

```bash
# Verificar se os headers estão corretos
make check
```

### Erro de Execução

```bash
# Verificar se os TADs de Lista e Pilha estão implementados
ls ../Cap3/Lista.h
ls ../Cap4/Pilha.h
```

### Resultado Inesperado

- Verificar se a função de comparação está correta
- Conferir se o grafo foi construído corretamente
- Testar com grafos menores primeiro

## Próximos Passos

1. **Teste com seus próprios grafos**
2. **Experimente diferentes tamanhos**
3. **Compare resultados com a teoria**
4. **Implemente melhorias se necessário**

## Contato e Suporte

Para dúvidas sobre a implementação, consulte:

- `README_Grafos_Avancados.md` - Documentação técnica completa
- Código fonte comentado nos arquivos `.h`
- Exemplos práticos em `TesteGrafosAvancados.c`

---

**Boa sorte com seus experimentos em teoria dos grafos!** 🚀
