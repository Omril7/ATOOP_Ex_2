#include <iostream>
#include "Graph.h"
#include "Ex2.h"
#include <cstring>
#include <array>

struct Trio {
    char type;
    string src;
    string dest;
    double weight;
};
vector<Trio> getFromFile(string fileName) {
    vector<Trio> edges;
    if(fileName[0] == 'b') {
        // add input_files[i] to busGraph
    }
    if(fileName[0] == 't') {
        // add input_files[i] to tramGraph
    }
    if(fileName[0] == 's') {
        // add input_files[i] to sprinterGraph
    }
    if(fileName[0] == 'r') {
        // add input_files[i] to railGraph
    }
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

    /*
     * SET INPUT FILES HERE
     */
    for(int i=0; i<static_cast<int>(input_files.size()); i++) {
        vector<Trio> temp = getFromFile(input_files[i]);
        for(int j=0; j<static_cast<int>(temp.size()); j++) {
            if(temp[j].type == 'b') {
                busGraph.addEdge(temp[j].src, temp[j].dest, temp[j].weight);
            }
            if(temp[j].type == 't') {
                tramGraph.addEdge(temp[j].src, temp[j].dest, temp[j].weight);
            }
            if(temp[j].type == 's') {
                sprinterGraph.addEdge(temp[j].src, temp[j].dest, temp[j].weight);
            }
            if(temp[j].type == 'r') {
                railGraph.addEdge(temp[j].src, temp[j].dest, temp[j].weight);
            }
        }
    }

    busGraph.addEdge("LagoonSouth", "LagoonNorth", 34);
    busGraph.addEdge("LagoonNorth", "LagoonSouth", 36);

    tramGraph.addEdge("CanibalCove", "PiccaninnyPlains", 4);
    tramGraph.addEdge("PiccaninnyPlains", "Neverseas", 3);
    tramGraph.addEdge("Neverseas", "CSPiccaninnyMain", 4);
    tramGraph.addEdge("CSPiccaninnyMain", "NeverlandPlains", 3);
    tramGraph.addEdge("NeverlandPlains", "PixieHollow", 5);
    tramGraph.addEdge("PixieHollow", "MazeOfRegrets", 4);
    tramGraph.addEdge("MazeOfRegrets", "NeverpeakMountain", 7);
    tramGraph.addEdge("NeverpeakMountain", "CanibalCove", 8);

    sprinterGraph.addEdge("LagoonEast", "LagoonWest", 12);
    sprinterGraph.addEdge("LagoonWest", "LagoonEast", 12);

    railGraph.addEdge("LagoonSouth", "LagoonWest", 6);
    railGraph.addEdge("LagoonWest", "LagoonSouth", 7);
    railGraph.addEdge("LagoonSouth", "LagoonEast", 8);
    railGraph.addEdge("LagoonEast", "LagoonSouth", 9);
    railGraph.addEdge("LagoonNorth", "LagoonWest", 15);
    railGraph.addEdge("LagoonWest", "LagoonNorth", 14);
    railGraph.addEdge("LagoonNorth", "LagoonEast", 17);
    railGraph.addEdge("LagoonEast", "LagoonNorth", 16);

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
                cout << "now loaded file: " << params[0] << endl;
//                if(loaded) {
//                    cout << "Update was successful." << endl;
//                }
//                else {
//                    cerr << "ERROR opening the specified file." << endl;
//                }
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
                    cout << "now multiExpress: " << params[0] << " " << params[1] << endl;
                }
            }
        }
        else if(command == "print") {
            out << busGraph << endl << tramGraph << endl << sprinterGraph << endl << railGraph << endl;
            cout << "printing to " << output << " the graph" << endl;
        }
        else if(command != "EXIT"){
            cerr << command  << " is not an option!" << endl;
        }
        iss.clear();
    }
    return 0;
}

