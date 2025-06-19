#ifndef EXCLUIR_VERTICE_H
#define EXCLUIR_VERTICE_H

/* --------------------------- */
void excluirVertice(pDGrafo grafo, void* info, FuncaoComparacao fc){
    
    if (grafo == NULL || grafo->listaVertices == NULL || fc == NULL) 
        return;
    
    pVertice vertice = buscarVertice(grafo, info, fc);
    if (vertice == NULL) 
        return;
    
    pNoh atual = grafo->listaVertices->primeiro;
    while (atual != NULL) {
        pVertice v = (pVertice)atual->info;
        if (v != vertice && v->listaAdjacencias != NULL) {
            excluirInfo(v->listaAdjacencias, vertice, fc);
            if (v->grau > 0) v->grau--;
        }
        atual = atual->prox;
    }
    
    excluirInfo(grafo->listaVertices, vertice, fc);
}
#endif
