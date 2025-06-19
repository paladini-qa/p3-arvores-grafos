#ifndef EXCLUIR_ARESTA_H
#define EXCLUIR_ARESTA_H

/* --------------------------- */
void excluirAresta(pDGrafo grafo, void *vOrig, void *vDest, FuncaoComparacao fc){
    
    if (grafo == NULL || grafo->listaVertices == NULL) 
        return;
    
    pVertice vOrigem = buscarVertice(grafo, vOrig, fc);
    pVertice vDestino = buscarVertice(grafo, vDest, fc);
    
    if (vOrigem == NULL || vDestino == NULL) 
        return;
    
    excluirInfo(vOrigem->listaAdjacencias, vDestino, fc);
    
    vOrigem->grau--;
    if (vDestino->grau > 0)
        vDestino->grau--;
}

#endif
