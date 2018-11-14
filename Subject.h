#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
    private:
        std::vector<Observer *> observers;

    public:
        virtual ~Subject() = 0;

        void attach(Observer * o);

        void detach(Observer * o);

        void notifyObservers();
};

#endif