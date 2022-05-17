//
// Created by Omri Leizerovitch on 05/07/2022.
//

#include <queue>
#include <array>
#include "Graph.h"

enum{INF = 999999};

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
bool Graph::containEdge(const string& src, const string& dest) const {
    if(containVertex(src) && containVertex(dest)) {
        int i = getVertexIndex(src);
        return graph[i].containEdge(dest);
    }
    return false;
}
void Graph::addEdge(const string& src, const string& dest, double w) {
    int i;
    if(!containEdge(src, dest)) {
        addVertex(src);
        addVertex(dest);
        i = getVertexIndex(src);
        graph[i].addEdge(dest, w);
    }
    else { // if contains that edge - set min_weight{graph[src][dest].w, w}
        i = graph[getVertexIndex(src)].getIndex(dest);
        if((graph[getVertexIndex(src)].getAdj())[i].weight > w) {
            graph[getVertexIndex(src)].addEdge(dest, w);
        }
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
    Graph* rev = new Graph(tt, graphType, waiting_t);
    for(auto & i : graph) {
        for(int j=0; j<static_cast<int>(i.getAdj().size()); j++) {
            rev->addEdge(i.getAdj()[j].dest, i.getName(), i.getAdj()[j].weight);
        }
    }
    return *rev;
}

bool Graph::load(string filename) {
    int count;
    string src, dest;
    double w;
    string buffer, word;
    stringstream ss;
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "ERROR opening the specified file." << endl;
        return false;
    }
    while(getline(ifs, buffer, '\n')) {
        count = 0;
        ss.clear();
        ss.str(buffer);
        while(ss >> word && count < 3) {
            if(count == 0) {
                src = word;
            }
            if(count == 1) {
                dest = word;
            }
            if(count == 2) {
                std::istringstream(word) >> w;
            }
            count++;
        }
        addEdge(src, dest, w);
    }
    return true;
}
void Graph::outBound(string src) {
    if(graph.empty() || !containVertex(src)) {
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
            if(!graph[getVertexIndex(adj.dest)].isVisited()) {
                count++;
                graph[getVertexIndex(adj.dest)].changeVisit(true);
                cout << adj.dest << '\t';
                queue.push_back(graph[getVertexIndex(adj.dest)]);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel" << endl;
    }
    cout << endl;
    for(auto & i : graph) {
        i.changeVisit(false);
    }
} // BFS
void Graph::inBound(string dest) {
    if(graph.empty() || !containVertex(dest)) {
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
            if(!revGraph.graph[getVertexIndex(adj.dest)].isVisited()) {
                count++;
                revGraph.graph[getVertexIndex(adj.dest)].changeVisit(true);
                cout << adj.dest << '\t';
                queue.push_back(revGraph.graph[getVertexIndex(adj.dest)]);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel";
    }
    cout << endl;
    for(auto & i : graph) {
        i.changeVisit(false);
    }
} // rev BFS
void Graph::uniExpress(string src, string dest) {
    if(graph.empty() || !containVertex(src) || !containVertex(dest)) {
        cout << graphType << ": " << "route unavailable" << endl;
        return;
    }

    typedef pair<double,string> iPair;
    auto Predicate = [](iPair& a, iPair& b) {return a.first < b.first;};
    priority_queue<iPair,vector<iPair>, decltype(Predicate)> pq(Predicate);

    int n = static_cast<int>(graph.size());
    vector<double> dist(n);
    for(int i=0; i<n; i++) {
        dist[i] = INF;
    } // init to INF

    pq.push(make_pair(0,src));
    dist[getVertexIndex(src)] = 0;

    while(!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        for(int i=0; i<static_cast<int>(graph[getVertexIndex(u)].getAdj().size()); i++) {
            string v = (graph[getVertexIndex(u)].getAdj())[i].dest;
            double w = (graph[getVertexIndex(u)].getAdj())[i].weight;

            if(dist[getVertexIndex(v)] > dist[getVertexIndex(u)] + w + waiting_t) {
                dist[getVertexIndex(v)] = dist[getVertexIndex(u)] + w + waiting_t;
                pq.push(make_pair(dist[getVertexIndex(v)], v));
            }
        }
    }
    if(dist[getVertexIndex(dest)] == INF) {
        cout << graphType << ": " << "route unavailable" << endl;
        return;
    }
    cout << graphType << ": " << dist[getVertexIndex(dest)]-waiting_t << endl;

} // shortest path (Dijkstra)
void Graph::multiExpress(string src, string dest) {
    if(graph.empty() || !containVertex(src) || !containVertex(dest)) {
        cout << graphType << ": " << "route unavailable" << endl;
        return;
    }

    typedef pair<double,string> iPair;
    auto Predicate = [](iPair& a, iPair& b) {return a.first < b.first;};
    priority_queue<iPair,vector<iPair>, decltype(Predicate)> pq(Predicate);

    int n = static_cast<int>(graph.size());
    vector<double> dist(n);
    for(int i=0; i<n; i++) {
        dist[i] = INF;
    } // init to INF

    pq.push(make_pair(0,src));
    dist[getVertexIndex(src)] = 0;

    while(!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        for(int i=0; i<static_cast<int>(graph[getVertexIndex(u)].getAdj().size()); i++) {
            string v = (graph[getVertexIndex(u)].getAdj())[i].dest;
            double w = (graph[getVertexIndex(u)].getAdj())[i].weight;
            int Vtt = graph[getVertexIndex(v)].getTT();
            if(dist[getVertexIndex(v)] > dist[getVertexIndex(u)] + w + Vtt) {
                dist[getVertexIndex(v)] = dist[getVertexIndex(u)] + w + Vtt;
                pq.push(make_pair(dist[getVertexIndex(v)], v));
            }
        }
    }
    if(dist[getVertexIndex(dest)] == INF) {
        cout << graphType << ": " << "route unavailable" << endl;
        return;
    }
    cout << "Shortest path length: " << dist[getVertexIndex(dest)]-graph[getVertexIndex(src)].getTT() << endl;

}

// shortest path (Dijkstra)
