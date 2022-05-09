#include <iostream>
#include "Graph.h"
#include "Ex2.h"
#include <cstring>

int main(int argc, char** argv) {
    /*
     * argv[1] = config.dat
     */
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

    Ex2 *ex2 = new Ex2(config);
    Graph<int> busGraph(ex2->getTT(), ex2->getWT().bus);
    Graph<int> tramGraph(ex2->getTT(), ex2->getWT().tram);
    Graph<int> sprinterGraph(ex2->getTT(), ex2->getWT().sprinter);
    Graph<int> railGraph(ex2->getTT(), ex2->getWT().rail);

    busGraph.printTT();


}


