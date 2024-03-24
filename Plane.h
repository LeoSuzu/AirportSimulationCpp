//
// Created by Leo Suzuki on 18.3.2024.
//

#ifndef PLANE_H
#define PLANE_H

#include "Utility.h"
#include "Random.h"

enum Plane_status {null, arriving, departing};

class Plane {
public:
   Plane();
   Plane(int flt, int time, Plane_status status);
   void refuse() const;
   void land(int time) const;
   void fly(int time) const;
   int started() const;

private:
   int flt_num;
   int clock_start;
   Plane_status state;
   Random random;
   int fuel;
};



#endif //PLANE_H
