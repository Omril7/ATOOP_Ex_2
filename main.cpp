#include <iostream>
#include "Graph.h"
#include "Ex2.h"
#include <cstring>
#include <array>

void MExpress(string src, string dest, Graph bg, Graph tg, Graph sg, Graph rg ){
    Graph qgprah;
    for (auto i : bg.getGraph()) {
        for (auto j : i.getAdj()) {
            qgprah.addEdge(i.getName(), j.dest, j.weight);
        }
    }
    for (auto i : tg.getGraph()) {
        for (auto j : i.getAdj()) {
            qgprah.addEdge(i.getName(), j.dest, j.weight);
        }
    }
    for (auto i : sg.getGraph()) {
        for (auto j : i.getAdj()) {
            qgprah.addEdge(i.getName(), j.dest, j.weight);
        }
    }
    for (auto i : rg.getGraph()) {
        for (auto j : i.getAdj()) {
            qgprah.addEdge(i.getName(), j.dest, j.weight);
        }
    }
    qgprah.multiExpress(src, dest);
}

int main(int argc, char** argv) {
    if(argc < 3) {
        cerr << "Not enough information" << endl;
        exit(-1);
    }
    char* config = nullptr;
    string output = "output.dat";
    std::vector<char*> input_files;
    int i=2;
    while(strcmp(argv[i],"-c") != 0 && strcmp(argv[i],"-o") != 0 && i<argc) {
        input_files.push_back(argv[i]);
        i++;
    }
    while(i<argc) {
        if(strcmp(argv[i],"-c") == 0) {
            config = argv[i+1];
            i += 2;
            continue;
        }
        if(strcmp(argv[i], "-o") == 0) {
            output = argv[i+1];
            i += 2;
            continue;
        }
    }

    ofstream out(output);

    Ex2 *ex2 = new Ex2(config);
    Graph busGraph(ex2->getTT(), "bus", ex2->getWT().bus);
    Graph tramGraph(ex2->getTT(), "tram", ex2->getWT().tram);
    Graph sprinterGraph(ex2->getTT(), "sprinter", ex2->getWT().sprinter);
    Graph railGraph(ex2->getTT(), "rail", ex2->getWT().rail);

    for(int i=0; i<static_cast<int>(input_files.size()); i++) {
        if(!strncmp(input_files[i], "bus", 3)) {
            busGraph.load(input_files[i]);
        }
        if(!strncmp(input_files[i], "tram", 4)) {
            tramGraph.load(input_files[i]);
        }
        if(!strncmp(input_files[i], "sprinter", 8)) {
            sprinterGraph.load(input_files[i]);
        }
        if(!strncmp(input_files[i], "rail", 4)) {
            railGraph.load(input_files[i]);
        }
    }

    string line, command, word;
    string params[2];
    int count;
    while(line != "EXIT") {
        params[0] = "";
        params[1] = "";
        count = 0;
        getline(cin, line);
        istringstream iss(line);
        while(iss >> word) {
            if(count == 0) {
                command = word;
            }
            else {
                params[count-1] = word;
            }
            count++;
        }
        if(command == "load") {
            if(params[0].empty()) {
                cerr << "Not enough information to load.\nPlease try again." << endl;
            }
            else {
                const char* temp = params[0].data();
                if(!strncmp(temp, "bus", 3)) {
                    if(busGraph.load(temp))
                        cout << "Update was successful." << endl;
                }
                else if(!strncmp(temp, "tram", 4)) {
                    if(tramGraph.load(temp))
                        cout << "Update was successful." << endl;
                }
                else if(!strncmp(temp, "sprinter", 8)) {
                    if(sprinterGraph.load(temp))
                        cout << "Update was successful." << endl;
                }
                else if(!strncmp(temp, "rail", 4)) {
                    if(railGraph.load(temp))
                        cout << "Update was successful." << endl;
                }
                else {
                    cerr << "ERROR opening the specified file." << endl;
                }
            }

        }
        else if(command == "outbound") {
            if(params[0].empty()) {
                cerr << "Not enough information to outbound.\nPlease try again." << endl;
            }
            else {
                if(!busGraph.containVertex(params[0]) && !tramGraph.containVertex(params[0])
                && !sprinterGraph.containVertex(params[0]) && !railGraph.containVertex(params[0])) {
                    cerr << params[0] << " does not exist in the current network. \n";
                }
                else {
                    busGraph.outBound(params[0]);
                    tramGraph.outBound(params[0]);
                    sprinterGraph.outBound(params[0]);
                    railGraph.outBound(params[0]);
                }
            }
        }
        else if(command == "inbound") {
            if(params[0].empty()) {
                cerr << "Not enough information to inbound.\nPlease try again." << endl;
            }
            else {
                if(!busGraph.containVertex(params[0]) && !tramGraph.containVertex(params[0])
                   && !sprinterGraph.containVertex(params[0]) && !railGraph.containVertex(params[0])) {
                    cerr << params[0] << " does not exist in the current network. \n";
                }
                else {
                    busGraph.inBound(params[0]);
                    tramGraph.inBound(params[0]);
                    sprinterGraph.inBound(params[0]);
                    railGraph.inBound(params[0]);
                }
            }
        }
        else if(command == "uniExpress") {
            if(params[0].empty() || params[1].empty()) {
                cerr << "Not enough information to uniExpress.\nPlease try again." << endl;
            }
            else {
                if(!busGraph.containVertex(params[0]) && !tramGraph.containVertex(params[0])
                   && !sprinterGraph.containVertex(params[0]) && !railGraph.containVertex(params[0])) {
                    cerr << params[0] << " does not exist in the current network. \n";
                }
                if(!busGraph.containVertex(params[1]) && !tramGraph.containVertex(params[1])
                   && !sprinterGraph.containVertex(params[1]) && !railGraph.containVertex(params[1])) {
                    cerr << params[1] << " does not exist in the current network. \n";
                }
                else {
                    busGraph.uniExpress(params[0], params[1]);
                    tramGraph.uniExpress(params[0], params[1]);
                    sprinterGraph.uniExpress(params[0], params[1]);
                    railGraph.uniExpress(params[0], params[1]);
                }
            }
        }
        else if(command == "multiExpress") {
            if(params[0].empty() || params[1].empty()) {
                cerr << "Not enough information to uniExpress.\nPlease try again." << endl;
            }
            else {
                if(!busGraph.containVertex(params[0]) && !tramGraph.containVertex(params[0])
                   && !sprinterGraph.containVertex(params[0]) && !railGraph.containVertex(params[0])) {
                    cerr << params[0] << " does not exist in the current network. \n";
                }
                if(!busGraph.containVertex(params[1]) && !tramGraph.containVertex(params[1])
                   && !sprinterGraph.containVertex(params[1]) && !railGraph.containVertex(params[1])) {
                    cerr << params[1] << " does not exist in the current network. \n";
                }
                else {
                    MExpress(params[0], params[1], busGraph, tramGraph, sprinterGraph, railGraph);
                }
            }
        }
        else if(command == "print") {
            out << busGraph << endl << tramGraph << endl << sprinterGraph << endl << railGraph << endl;
        }
        else if(command != "EXIT"){
            cerr << command  << " is not an option!" << endl;
        }
        iss.clear();
    }
    return 0;
}