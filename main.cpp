#include <iostream>
#include "Driver.h"

using namespace std;

int main(int argc, char **argv) {

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

    return 0;
}
