//
// Created by jacks on 4/6/2020.
//

#ifndef S20_PA04_FLIGHTPLANNER_JPITERATOR_H
#define S20_PA04_FLIGHTPLANNER_JPITERATOR_H

#include "JPNode.h"

template <typename T>
class JPIterator{
private:
    JPNode<T>* node;
public:
    JPIterator(JPNode<T> *jpNode = NULL) : node(jpNode){}
    ~JPIterator(){
        if(node == NULL){
            node = NULL;
        }
    }
    JPNode<T>* nextNode(){
        if(node == NULL){
            return NULL;
        }
        node = node->next;
        return node;    }
    JPNode<T>* previousNode(){
        if(node == NULL){
            return NULL;
        }
        node = node->previous;
        return node;
    }
    JPNode<T>* getNode(){
        return node;
    }
    void reset(){
        while(node->previous != nullptr){
            node = node->previous;
        }
    }
    void position(int pos){
        reset();
        for(int i = 0; i < pos; i++){
            node = node ->next;
        }
    }


};

#endif //S20_PA04_FLIGHTPLANNER_JPITERATOR_H
