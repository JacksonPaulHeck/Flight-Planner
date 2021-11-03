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
    //reset input file each time it is called
    inFile.clear();
    inFile.seekg(0, ios::beg);
    //create variables used for input from file
    char *line = new char[80];
    char *origin = new char[20];
    char *dest = new char[20];
    char *cost = new char[20];
    char *time = new char[20];

    //get whole line
    inFile.getline(line, 80);
    //the first line is the length of the file
    int length = atoi(line);
    //iterate through the file
    for (int i = 0; i < length; i++) {
        //getline
        inFile.getline(line, 80);
        stringstream ss(line);
        //iterate through each line
        while (!ss.eof()) {
            //delimit by '|'
            ss.getline(origin, 20, '|');
            ss.getline(dest, 20, '|');
            ss.getline(cost, 20, '|');
            ss.getline(time, 20);

            JPString JPOrigin(origin);
            JPString JPDest(dest);
            int c = atoi(cost);
            int t = atoi(time);
            //create cities objects
            Cities cities_Orig(JPOrigin, JPDest, c, t);
            Cities cities_Dest(JPDest, JPOrigin, c, t);

            //if the list is empty
            if (JPAdjList.length() == 0) {
                //creates new list and adds it to the ADJ list
                emptyList(JPAdjList, cities_Orig, cities_Dest);
            } else {
                //move to head
                JPAdjList.moveCurrToHead();
                bool isOrigin;
                //search if the origin is in the list
                searchInList(JPAdjList, cities_Orig, isOrigin = false);
                JPAdjList.moveCurrToHead();
                bool isDest;
                //search if the dest is in the list
                searchInList(JPAdjList, cities_Dest, isDest = false);
                JPAdjList.moveCurrToHead();
                JPAdjList.getCurrValue()->moveCurrToHead();
                //add each new list
                addNewList(JPAdjList, cities_Orig, isOrigin);
                addNewList(JPAdjList, cities_Dest, isDest);
                JPAdjList.moveCurrToRight();
            }
        }
    }
    //delete temp vars
    delete[] line;
    delete[] origin;
    delete[] dest;
    delete[] cost;
    delete[] time;
}

void emptyList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, Cities &cities1, Cities &cities2) {
    //creates new list
    auto *jpLinkedList = new JPLinkedList<Cities>;
    jpLinkedList->moveCurrToHead();
    //insert cities
    jpLinkedList->insert(cities1);
    JPAdjList.moveCurrToHead();
    //inserts whole list
    JPAdjList.insert(jpLinkedList);
    //does the same with cities2 but instead of inserting it appends
    auto *jpLinkedList1 = new JPLinkedList<Cities>;
    jpLinkedList1->moveCurrToHead();
    jpLinkedList1->insert(cities2);
    JPAdjList.append(jpLinkedList1);
}

void searchInList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, Cities &head, bool &isThere) {
    //iterate through the outer list
    for (int j = 0; j < JPAdjList.length(); j++) {
        isThere = false;
        JPAdjList.getCurrValue()->moveCurrToHead();
        //check if the cities origins match
        if (JPAdjList.getCurrValue()->getCurrValue().getOrigin() == head.getOrigin()) {
            JPAdjList.getCurrValue()->moveCurrToHead();
            //if they do then append the head Cities
            JPAdjList.getCurrValue()->append(head);
            break;
        } else { isThere = true; }
        JPAdjList.moveCurrToRight();
    }
}

void addNewList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, Cities &head, bool &isThere) {
    //checks if the list "isThere or not"
    if (isThere) {
        //if it is not there (the isThere varibable being true)
        //create a new list, add the cities var as its head
        auto *jpLinkedList = new JPLinkedList<Cities>;
        jpLinkedList->moveCurrToHead();
        //insert it to the list
        jpLinkedList->insert(head);
        JPAdjList.moveCurrToHead();
        JPAdjList.insert(jpLinkedList);
    }
}

int findHead(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, const JPString &origin) {
    //creates an iterator from the ADJ List
    JPIterator<JPLinkedList<Cities> *> *bigList = JPAdjList.getHeadIterator();
    int i = 0;
    while (bigList->nextNode() != NULL) {
        //if the current head value of the big list == origin
        if (bigList->getNode()->data->getCurrValue().getOrigin() == origin) {
            //return the position of the list
            delete bigList;
            return i;
        }
        i++;
    }
    delete bigList;
    return -1;
}

void saveStack(JPVector<JPVector<JPString>> &outputList, JPStack &jpStack) {
    //creates a new Linked list from the jpstack
    auto *jpLinkedList = new JPLinkedList(*jpStack.save());
    JPVector<JPString> jpVector;
    JPIterator<JPString> *jpIterator = jpLinkedList->getHeadIterator();
    jpIterator->nextNode();
    //iterates through the stack
    while (jpIterator->peekNextNode() != NULL) {
        //adds each value in the stack to a vector
        jpVector.push_back(jpIterator->nextNode()->data);
    }
    //add vector to outputList
    outputList.push_back(jpVector);

    delete jpIterator;
    delete jpLinkedList;
}

//method to reset the current pointers in the ADJ list
void resetAdjList(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList){
    JPAdjList.moveCurrToHead();
    for(int i = 0; i < JPAdjList.length(); i++){
        JPAdjList.getCurrValue()->moveCurrToHead();
    }
    JPAdjList.moveCurrToHead();
}

void iterativeBacktrack(JPLinkedList<JPLinkedList<Cities> *> &JPAdjList, JPStack & jpStack, const Cities &requested,
                        JPVector<JPVector<JPString>> &outputList) {
    //adds the head node with its origin that is requested to the stack
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
    //resets the curr pointer in ADJ List to the head
    resetAdjList(JPAdjList);

    //check if the stack is empty
    while (!jpStack.isEmpty()) {
        //if the top of the stack equals the requested destination
        if (jpStack.peek() == requested.getDestination()) {
            //save the stack
            saveStack(outputList, jpStack);
            //pop off the top of the stack
            jpStack.pop();
        } else {
            //move to the position in the adj list where the top of the stack is without changing where the internal iterator is
            JPAdjList.moveToPosition(findHead(JPAdjList, jpStack.peek()));
            for (int j = 0; j < JPAdjList.getCurrValue()->length(); j++) {
                //if the next node is null(end of the list in one of the lists)
                if (JPAdjList.getCurrValue()->getCurrNextNode() == nullptr) {
                    //pop off top
                    jpStack.pop();
                    //reset curr pointer
                    JPAdjList.getCurrValue()->moveToPosition(1);
                    //else if the stack contains the element
                } else if (jpStack.contains(JPAdjList.getCurrValue()->getCurrValue().getDestination())) {
                    //iterate to the right
                    JPAdjList.getCurrValue()->moveCurrToRight();
                    continue;
                } else {
                    //push the value to the stack
                    jpStack.push(JPAdjList.getCurrValue()->getCurrValue().getDestination());
                    //iterate the internal list
                    JPAdjList.getCurrValue()->moveCurrToRight();
                    break;
                }
            }
        }
    }
}

//method to calculate time of a route
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
        iterativeBacktrack(JPAdjList, jpStack, requestedRoutes[i], outputList); //calls iterative backtrack to get ouotput routes
        resetAdjList(JPAdjList); //resets the list
        getTopThree(JPAdjList, outputList, requestedRoutes[i]); //get the top three best of cost or time
        outFile << "Flight " << i+1 << ": " << requestedRoutes[i].getDestination() << ", " << requestedRoutes[i].getOrigin() << " (" << type << ")" << endl;
        //print each of the paths
        for (int j = 0; j < outputList.size(); j++) {
            printToFile(outFile, j, requestedRoutes, JPAdjList, outputList);
            resetAdjList(JPAdjList);
        }
        outFile << endl;
        //clear each of the lists to delete objects and to reset for the next iteration
        clearList(outputList);
        JPAdjList.clear();
        parseInputFile(JPAdjList, data); //reparse the input file for the next iteration
        resetAdjList(JPAdjList);
    }
    JPAdjList.clear(); //clear the final ADJ list to delete it
}