#include <iostream>
#include "Graph.h"
#include "Ex2.h"
#include <cstring>

int main(int argc, char** argv) {
    /*
     * argv[1] = config.dat
     */
    char* config = nullptr;
    char* output = nullptr;
    std::vector<char*> input_files;
    int i=2;
    while(strcmp(argv[i],"-c") != 0 && strcmp(argv[i],"-o") != 0 && i<argc) {
        input_files.push_back(argv[i]);
        i++;
    }
    if(i<argc) {
        if(strcmp(argv[i],"-c") == 0) {
            config = argv[i+1];
            i++;
        }
        if(strcmp(argv[i], "-o") == 0) {
            output = argv[i+1];
            i++;
        }
    }
    Ex2 *ex2 = new Ex2(config);
    Graph graph(ex2->getWT(), ex2->getTT());
    graph.printWT();
    graph.printTT();


}


d:  e
e:  f
f:  -

d:  -
e:  d
f:  e