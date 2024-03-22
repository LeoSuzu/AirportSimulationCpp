//
// Created by Leo Suzuki on 18.3.2024.
//

#ifndef RUNWAY_H
#define RUNWAY_H

#include "Utility.h"
#include "Plane.h"
#include "Queue.h"

enum Runway_activity {idle, land, takeoff};

class Runway {
public:
   Runway(int limit);
   Error_code can_land(const Plane &current);
   Error_code can_depart(const Plane &current);
   Runway_activity activity(int time, Plane &moving);
   void shut_down(const Runway& runway) const;

   // Methods to access statistics for landing operations
   int getNumLandRequests() const;
   int getNumLandings() const;
   int getNumLandAccepted() const;
   int getNumLandRefused() const;
   int getLandWait() const;

   // Methods to access statistics for takeoff operations
   int getNumTakeoffRequests() const;
   int getNumTakeoffs() const;
   int getNumTakeoffAccepted() const;
   int getNumTakeoffRefused() const;
   int getTakeoffWait() const;

   // Method to acces idle time
   int getIdleTime() const;

   // Declaration of the << operator overload as a friend function
   friend std::ostream& operator<<(std::ostream& os, const Runway& runway);

private:
   Queue landing_queue;
   Queue takeoff_queue;
   int queue_limit;

   // Landing operation statistics
   int num_land_requests;
   int num_landings;
   int num_land_accepted;
   int num_land_refused;
   int land_wait;

   // Takeoff operation statistics
   int num_takeoff_requests;
   int num_takeoffs;
   int num_takeoff_accepted;
   int num_takeoff_refused;
   int takeoff_wait;

   int idle_time;                // Total time runway is idle

};

// Declaration of the << operator overload for the Runway class
std::ostream& operator<<(std::ostream& os, const Runway& runway);


#endif
