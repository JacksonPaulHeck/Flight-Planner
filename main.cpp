#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include "Driver.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc <= 1){
        Catch::Session().run();
        return 0;
    }
    ifstream data(argv[1]);
    ifstream input(argv[2]);
    ofstream output(argv[3]);

    JPLinkedList<JPLinkedList<Cities> *> JPAdjList;
    JPVector<JPVector<JPString>> outputList;
    JPVector<Cities> requestedRoutes;
    JPStack jpStack;

    parseRequested(requestedRoutes, input);

    parseInputFile(JPAdjList, data);

    getOutput(JPAdjList, requestedRoutes, outputList, output, jpStack, data);

    data.close();
    input.close();
    output.close();
    return 0;
}

