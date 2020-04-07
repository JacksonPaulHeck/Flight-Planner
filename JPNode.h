//
// Created by jacks on 3/27/2020.
//
#include <iostream>
#include <fstream>

#ifndef S20_PA04_FLIGHTPLANNER_JPNODE_H
#define S20_PA04_FLIGHTPLANNER_JPNODE_H

template<typename T>
class JPNode {
    friend class JPStack;
    template <class U> friend class JPLinkedList;
    template <class E> friend class JPIterator;
private:
    static JPNode<T> * freelist;
public:
    T data;
    JPNode<T> *next;
    JPNode<T> *previous;

    JPNode(const T& it, JPNode* prev, JPNode* nex){
        data = it;
        previous = prev;
        next = nex;
    }
    JPNode(JPNode* prev = NULL, JPNode* nex = NULL){
        previous = prev;
        next = nex;
    }

    void* operator new (size_t){
        if(freelist == NULL){
            return :: new JPNode;
        }
        JPNode<T> * temp = freelist;
        freelist = freelist->next;
        return temp;
    }
    void operator delete(void * ptr){
        ((JPNode<T>*)ptr)->next = freelist;
        freelist = (JPNode<T>*)ptr;
    }
};
template<typename T>
JPNode<T>* JPNode<T> :: freelist = NULL;

#endif //S20_PA04_FLIGHTPLANNER_JPNODE_H