#ifndef COLORACAO_H
#define COLORACAO_H

// Estrutura simplificada para armazenar cores dos vértices
#define MAX_VERTICES_COLORACAO 100

// Arrays paralelos para armazenar vértices e suas cores
pVertice verticesColoridos[MAX_VERTICES_COLORACAO];
int coresAtribuidas[MAX_VERTICES_COLORACAO];
int totalVerticesColoridos = 0;

// Função para inicializar o sistema de coloração
void inicializarColoracao()
{
    totalVerticesColoridos = 0;
    for (int i = 0; i < MAX_VERTICES_COLORACAO; i++) 
    {
        verticesColoridos[i] = NULL;
        coresAtribuidas[i] = 0;
    }
}

// Função para obter a cor de um vértice
int obterCorVertice(pVertice vertice)
{
    for (int i = 0; i < totalVerticesColoridos; i++)
    {
        if (verticesColoridos[i] == vertice)
        {
            return coresAtribuidas[i];
        }
    }
    return -1; // Vértice não colorido
}

// Função para definir a cor de um vértice
void definirCorVertice(pVertice vertice, int cor)
{
    // Verifica se o vértice já foi colorido
    for (int i = 0; i < totalVerticesColoridos; i++)
    {
        if (verticesColoridos[i] == vertice)
        {
            coresAtribuidas[i] = cor;
            return;
        }
    }
    
    // Se não foi colorido, adiciona novo
    if (totalVerticesColoridos < MAX_VERTICES_COLORACAO)
    {
        verticesColoridos[totalVerticesColoridos] = vertice;
        coresAtribuidas[totalVerticesColoridos] = cor;
        totalVerticesColoridos++;
    }
}

// Função para verificar se uma cor é válida para um vértice
int corValida(pDGrafo grafo, pVertice vertice, int cor)
{
    if (!vertice || !grafo || !grafo->listaVertices)
    {
        return 1; // Sem adjacências, qualquer cor é válida
    }

    // Em um grafo dirigido, para coloração, dois vértices devem ter cores diferentes
    // se há uma aresta entre eles em QUALQUER direção
    
    // 1. Verifica adjacências de saída (vértices que este vértice aponta)
    if (vertice->listaAdjacencias)
    {
        pNoh atual = vertice->listaAdjacencias->primeiro;
        while (atual != NULL)
        {
            pVertice adjacente = (pVertice)atual->info;
            
            if (adjacente)
            {
                int corAdjacente = obterCorVertice(adjacente);
                
                // Se o adjacente tem a mesma cor, é inválida
                if (corAdjacente == cor)
                {
                    return 0;
                }
            }
            
            atual = atual->prox;
        }
    }
    
    // 2. Verifica adjacências de entrada (vértices que apontam para este vértice)
    pNoh atualVertice = grafo->listaVertices->primeiro;
    while (atualVertice != NULL)
    {
        pVertice outroVertice = (pVertice)atualVertice->info;
        
        if (outroVertice && outroVertice != vertice && outroVertice->listaAdjacencias)
        {
            // Verifica se outroVertice aponta para nosso vértice
            pNoh atualAdj = outroVertice->listaAdjacencias->primeiro;
            while (atualAdj != NULL)
            {
                pVertice adjacente = (pVertice)atualAdj->info;
                
                if (adjacente == vertice)
                {
                    // outroVertice aponta para nosso vértice
                    int corOutroVertice = obterCorVertice(outroVertice);
                    
                    if (corOutroVertice == cor)
                    {
                        return 0; // Cor inválida
                    }
                    break;
                }
                
                atualAdj = atualAdj->prox;
            }
        }
        
        atualVertice = atualVertice->prox;
    }

    return 1; // Cor válida
}

// Função para colorir o grafo
int coloracao(pDGrafo grafo, FuncaoComparacao fc)
{
    // Verifica se o grafo é nulo ou se não tem vértices
    if (!grafo || !grafo->listaVertices || grafo->listaVertices->quantidade == 0)
    {
        return 0;
    }

    // Inicializa o sistema de coloração
    inicializarColoracao();

    // Obtém o total de vértices
    int totalVertices = grafo->listaVertices->quantidade;
    int maxCores = 0;

    // Percorre cada vértice do grafo
    for (int pos = 1; pos <= totalVertices; pos++)
    {
        pVertice vertice = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        if (!vertice)
            continue;

        // Tenta encontrar uma cor válida (começando pela cor 1)
        int cor = 1;
        int corEncontrada = 0;

        while (cor <= totalVertices && !corEncontrada)
        {
            if (corValida(grafo, vertice, cor))
            {
                // Define a cor do vértice
                definirCorVertice(vertice, cor);
                
                // Atualiza o número máximo de cores usado
                if (cor > maxCores)
                {
                    maxCores = cor;
                }
                
                corEncontrada = 1;
            }
            else
            {
                cor++;
            }
        }
        
        // Se não encontrou cor válida, há um problema
        if (!corEncontrada)
        {
            return 0; // Falha na coloração
        }
    }

    // Retorna o número máximo de cores usadas
    return maxCores;
}

#endif