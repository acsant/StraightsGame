//
// Created by Akash Sant on 15-07-15.
//

#ifndef STRAIGHTS_SUBJECT_H
#define STRAIGHTS_SUBJECT_H
#include "Observer.h"
#include <set>

class Subject {
public:
    void subscribe(Observer*);
    void unsubscribe(Observer*);

protected:
    void notify();

private:
    typedef std::set<Observer*> Observers;
    Observers observers_;
};


#endif //STRAIGHTS_SUBJECT_H
