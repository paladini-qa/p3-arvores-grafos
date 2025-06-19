#ifndef GRAFO_BIPARTIDO_H
#define GRAFO_BIPARTIDO_H

int grafoBipartido(pDGrafo grafo, FuncaoComparacao fc) {
    if (grafo == NULL || grafo->listaVertices == NULL || grafo->listaVertices->quantidade == 0) {
        return 1;
    }

    pDLista vertices = grafo->listaVertices;
    pNoh atual = vertices->primeiro;

    int cores[1000];
    int visitados[1000];
    
    for (int i = 0; i < 1000; i++) {
        cores[i] = -1;
        visitados[i] = 0;
    }

    while (atual != NULL) {
        pVertice v = (pVertice)atual->info;
        int idVertice = *((int*)v->info);
        
        if (!visitados[idVertice]) {
            pDLista fila = criarLista();
            incluirInfo(fila, v);
            cores[idVertice] = 0;
            visitados[idVertice] = 1;

            while (fila->quantidade > 0) {
                pVertice verticeAtual = (pVertice)fila->primeiro->info;
                excluirInfo(fila, verticeAtual, fc);
                
                int idAtual = *((int*)verticeAtual->info);
                
                pNoh adjAtual = verticeAtual->listaAdjacencias->primeiro;
                while (adjAtual != NULL) {
                    pVertice vizinho = (pVertice)adjAtual->info;
                    int idVizinho = *((int*)vizinho->info);
                    
                    if (!visitados[idVizinho]) {
                        cores[idVizinho] = 1 - cores[idAtual];
                        visitados[idVizinho] = 1;
                        incluirInfo(fila, vizinho);
                    }
                    else if (cores[idVizinho] == cores[idAtual]) {
                        return 0;
                    }
                    
                    adjAtual = adjAtual->prox;
                }
            }
        }
        atual = atual->prox;
    }
    
    return 1;
}

#endif 