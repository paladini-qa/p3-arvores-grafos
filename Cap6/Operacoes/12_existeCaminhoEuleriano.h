#ifndef EXISTE_CAMINHO_EULERIANO_H
#define EXISTE_CAMINHO_EULERIANO_H


int calcularGrauVertice(pVertice vertice) {
    if (!vertice || !vertice->listaAdjacencias) {
        return 0;
    }
    return vertice->listaAdjacencias->quantidade;
}


int existeCaminhoEuleriano(pDGrafo grafo, FuncaoComparacao fc) {
    if (!grafo || !grafo->listaVertices || grafo->listaVertices->quantidade == 0) {
        return 0;
    }
    

    if (!grafoConexo(grafo, fc)) {
        return 0;
    }
    
    int verticesGrauImpar = 0;
    int totalVertices = grafo->listaVertices->quantidade;
    

    for (int pos = 1; pos <= totalVertices; pos++) {
        pVertice vertice = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        if (vertice) {
            int grau = calcularGrauVertice(vertice);
            if (grau % 2 == 1) {
                verticesGrauImpar++;
            }
        }
    }
    

    
    return (verticesGrauImpar == 0 || verticesGrauImpar == 2) ? 1 : 0;
}

#endif 