//
// Created by JP Heck on 3/27/2020.
//
#include "Driver.h"
#include <sstream>

void parseRequested(JPVector<Cities> &requestedList, ifstream &inFile) {
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
            ss.getline(type, 20, '\r');

            JPString JPOrigin(origin);
            JPString JPDest(dest);
            JPString JPType(type);
            int costBool = 0;
            int timeBool = 0;
            if (JPType == "C") {
                costBool = 1;
            } else {
                timeBool = 1;
            }
            Cities requested(JPDest, JPOrigin, costBool, timeBool);
            if(requested.getOrigin() != JPString() && requested.getDestination() != JPString()) {
                requestedList.push_back(requested);
            }
        }
    }
    delete[] line;
    delete[] origin;
    delete[] dest;
    delete[] type;
}

void parseInputFile(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, ifstream &inFile) {
    inFile.clear();
    inFile.seekg(0, ios::beg);
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

void saveStack(JPVector<JPVector<JPString>> &outputList, JPStack &jpStack) {
    auto *jpLinkedList = new JPLinkedList(*jpStack.save());
    JPVector<JPString> jpVector;
    JPIterator<JPString> *jpIterator = jpLinkedList->getHeadIterator();
    jpIterator->nextNode();
    while (jpIterator->peekNextNode() != NULL) {
        jpVector.push_back(jpIterator->nextNode()->data);
    }
    outputList.push_back(jpVector);

    delete jpIterator;
    delete jpLinkedList;
}

void resetAdjList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList){
    JPAdjList.moveCurrToHead();
    for(int i = 0; i < JPAdjList.length(); i++){
        JPAdjList.getCurrValue()->moveCurrToHead();
    }
    JPAdjList.moveCurrToHead();
}

void iterativeBacktrack(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPStack & jpStack, const Cities &requested,
                        JPVector<JPVector<JPString>> &outputList) {
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

    resetAdjList(JPAdjList);

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

int calculateTime(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPVector<JPString> &route) {
    int total = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        JPIterator<JPLinkedList<Cities> *> *AdjListBigIter = JPAdjList.getHeadIterator();
        while (AdjListBigIter->nextNode() != NULL) {
            JPIterator<Cities> *AdjListSmallerIter = AdjListBigIter->getNode()->data->getHeadIterator();
            while (AdjListSmallerIter->nextNode() != NULL) {
                if (route[i] == AdjListSmallerIter->getNode()->data.getOrigin() &&
                    route[i + 1] == AdjListSmallerIter->getNode()->data.getDestination()) {
                    total = total + AdjListSmallerIter->getNode()->data.getTime();
                }
            }
            delete AdjListSmallerIter;
        }
        delete AdjListBigIter;
    }
    return total;
}

int calculateCost(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPVector<JPString> &route) {
    int total = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        JPIterator<JPLinkedList<Cities> *> *AdjListBigIter = JPAdjList.getHeadIterator();
        while (AdjListBigIter->nextNode() != NULL) {
            JPIterator<Cities> *AdjListSmallerIter = AdjListBigIter->getNode()->data->getHeadIterator();
            while (AdjListSmallerIter->nextNode() != NULL) {
                if (route[i] == AdjListSmallerIter->getNode()->data.getOrigin() &&
                    route[i + 1] == AdjListSmallerIter->getNode()->data.getDestination()) {
                    total = total + AdjListSmallerIter->getNode()->data.getCost();
                }
            }
            delete AdjListSmallerIter;
        }
        delete AdjListBigIter;
    }
    return total;
}

void getTopThree(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPVector<JPVector<JPString>> & list, Cities & requested){
    resetAdjList(JPAdjList);
    int first, second, third;
    JPVector<JPString> firstList, secondList, thirdList;
    if(list.size() < 3){
        return;
    }else if(requested.getTime() == 1) {
        third = second = first = INT32_MAX;
        for (int i = 0; i < list.size(); i++) {
            if (calculateTime(JPAdjList, list[i]) < first) {
                resetAdjList(JPAdjList);
                third = second;
                second = first;
                first = calculateTime(JPAdjList, list[i]);
                thirdList = secondList;
                secondList = firstList;
                firstList = list[i];
            } else if (calculateTime(JPAdjList, list[i]) < second) {
                resetAdjList(JPAdjList);
                third = second;
                second = calculateTime(JPAdjList, list[i]);
                thirdList = secondList;
                secondList = list[i];
            } else if (calculateTime(JPAdjList, list[i]) < third) {
                resetAdjList(JPAdjList);
                third = calculateTime(JPAdjList, list[i]);
                thirdList = list[i];
            }
        }
    }else{
        third = second = first = INT32_MAX;
        for (int i = 0; i < list.size(); i++) {
            if (calculateCost(JPAdjList, list[i]) < first) {
                resetAdjList(JPAdjList);
                third = second;
                second = first;
                first = calculateCost(JPAdjList, list[i]);
                thirdList = secondList;
                secondList = firstList;
                firstList = list[i];
            } else if (calculateCost(JPAdjList, list[i]) < second) {
                resetAdjList(JPAdjList);
                third = second;
                second = calculateCost(JPAdjList, list[i]);
                thirdList = secondList;
                secondList = list[i];
            } else if (calculateCost(JPAdjList, list[i]) < third) {
                resetAdjList(JPAdjList);
                third = calculateCost(JPAdjList, list[i]);
                thirdList = list[i];
            }
        }
    }
    resetAdjList(JPAdjList);
    clearList(list);
    list.push_back(firstList);
    list.push_back(secondList);
    list.push_back(thirdList);
}

void printToFile(ofstream& outFile, int j, JPVector<Cities> & requestedRoutes, JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPVector<JPVector<JPString>> &outputList){
    outFile << "Path " << j+1 << ": ";
    for (int k = 0; k < outputList[j].size() - 1; k++) {
        outFile << outputList[j][k] << " -> ";
    }
    outFile << outputList[j][outputList[j].size() - 1];
    outFile << ". Time: " << calculateTime(JPAdjList, outputList[j]);
    resetAdjList(JPAdjList);
    outFile << " Cost: " << calculateCost(JPAdjList, outputList[j]) << endl;
    resetAdjList(JPAdjList);
}

void clearList(JPVector<JPVector<JPString>> &outputList){
    int j = outputList.size();
    for(int i = 0; i < j; i++){
        outputList.pop_back();
    }
}

void getOutput(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPVector<Cities> &requestedRoutes, JPVector<JPVector<JPString>> &outputList, ofstream &outFile, JPStack & jpStack, ifstream & data) {

    JPString type;

    for(int i = 0; i < requestedRoutes.size(); i++) {
        if(requestedRoutes[i].getCost() == 1){
            type = "Cost";
        }else{
            type = "Time";
        }
        iterativeBacktrack(JPAdjList, jpStack, requestedRoutes[i], outputList);
        resetAdjList(JPAdjList);
        getTopThree(JPAdjList, outputList, requestedRoutes[i]);
        outFile << "Flight " << i+1 << ": " << requestedRoutes[i].getDestination() << ", " << requestedRoutes[i].getOrigin() << " (" << type << ")" << endl;
        for (int j = 0; j < outputList.size(); j++) {
            printToFile(outFile, j, requestedRoutes, JPAdjList, outputList);
            resetAdjList(JPAdjList);
        }
        outFile << endl;
        clearList(outputList);
        JPAdjList.clear();
        parseInputFile(JPAdjList, data);
        resetAdjList(JPAdjList);
    }
}