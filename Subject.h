#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
    private:
        std::vector<Observer *> observers;

    public:
        virtual ~Subject() = 0;

        // Ensures: adds the Observer pointer o to observers
        void attach(Observer * o);

        // Ensures: removes the Observer pointer o from observers
        void detach(Observer * o);

        // Ensures: For each Observer o in observers, calls o->getNotified()
        void notifyObservers();
};

#endif