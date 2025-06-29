#ifndef EXISTE_CAMINHO_EULERIANO_H
#define EXISTE_CAMINHO_EULERIANO_H

// Função auxiliar para calcular o grau de saída de um vértice (out-degree)
int calcularGrauSaida(pVertice vertice)
{
    if (!vertice || !vertice->listaAdjacencias)
    {
        return 0;
    }
    return vertice->listaAdjacencias->quantidade;
}

// Função auxiliar para calcular o grau de entrada de um vértice (in-degree)
int calcularGrauEntrada(pDGrafo grafo, pVertice verticeAlvo, FuncaoComparacao fc)
{
    int grauEntrada = 0;
    int totalVertices = grafo->listaVertices->quantidade;
    
    // Percorre todos os vértices do grafo
    for (int pos = 1; pos <= totalVertices; pos++)
    {
        pVertice verticeAtual = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        if (verticeAtual && verticeAtual->listaAdjacencias)
        {
            // Verifica se este vértice tem uma aresta para o vértice alvo
            pNoh atual = verticeAtual->listaAdjacencias->primeiro;
            while (atual != NULL)
            {
                pVertice adjacente = (pVertice)atual->info;
                if (fc(adjacente, verticeAlvo) == 0)
                {
                    grauEntrada++;
                }
                atual = atual->prox;
            }
        }
    }
    
    return grauEntrada;
}

// Função para verificar se existe caminho euleriano em grafo dirigido
int existeCaminhoEuleriano(pDGrafo grafo, FuncaoComparacao fc)
{
    // Verifica se o grafo é nulo ou se não tem vértices
    if (!grafo || !grafo->listaVertices || grafo->listaVertices->quantidade == 0)
    {
        return 0;
    }

    // Verifica se o grafo é conexo (para grafos dirigidos, seria fracamente conexo)
    if (!grafoConexo(grafo, fc))
    {
        return 0;
    }

    int totalVertices = grafo->listaVertices->quantidade;
    int verticesComGrauSaidaMaior = 0;    // grau_saída = grau_entrada + 1
    int verticesComGrauEntradaMaior = 0;  // grau_entrada = grau_saída + 1
    int verticesComGrausIguais = 0;       // grau_entrada = grau_saída

    // Analisa cada vértice
    for (int pos = 1; pos <= totalVertices; pos++)
    {
        pVertice vertice = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        if (vertice)
        {
            int grauSaida = calcularGrauSaida(vertice);
            int grauEntrada = calcularGrauEntrada(grafo, vertice, fc);
            
            if (grauSaida == grauEntrada + 1)
            {
                verticesComGrauSaidaMaior++;
            }
            else if (grauEntrada == grauSaida + 1)
            {
                verticesComGrauEntradaMaior++;
            }
            else if (grauEntrada == grauSaida)
            {
                verticesComGrausIguais++;
            }
            else
            {
                // Se algum vértice não se encaixa nas condições, não há caminho euleriano
                return 0;
            }
        }
    }

    // Condições para caminho euleriano em grafo dirigido:
    // 1. Todos os vértices têm grau_entrada = grau_saída (ciclo euleriano)
    // 2. Exatamente 1 vértice com grau_saída = grau_entrada + 1 (início),
    //    exatamente 1 vértice com grau_entrada = grau_saída + 1 (fim),
    //    e todos os outros com grau_entrada = grau_saída
    
    if (verticesComGrausIguais == totalVertices)
    {
        return 1; // Ciclo euleriano
    }
    else if (verticesComGrauSaidaMaior == 1 && 
             verticesComGrauEntradaMaior == 1 && 
             verticesComGrausIguais == totalVertices - 2)
    {
        return 1; // Caminho euleriano
    }
    
    return 0;
}

#endif