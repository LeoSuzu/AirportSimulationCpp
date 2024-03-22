//
// Created by Leo Suzuki on 18.3.2024.
//

#include "Queue.h"

Queue::Queue() {
   count = 0;
   rear = maxqueue - 1;
   front = 0;
}

bool Queue::empty() const {
   return count == 0;
}

bool Queue::full() const {
   return count == maxqueue;
}

int Queue::size() const {
   return count;
}

void Queue::clear() {
   count = 0;
   front = 0;
   rear = maxqueue - 1;
}

Error_code Queue::append(const Plane &item) {
   if (count >= maxqueue)
      return overflow;
   count++;
   rear = (rear + 1) % maxqueue;
   entry[rear] = item;
   return success;
}

Error_code Queue::serve() {
   if (count <= 0)
      return underflow;
   count--;
   front = (front + 1) % maxqueue;
   return success;
}

Error_code Queue::retrieve(Plane &item) const {
   if (count <= 0)
      return underflow;
   item = entry[front];
   return success;
}