#ifndef BUSCA_AMPLITUDE_H
#define BUSCA_AMPLITUDE_H

/* --------------------------- */
void buscaAmplitude(pDGrafo grafo, FuncaoComparacao fc, FuncaoImpressao fi){
    
    if (grafo == NULL || grafo->listaVertices == NULL || fi == NULL) 
        return;
    
    if (grafo->listaVertices->quantidade == 0) 
        return;
    
    pDLista visitados = criarLista();
    pDLista fila = criarLista();
    
    pNoh atual = grafo->listaVertices->primeiro;
    
    while (atual != NULL) {
        pVertice v = (pVertice)atual->info;
        
        if (contemInfo(visitados, v, fc) == 0) {
            incluirInfo(fila, v);
            incluirInfo(visitados, v);
            
            while (fila->quantidade > 0) {
                pVertice verticeAtual = (pVertice)fila->primeiro->info;
                excluirInfo(fila, verticeAtual, fc);
                
                fi(verticeAtual);
                
                if (verticeAtual->listaAdjacencias != NULL) {
                    pNoh adjAtual = verticeAtual->listaAdjacencias->primeiro;
                    while (adjAtual != NULL) {
                        pVertice vizinho = (pVertice)adjAtual->info;
                        if (contemInfo(visitados, vizinho, fc) == 0) {
                            incluirInfo(fila, vizinho);
                            incluirInfo(visitados, vizinho);
                        }
                        adjAtual = adjAtual->prox;
                    }
                }
            }
        }
        atual = atual->prox;
    }
}
#endif
