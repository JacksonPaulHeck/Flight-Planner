//
// Created by jacks on 4/3/2020.
//

#ifndef S20_PA04_FLIGHTPLANNER_CITIES_H
#define S20_PA04_FLIGHTPLANNER_CITIES_H

#include "JPString.h"

class Cities {
private:
    JPString origin;
    JPString destination;
    int cost;
    int time;
public:
    Cities() {
        cost = 0;
        time = 0;
    }

    Cities(JPString &o, JPString &d, int c, int t) {
        origin = JPString(o);
        destination = JPString(d);
        cost = c;
        time = t;
    }

    [[nodiscard]] JPString getOrigin() const {
        return origin;
    }

    [[nodiscard]] JPString getDestination() const {
        return destination;
    }

    [[nodiscard]] int getCost() const {
        return cost;
    }

    [[nodiscard]] int getTime() const {
        return time;
    }

    void setOrigin(JPString &o) {
        origin = JPString(o);
    }

    void setDestination(JPString &d) {
        destination = JPString(d);
    }

    void setCost(int c) {
        cost = c;
    }

    void setTime(int t) {
        time = t;
    }

    friend std::ostream &operator<<(std::ostream &outStream, const Cities &cities) {
        if (cities != Cities()) {
            outStream << cities.getOrigin() << " :: " << cities.getDestination();
        } else {
            outStream << "";
        }
        return outStream;
    }

    //Equality Comparison Operator
    friend bool operator==(const Cities &cities1, const Cities &cities2) {
        return !(cities1.getOrigin() != cities2.getOrigin() ||
                 cities1.getDestination() != cities2.getDestination() ||
                 cities1.getCost() != cities2.getCost() ||
                 cities1.getTime() != cities2.getTime());
    }

    friend bool operator!=(const Cities &cities1, const Cities &cities2) {
        return (cities1.getOrigin() != cities2.getOrigin() ||
                cities1.getDestination() != cities2.getDestination() ||
                cities1.getCost() != cities2.getCost() ||
                cities1.getTime() != cities2.getTime());
    }

};

#endif //S20_PA04_FLIGHTPLANNER_CITIES_H