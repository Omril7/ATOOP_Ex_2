//
// Created by omril on 05/07/2022.
//

#include "Graph.h"
template <class V>
void Graph<V>::addVertex(const V& v) {
    if(getVertexIndex(v) < 0) { // v is not in graph
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

template <class V>
void Graph<V>::outBound(V src) {
    cout << graphType << ": ";
    int count = 0;
    list<V> queue;
    graph[getVertexIndex(src)].changeVisit(true);
    queue.push_back(src);
    while(!queue.empty()) {
        src = queue.front();
        queue.pop_front();
        for(auto adj : graph[getVertexIndex(src)].getAdj().getVertex()) {
            if(!adj.isVisited()) {
                count++;
                adj.changeVisit(true);
                cout << adj.getName() << '\t';
                queue.push_back(adj);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel" << endl;
    }
    for(int i=0; i<static_cast<int>(graph.size()); i++) {
        graph[i].changeVisit(false);
    }
} // BFS
template <class V>
void Graph<V>::inBound(V dest) {
    Graph<V> revGraph = getReverse();

    cout << graphType << ": ";
    int count = 0;
    list<V> queue;
    revGraph[getVertexIndex(dest)].changeVisit(true);
    queue.push_back(dest);
    while(!queue.empty()) {
        dest = queue.front();
        queue.pop_front();
        for(auto adj : revGraph[getVertexIndex(dest)].getAdj().getVertex()) {
            if(!adj.isVisited()) {
                count++;
                adj.changeVisit(true);
                cout << adj.getName() << '\t';
                queue.push_back(adj);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel" << endl;
    }
    for(int i=0; i<static_cast<int>(graph.size()); i++) {
        graph[i].changeVisit(false);
    }
} // rev BFS
template <class V>
int Graph<V>::uniExpress(V src, V dest) {} // shortest path (Dijkstra)
template <class V>
int Graph<V>::multiExpress(V src, V dest) {} // shortest path (Dijkstra)
template<class V>
void Graph<V>::print() {
    cout << graphType << ": " << endl;
    for(int i=0; i<static_cast<int>(graph.size()); i++) {
        cout << '\t' << graph[i].getName() << " : " << graph[i].getAdj() << endl;
    }
}


// V needs V& operator=(const V& v) method
// E needs E& operator=(const E& e) method   -> maybe
// V needs void addAdj(V v, int w) method
// V needs void changeVisit(bool b) method
// V needs vector<E> getAdj() const method
// E needs V getVertex() const method
// V needs bool isVisited() const method
// V needs void changeVisit(bool b) method
// V needs string getName() const method

// E needs pointers to V in graph,
// because when we change in graph the V in E needs to adjust
