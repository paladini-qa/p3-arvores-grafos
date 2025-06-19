#ifndef GRAFO_CONEXO_H
#define GRAFO_CONEXO_H


int grafoConexo(pDGrafo grafo, FuncaoComparacao fc) {
    if (!grafo || !grafo->listaVertices || grafo->listaVertices->quantidade <= 1) {
        return 1;
    }
    
    int totalVertices = grafo->listaVertices->quantidade;
    

    pVertice primeiroVertice = (pVertice)buscarInfoPos(grafo->listaVertices, 1);
    if (!primeiroVertice) return 0;
    

    for (int pos = 2; pos <= totalVertices; pos++) {
        pVertice verticeDestino = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        if (!verticeDestino) continue;
        

        if (!existeCaminho(grafo, primeiroVertice->info, verticeDestino->info, fc)) {
            return 0;
        }
    }
    
    return 1;
}

#endif 