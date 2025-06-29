#ifndef EXCLUIR_ARESTA_H
#define EXCLUIR_ARESTA_H

/* --------------------------- */
void excluirAresta(pDGrafo grafo, void *vOrig, void *vDest, FuncaoComparacao fc)
{

    if (grafo == NULL || grafo->listaVertices == NULL)
        return;

    pVertice vOrigem = buscarVertice(grafo, vOrig, fc);
    pVertice vDestino = buscarVertice(grafo, vDest, fc);

    if (vOrigem == NULL || vDestino == NULL)
        return;

    // Para grafo dirigido, excluir aresta apenas na direção especificada
    excluirInfo(vOrigem->listaAdjacencias, vDestino, fc);
}

#endif
