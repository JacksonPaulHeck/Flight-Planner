//
// Created by JP Heck on 3/27/2020.
//
#include "JPStack.h"
#include "JPIterator.h"
#include "Cities.h"
#include "JPVector.h"

#ifndef S20_PA04_FLIGHTPLANNER_DRIVER_H
#define S20_PA04_FLIGHTPLANNER_DRIVER_H

using namespace std;

void getOutput(JPLinkedList<JPLinkedList<Cities> *> &, JPVector<Cities> &, JPVector<JPVector<JPString>> &, ofstream &, JPStack &, ifstream& data);

int calculateTime(JPLinkedList<JPLinkedList<Cities> *> &, JPVector<JPString> &);

int calculateCost(JPLinkedList<JPLinkedList<Cities> *> &, JPVector<JPString> &);

void iterativeBacktrack(JPLinkedList<JPLinkedList<Cities> *> &, JPStack & , const Cities &, JPVector<JPVector<JPString>> &);

void resetAdjList(JPLinkedList<JPLinkedList<Cities> *> &);

void saveStack(JPVector<JPVector<JPString>> &, JPStack &);

int findHead(JPLinkedList<JPLinkedList<Cities> *> &, const JPString &);

void addNewList(JPLinkedList<JPLinkedList<Cities> *> &, Cities &, bool &);

void searchInList(JPLinkedList<JPLinkedList<Cities> *> &, Cities &, bool &);

void emptyList(JPLinkedList<JPLinkedList<Cities> *> &, Cities &, Cities &);

void parseInputFile(JPLinkedList<JPLinkedList<Cities> *> &, ifstream &);

void parseRequested(JPVector<Cities> &, ifstream &);

void printToFile(ofstream&, int, JPVector<Cities> &, JPLinkedList<JPLinkedList<Cities> *> &, JPVector<JPVector<JPString>> &);

void getTopThree(JPLinkedList<JPLinkedList<Cities> *> &, JPVector<JPVector<JPString>> &, Cities &);

void clearList(JPVector<JPVector<JPString>> &);

void deleteAdjList(JPLinkedList<JPLinkedList<Cities> *> &);

#endif //S20_PA04_FLIGHTPLANNER_DRIVER_H