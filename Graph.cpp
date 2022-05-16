//
// Created by Omri Leizerovitch on 05/07/2022.
//

#include "Graph.h"

bool Graph::containVertex(const string& v) const {
    for(auto & i : graph) {
        if(i.getName() == v) {
            return true;
        }
    }
    return false;
}
void Graph::addVertex(string v) {
    if(!containVertex(v)) { // v is not in graph
        if(v[0] == 'I' && v[1] == 'C') { // intercity
            graph.push_back(Intercity(v, tt.intercity));
        }
        if(v[0] == 'C' && v[1] == 'S') { // centraal
            graph.push_back(Centraal(v, tt.centraal));
        }
        else { // stad
            graph.push_back(Stad(v, tt.stad));
        }
    }
}
bool Graph::containEdge(const string& src, const string& dest, double w) const {
    if(containVertex(src) && containVertex(dest)) {
        int i = getVertexIndex(src);
        return graph[i].containEdge(dest, w);
    }
    return false;
}
void Graph::addEdge(const string& src, const string& dest, double w) {
    if(!containEdge(src, dest, w)) {
        addVertex(src);
        addVertex(dest);
        int i = getVertexIndex(src);
        graph[i].addEdge(dest, w, tt);
    }
}

int Graph::getVertexIndex(const string& v) const {
    for(int i=0; i< static_cast<int>(graph.size()); i++) {
        if(graph[i].getName() == v) {
            return i;
        }
    }
    return -1;
}
Graph& Graph::getReverse() {
    Graph rev(tt, graphType, stop_t);
    for(auto & i : graph) {
        for(int j=0; j<static_cast<int>(i.getAdj().size()); j++) {
            rev.addEdge(i.getAdj()[j].dest->getName(), i.getName(), i.getAdj()[j].weight);
        }
    }
    return rev;
}

void Graph::outBound(string src) {
    if(graph.empty()) {
        cout << graphType << ": " << "no outbound travel" << endl;
        return;
    }
    cout << graphType << ": ";
    int count = 0;
    list<Station> queue;
    graph[getVertexIndex(src)].changeVisit(true);
    queue.push_back(graph[getVertexIndex(src)]);
    while(!queue.empty()) {
        src = queue.front().getName();
        queue.pop_front();
        for(auto adj : graph[getVertexIndex(src)].getAdj()) {
            if(!adj.dest->isVisited()) {
                count++;
                adj.dest->changeVisit(true);
                cout << adj.dest->getName() << '\t';
                queue.push_back(*adj.dest);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel" << endl;
    }
    for(auto & i : graph) {
        i.changeVisit(false);
    }
} // BFS
void Graph::inBound(string dest) {
    if(graph.empty()) {
        cout << graphType << ": " << "no outbound travel" << endl;
        return;
    }
    Graph revGraph = getReverse();

    cout << graphType << ": ";
    int count = 0;
    list<Station> queue;
    revGraph.graph[getVertexIndex(dest)].changeVisit(true);
    queue.push_back(revGraph.graph[getVertexIndex(dest)]);
    while(!queue.empty()) {
        dest = queue.front().getName();
        queue.pop_front();
        for(auto adj : revGraph.graph[getVertexIndex(dest)].getAdj()) {
            if(!adj.dest->isVisited()) {
                count++;
                adj.dest->changeVisit(true);
                cout << adj.dest->getName() << '\t';
                queue.push_back(*adj.dest);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel" << endl;
    }
    for(auto & i : graph) {
        i.changeVisit(false);
    }
} // rev BFS
void Graph::uniExpress(string src, string dest) {
    if(graph.empty()) {
        cout << graphType << ": " << "no outbound travel" << endl;
        return;
    }
} // shortest path (Dijkstra)
void Graph::multiExpress(string src, string dest) {
    if(graph.empty()) {
        cout << graphType << ": " << "no outbound travel" << endl;
        return;
    }
} // shortest path (Dijkstra)
void Graph::print() {
    cout << graphType << " graph: " << endl;
    for(int i=0; i<static_cast<int>(graph.size()); i++) {
        cout << '\t' << graph[i].getName() << " : ";
        for(int j=0; j<static_cast<int>(graph[i].getAdj().size()); j++) {
            cout << (graph[i].getAdj())[j].dest->getName() << endl;
        }
    }
}


// V needs V& operator=(const V& v) method
// E needs E& operator=(const E& e) method   -> maybe
// E needs V getVertex() const method
// V needs bool containEdge(V dest, double w) method
// V needs void addEdge(V dest, double w) method
// V needs void changeVisit(bool b) method
// V needs vector<E> getAdj() const method

// V needs bool isVisited() const method
// V needs string getName() const method

// E needs pointers to V in graph,
// because when we change in graph the V in E needs to adjust


/*
 * NEED TO SET DEFAULT PARAMETERS FOR VERTICES AND EDGES TO SEE IF CODE OK
 */