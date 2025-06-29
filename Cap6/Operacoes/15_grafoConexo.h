#ifndef GRAFO_CONEXO_H
#define GRAFO_CONEXO_H

// Função para verificar se o grafo é conexo
int grafoConexo(pDGrafo grafo, FuncaoComparacao fc)
{
    // Verifica se o grafo é nulo ou se não tem vértices
    if (!grafo || !grafo->listaVertices || grafo->listaVertices->quantidade <= 1)
    {
        return 1;
    }

    // Obtém o total de vértices
    int totalVertices = grafo->listaVertices->quantidade;

    // Obtém o primeiro vértice
    pVertice primeiroVertice = (pVertice)buscarInfoPos(grafo->listaVertices, 1);
    if (!primeiroVertice)
        return 0;

    // Verifica se existe caminho entre o primeiro vértice e os demais
    for (int pos = 2; pos <= totalVertices; pos++)
    {
        pVertice verticeDestino = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        if (!verticeDestino)
            continue;

        // Verifica se existe caminho entre o primeiro vértice e o vértice destino
        if (!existeCaminho(grafo, primeiroVertice->info, verticeDestino->info, fc))
        {
            return 0;
        }
    }

    return 1;
}

#endif