//
// Created by Omri Leizerovitch on 05/07/2022.
//

#include "Station.h"

bool Station::containEdge(const string& dest) const {
    for(auto i : adjList) {
        if(i.dest == dest) {
            return true;
        }
    }
    return false;
}
void Station::addEdge(string dest, double w) {
    if(!containEdge(dest)) {
        edge e;
        e.dest = dest;
        e.weight = w;
        adjList.push_back(e);
    }
    else {
        adjList[getIndex(dest)].weight = w;
    }
}
int Station::getIndex(string dest) const {
    for(int i=0; i<static_cast<int>(adjList.size()); i++) {
        if(adjList[i].dest == dest) {
            return i;
        }
    }
    return -1;
}