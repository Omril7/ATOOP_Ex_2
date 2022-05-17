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
void Station::addEdge(string dest, double w, Transit_time tt) {
    if(!containEdge(dest)) {
        edge e;
        e.dest = dest;
        e.weight = w;
        adjList.push_back(e);
    }
}