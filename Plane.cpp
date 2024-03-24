//
// Created by Leo Suzuki on 18.3.2024.
//

#include "Plane.h"

Plane::Plane(int flt, int time, Plane_status status)
// Plane data members flt_num, clock_start, and state are set to the values of the parameters flt,
// time and status, respectively.

{
   flt_num = flt;
   clock_start = time;
   state = status;
   cout << "Plane number " << flt << " ready to ";
   if (status == arriving)
      cout << "land." << endl;
   else
      cout << "take off." << endl;
}


Plane::Plane()
// The Plane data members flt_num, clock_start, state are set to illegal default values.
{
   flt_num = 0;
   clock_start = -1;
   state = null;
   fuel = random.random_integer(3, 10);
}


void Plane::refuse() const
// Processes a Plane wanting to use Runway, when the Queue is full.
{
   cout << "Plane number " << flt_num;
   if (state == arriving)
      cout << " directed to another airport" << endl;
   else
      cout << " told to try to takeoff again later" << endl;
}


void Plane::land(int time) const
// Processes a Plane that is landing at the specified time.
{
   int wait = time - clock_start;
   cout << time << ": Plane number " << flt_num << " landed after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the landing queue." << endl;
}


void Plane::fly(int time) const
//Process a Plane that is taking off at the specified time.
{
   int wait = time - clock_start;
   cout << time << ": Plane number " << flt_num << " took off after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue." << endl;
}

int Plane::started() const
// Return the time that the Plane entered the airport system.
{
   return clock_start;
}

