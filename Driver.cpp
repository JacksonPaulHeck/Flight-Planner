//
// Created by jacks on 3/27/2020.
//

#include "Driver.h"
#include <sstream>

void parseRequested(JPLinkedList<Cities> &requestedList, ifstream &inFile) {
    char *line = new char[80];
    char *origin = new char[20];
    char *dest = new char[20];
    char *type = new char[20];

    inFile.getline(line, 80);
    int length = atoi(line);
    for (int i = 0; i < length; i++) {
        inFile.getline(line, 80);
        stringstream ss(line);
        while (!ss.eof()) {
            ss.getline(origin, 20, '|');
            ss.getline(dest, 20, '|');
            ss.getline(type, 20);

            JPString JPOrigin(origin);
            JPString JPDest(dest);
            JPString JPType(type);
            cout << JPType << endl;
            int costBool = false;
            int timeBool = false;
            if (JPType == "C") {
                costBool = true;
            } else {
                timeBool = true;
            }
            Cities requested(JPOrigin, JPDest, costBool, timeBool);
            requestedList.append(requested);

        }
    }
    delete[] line;
    delete[] origin;
    delete[] dest;
    delete[] type;

}

void parseInputFile(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, ifstream &inFile) {
    char *line = new char[80];
    char *origin = new char[20];
    char *dest = new char[20];
    char *cost = new char[20];
    char *time = new char[20];

    inFile.getline(line, 80);
    int length = atoi(line);
    for (int i = 0; i < length; i++) {
        inFile.getline(line, 80);
        stringstream ss(line);
        while (!ss.eof()) {
            ss.getline(origin, 20, '|');
            ss.getline(dest, 20, '|');
            ss.getline(cost, 20, '|');
            ss.getline(time, 20);

            JPString JPOrigin(origin);
            JPString JPDest(dest);
            int c = atoi(cost);
            int t = atoi(time);
            Cities cities_Orig(JPOrigin, JPDest, c, t);
            Cities cities_Dest(JPDest, JPOrigin, c, t);

            if (JPAdjList.length() == 0) {
                emptyList(JPAdjList, cities_Orig, cities_Dest);
            } else {
                JPAdjList.moveCurrToHead();
                bool isOrigin;
                searchInList(JPAdjList, cities_Orig, isOrigin = false);
                JPAdjList.moveCurrToHead();
                bool isDest;
                searchInList(JPAdjList, cities_Dest, isDest = false);
                JPAdjList.moveCurrToHead();
                JPAdjList.getCurrValue()->moveCurrToHead();
                addNewList(JPAdjList, cities_Orig, isOrigin);
                addNewList(JPAdjList, cities_Dest, isDest);
                JPAdjList.moveCurrToRight();
            }
        }
    }

    delete[] line;
    delete[] origin;
    delete[] dest;
    delete[] cost;
    delete[] time;
}

void emptyList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, Cities &cities1, Cities &cities2) {
    auto *jpLinkedList = new JPLinkedList<Cities>;
    jpLinkedList->moveCurrToHead();
    jpLinkedList->insert(cities1);
    JPAdjList.moveCurrToHead();
    JPAdjList.insert(jpLinkedList);
    auto *jpLinkedList1 = new JPLinkedList<Cities>;
    jpLinkedList1->moveCurrToHead();
    jpLinkedList1->insert(cities2);
    JPAdjList.append(jpLinkedList1);
}

void searchInList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, Cities &head, bool &isThere) {
    for (int j = 0; j < JPAdjList.length(); j++) {
        isThere = false;
        JPAdjList.getCurrValue()->moveCurrToHead();
        if (JPAdjList.getCurrValue()->getCurrValue().getOrigin() == head.getOrigin()) {
            JPAdjList.getCurrValue()->moveCurrToHead();
            JPAdjList.getCurrValue()->append(head);
            break;
        } else { isThere = true; }
        JPAdjList.moveCurrToRight();
    }
}

void addNewList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, Cities &head, bool &isThere) {
    if (isThere) {
        auto *jpLinkedList = new JPLinkedList<Cities>;
        jpLinkedList->moveCurrToHead();
        jpLinkedList->insert(head);
        JPAdjList.moveCurrToHead();
        JPAdjList.insert(jpLinkedList);
    }
}

int findHead(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, const JPString &origin) {
    JPIterator<JPLinkedList<Cities> *> *bigList = JPAdjList.getHeadIterator();
    int i = 0;
    while (bigList->nextNode() != NULL) {
        if (bigList->getNode()->data->getCurrValue().getOrigin() == origin) {
            delete bigList;
            return i;
        }
        i++;
    }
    delete bigList;
    return -1;
}

void saveStack(JPLinkedList<JPLinkedList<JPString> *> &outputList, JPStack &jpStack) {
    auto *jpLinkedList = new JPLinkedList(*jpStack.save());
    outputList.insert(jpLinkedList);
}

void iterativeBacktrack(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPStack &jpStack, const Cities &requested,
                        JPLinkedList<JPLinkedList<JPString> *> &outputList) {
    /*
     * ITERATIVE BACKTRACKING PSEUDOCODE
     * 1.  Push source to stack
     * 2.  While stack not empty:
     *
     * 3.  Check if stack.top is dest
     *      --Yes: store path & pop
     *
     *      --No:  for connection in stack.top:
     *              is connection NULL?
     *                  --Yes: pop stack.top & reset iter
     *
     *              is connection on stack?
     *                  --Yes: continue, move iter
     *                  --No:  push connection, jump to step 3 , move iter
     *
     */
    JPAdjList.moveCurrToHead();
    for (int i = 0; i < JPAdjList.length(); i++) {
        if (JPAdjList.getCurrValue()->getCurrValue().getOrigin() == requested.getOrigin()) {
            jpStack.push(JPAdjList.getCurrValue()->getCurrValue().getOrigin());
            break;
        } else {
            JPAdjList.moveCurrToRight();
        }
    }
    JPAdjList.moveCurrToHead();

    for (int i = 0; i < JPAdjList.length(); i++) {
        JPAdjList.getCurrValue()->moveCurrToHead();
    }
    JPAdjList.moveCurrToHead();

    while (!jpStack.isEmpty()) {
        if (jpStack.peek() == requested.getDestination()) {
            saveStack(outputList, jpStack);
            jpStack.pop();
        } else {
            JPAdjList.moveToPosition(findHead(JPAdjList, jpStack.peek()));
            for (int j = 0; j < JPAdjList.getCurrValue()->length(); j++) {
                if (JPAdjList.getCurrValue()->getCurrNextNode() == nullptr) {
                    jpStack.pop();
                    JPAdjList.getCurrValue()->moveToPosition(1);
                } else if (jpStack.contains(JPAdjList.getCurrValue()->getCurrValue().getDestination())) {
                    JPAdjList.getCurrValue()->moveCurrToRight();
                    continue;
                } else {
                    jpStack.push(JPAdjList.getCurrValue()->getCurrValue().getDestination());
                    JPAdjList.getCurrValue()->moveCurrToRight();
                    break;
                }
            }
        }
    }
}

int calculateTime(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPLinkedList<JPString> &route) {
    int total = 0;
    JPIterator<JPString> *routeIter = route.getHeadIterator();
    routeIter->nextNode();
    while (routeIter->nextNode() != NULL) {
        JPIterator<JPLinkedList<Cities> *> *AdjListBigIter = JPAdjList.getHeadIterator();
        while (AdjListBigIter->nextNode() != NULL) {
            if (routeIter->getNode()->data == AdjListBigIter->getNode()->data->getCurrValue().getOrigin()) {
                if (routeIter->peekNextNode()->data ==
                    AdjListBigIter->getNode()->data->getCurrValue().getDestination()) {
                    total = total + AdjListBigIter->getNode()->data->getCurrValue().getTime();
                    break;
                } else {
                    JPIterator<Cities> *AdjListSmallIter = AdjListBigIter->getNode()->data->getHeadIterator();
                    while (AdjListSmallIter->nextNode() != NULL) {
                        if (routeIter->peekNextNode()->data ==
                            AdjListBigIter->getNode()->data->getCurrValue().getDestination()) {
                            total = total + AdjListBigIter->getNode()->data->getCurrValue().getTime();
                            break;
                        }
                    }
                    delete AdjListSmallIter;
                    break;
                }
            }

        }
        delete AdjListBigIter;
    }
    delete routeIter;
    return total;
}

int calculateCost(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPLinkedList<JPString> &route) {
    int total = 0;
    JPIterator<JPString> *routeIter = route.getHeadIterator();
    routeIter->nextNode();
    while (routeIter->nextNode() != NULL) {
        JPIterator<JPLinkedList<Cities> *> *AdjListBigIter = JPAdjList.getHeadIterator();
        while (AdjListBigIter->nextNode() != NULL) {
            if (routeIter->getNode()->data == AdjListBigIter->getNode()->data->getCurrValue().getOrigin()) {
                if (routeIter->peekNextNode()->data ==
                    AdjListBigIter->getNode()->data->getCurrValue().getDestination()) {
                    total = total + AdjListBigIter->getNode()->data->getCurrValue().getCost();
                    break;
                } else {
                    JPIterator<Cities> *AdjListSmallIter = AdjListBigIter->getNode()->data->getHeadIterator();
                    while (AdjListSmallIter->nextNode() != NULL) {
                        if (routeIter->peekNextNode()->data ==
                            AdjListBigIter->getNode()->data->getCurrValue().getDestination()) {
                            total = total + AdjListBigIter->getNode()->data->getCurrValue().getCost();
                            break;
                        }
                    }
                    delete AdjListSmallIter;
                    break;
                }
            }

        }
        delete AdjListBigIter;
    }
    delete routeIter;
    return total;
}

void getOutput(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPLinkedList<Cities> &requestedRoutes,
               JPLinkedList<JPLinkedList<JPString> *> &outputList, ofstream &outFile, JPStack &jpStack) {


    JPIterator<Cities> *jpIterator4 = requestedRoutes.getHeadIterator();
    while (jpIterator4->nextNode() != nullptr) {
        iterativeBacktrack(JPAdjList, jpStack, jpIterator4->getNode()->data, outputList);
    }

    delete jpIterator4;

    JPIterator<Cities> *jpIterator5 = requestedRoutes.getHeadIterator();
    while (jpIterator5->peekNextNode() != nullptr) {
        JPIterator<JPLinkedList<JPString> *> *jpIterator = outputList.getHeadIterator();
        if (jpIterator->nextNode()->data->getCurrValue() == jpIterator5->getNode()->data.getOrigin()) {
            while (jpIterator->nextNode() != nullptr) {
                if (jpIterator->getNode()->data->getCurrValue() == jpIterator5->getNode()->data.getDestination()) {
                    cout << calculateTime(JPAdjList, *jpIterator->getNode()->data) << endl;
                }
            }
        }
        jpIterator5->nextNode();
        delete jpIterator;
    }

    delete jpIterator5;

}