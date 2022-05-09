//
// Created by omril on 05/07/2022.
//

#include "Graph.h"
template <class V>
void Graph<V>::addVertex(const V& v) {
    int i = getVertexIndex(v);
    if(i < 0) {
        graph.push_back(v);
    }
}
template <class V>
void Graph<V>::addEdge(V src, V dest, int w) {
    addVertex(src);
    addVertex(dest);
    int i = getVertexIndex(src);
    graph[i].addAdj(dest, w);
}

template <class V>
int Graph<V>::getVertexIndex(V v) {
    for(int i=0; i< static_cast<int>(graph.size()); i++) {
        if(graph[i] == v) {
            return i;
        }
    }
    return -1;
}



// V needs addAdj(V v, int w) method