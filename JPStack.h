//
// Created by jacks on 3/26/2020.
//

#ifndef S20_PA04_FLIGHTPLANNER_JPSTACK_H
#define S20_PA04_FLIGHTPLANNER_JPSTACK_H

#include "JPLinkedList.h"
#include "JPString.h"

class JPStack {
private:
    int size;
    JPLinkedList<JPString> *data;
public:
    JPStack() {
        data = new JPLinkedList<JPString>;
        size = data->length();
    }

    ~JPStack() {
        clear();
    }

    bool isEmpty(){
        return data->head->next == nullptr;
    }

    void clear() {
        data->clear();
        size = data->length();
        delete data;
    }

    void push(const JPString &it) {
        data->moveCurrToHead();
        data->insert(it);
        data->curr = data->head->next;
        size = data->length();
    }

    JPString pop() {
        if (size > 0) {
            data->moveCurrToHead();
            size--;
            return data->remove();
        }
        return JPString();
    }

    const JPString &peek() const {
        data->moveCurrToHead();
        return data->getCurrValue();
    }

    int length() const {
        return size;
    }

    void print(){
        JPNode<JPString> * tp = data->head;
        while(tp->next!= nullptr){
            tp = tp->next;
            std::cout << tp->data << "-->";
        }
        std::cout<< "|" << std::endl;
    }

    bool contains(const JPString& requestedOrigin){
        JPNode<JPString> * tp = data->head->next;
        while(tp != NULL){
            if(tp->data == requestedOrigin){
                return true;
            }
            tp = tp -> next;
        }
        return false;
    }
    JPLinkedList<JPString>* & save(){
        return data;
    }

};


#endif //S20_PA04_FLIGHTPLANNER_JPSTACK_H
