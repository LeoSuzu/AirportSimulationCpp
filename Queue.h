//
// Created by Leo Suzuki on 18.3.2024.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "Utility.h"
#include "Plane.h"

const int maxqueue = 100; // Small value for testing

class Queue {
public:
    Queue();
    bool empty() const;
    bool full() const;
    int size() const;
    void clear();
    Error_code serve();
    Error_code append(const Plane &item);
    Error_code retrieve(Plane &item) const;

protected:
    int count;
    int front, rear;
    Plane entry[maxqueue];
};

#endif // QUEUE_H

