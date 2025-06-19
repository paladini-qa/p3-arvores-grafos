#ifndef COLORACAO_H
#define COLORACAO_H



#define MAX_CORES 100


typedef struct {
    void* verticeInfo;
    int cor;
} VerticeColorido;

VerticeColorido coresVertices[MAX_CORES];
int numVerticesColoridos = 0;
int obterCorVertice(void* verticeInfo, FuncaoComparacao fc) {
    for (int i = 0; i < numVerticesColoridos; i++) {
        if (fc(coresVertices[i].verticeInfo, verticeInfo) == 0) {
            return coresVertices[i].cor;
        }
    }
    return -1;
}


void definirCorVertice(void* verticeInfo, int cor) {
    if (numVerticesColoridos < MAX_CORES) {
        coresVertices[numVerticesColoridos].verticeInfo = verticeInfo;
        coresVertices[numVerticesColoridos].cor = cor;
        numVerticesColoridos++;
    }
}

int corValida(pDGrafo grafo, void* verticeInfo, int cor, FuncaoComparacao fc) {
    pVertice vertice = buscarVertice(grafo, verticeInfo, fc);
    if (!vertice || !vertice->listaAdjacencias) {
        return 1;
    }
    for (int pos = 1; pos <= vertice->listaAdjacencias->quantidade; pos++) {
        pVertice adjacente = (pVertice)buscarInfoPos(vertice->listaAdjacencias, pos);
        if (adjacente) {
            int corAdjacente = obterCorVertice(adjacente->info, fc);
            if (corAdjacente == cor) {
                return 0;
            }
        }
    }
    
    return 1;
}

int coloracao(pDGrafo grafo, FuncaoComparacao fc) {
    if (!grafo || !grafo->listaVertices || grafo->listaVertices->quantidade == 0) {
        return 0;
    }
    
    numVerticesColoridos = 0;
    
    int totalVertices = grafo->listaVertices->quantidade;
    int maxCores = 0;
    for (int pos = 1; pos <= totalVertices; pos++) {
        pVertice vertice = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        if (!vertice) continue;
        
        int cor = 1;
        while (cor <= totalVertices) {
            if (corValida(grafo, vertice->info, cor, fc)) {
                definirCorVertice(vertice->info, cor);
                if (cor > maxCores) {
                    maxCores = cor;
                }
                break;
            }
            cor++;
        }
    }
    
    return maxCores;
}

#endif 