//
// Created by jacks on 3/26/2020.
//

#ifndef S20_PA04_FLIGHTPLANNER_JPSTACK_H
#define S20_PA04_FLIGHTPLANNER_JPSTACK_H

#include "JPLinkedList.h"

template<class T>
class JPStack {
private:
    JPLinkedList<T> *data;
    int size;
public:
    JPStack() {
        data = new JPLinkedList<T>;
        size = data->length();
    }

    ~JPStack() {
        clear();
    }

    void clear() {
        data->clear();
        size = data->length();
        delete data;
    }

    void push(const T &it) {
        data->moveToHead();
        data->insert(it);
        size = data->length();
    }

    T pop() {
        if (size > 0) {
            data->moveToHead();
            size--;
            return data->remove();
        }
        return NULL;
    }

    const T &topValue() const {
        data->moveToHead();
        return data->getValue();
    }

    int length() const {
        return size;
    }
};


#endif //S20_PA04_FLIGHTPLANNER_JPSTACK_H
