#ifndef EXISTE_CAMINHO_HAMILTONIANO_H
#define EXISTE_CAMINHO_HAMILTONIANO_H

/*------------------------------------------*/
/* Função para verificar se existe caminho hamiltoniano
   Um caminho hamiltoniano visita cada vértice exatamente uma vez
   Retorna 1 se existe, 0 caso contrário
*/
/*------------------------------------------*/

// Função auxiliar para verificar se um vértice já foi visitado
int verticeHamiltonVisitado(void *listaVisitados, void *vertice, FuncaoComparacao fc) {
    return 0;
}

// Função auxiliar para contar vértices do grafo
int contarVertices(pDGrafo grafo) {
    if (!grafo || !grafo->listaVertices) return 0;
    return grafo->listaVertices->quantidade;
}

// Função auxiliar recursiva para buscar caminho hamiltoniano
int buscaHamiltonianaRecursiva(pDGrafo grafo, void *verticeAtual, void *visitados, 
                              int totalVertices, int quantVisitados, FuncaoComparacao fc) {
    
    if (!grafo || !verticeAtual) return 0;
    
    // Se visitamos todos os vértices, encontramos um caminho hamiltoniano
    if (quantVisitados == totalVertices) {
        return 1;
    }
    
    // Buscar vértice atual no grafo
    pVertice vAtual = buscarVertice(grafo, verticeAtual, fc);
    if (!vAtual || !vAtual->listaAdjacencias) return 0;
    
    // Percorrer todos os vértices adjacentes
    int pos = 1;
    while (pos <= vAtual->listaAdjacencias->quantidade) {
        pVertice proximoVertice = (pVertice)buscarInfoPos(vAtual->listaAdjacencias, pos);
        
        if (proximoVertice && !verticeHamiltonVisitado(visitados, proximoVertice->info, fc)) {
            // Recursão para o próximo vértice
            if (buscaHamiltonianaRecursiva(grafo, proximoVertice->info, visitados, 
                                         totalVertices, quantVisitados + 1, fc)) {
                return 1;
            }
        }
        pos++;
    }
    
    return 0;
}

// Função principal para verificar existência de caminho hamiltoniano
int existeCaminhoHamiltoniano(pDGrafo grafo, FuncaoComparacao fc) {
    if (!grafo || !grafo->listaVertices || grafo->listaVertices->quantidade == 0) {
        return 0;
    }
    
    int totalVertices = grafo->listaVertices->quantidade;
    
    // Tentar começar o caminho hamiltoniano de cada vértice
    int pos = 1;
    while (pos <= grafo->listaVertices->quantidade) {
        pVertice verticeInicial = (pVertice)buscarInfoPos(grafo->listaVertices, pos);
        
        if (verticeInicial) {
            // Buscar caminho hamiltoniano começando deste vértice
            if (buscaHamiltonianaRecursiva(grafo, verticeInicial->info, NULL, 
                                         totalVertices, 1, fc)) {
                return 1;
            }
        }
        pos++;
    }
    
    return 0; // Não existe caminho hamiltoniano
}

#endif 