#include "Runway.h"

Runway::Runway(int limit)
{
   queue_limit = limit;
   num_land_requests = num_takeoff_requests = 0;
   num_landings = num_takeoffs = 0;
   num_land_refused = num_takeoff_refused = 0;
   num_land_accepted = num_takeoff_accepted = 0;
   land_wait = takeoff_wait = idle_time = 0;
}

Error_code Runway::can_land(const Plane &current)
{
   Error_code result;
   if (landing_queue.size() < queue_limit)
      result = landing_queue.append(current);
   else
      result = fail;
   num_land_requests++;

   if (result != success)
      num_land_refused++;
   else
      num_land_accepted++;

   return result;
}

Error_code Runway::can_depart(const Plane &current)
{
   Error_code result;
   if (takeoff_queue.size() < queue_limit)
      result = takeoff_queue.append(current);
   else
      result = fail;
   num_takeoff_requests++;
   if (result != success)
      num_takeoff_refused++;
   else
      num_takeoff_accepted++;

   return result;
}

Runway_activity Runway::activity(int time, Plane &moving)
{
   Runway_activity in_progress;
   if (!landing_queue.empty()) {
      landing_queue.retrieve(moving);
      land_wait += time - moving.started();
      num_landings++;
      in_progress = land;
      landing_queue.serve();
   }

   else if (!takeoff_queue.empty()) {
      takeoff_queue.retrieve(moving);
      takeoff_wait += time - moving.started();
      num_takeoffs++;
      in_progress = takeoff;
      takeoff_queue.serve();
   }

   else {
      idle_time++;
      in_progress = idle;
   }
   return in_progress;
}

// Implementation to return total number of activities
// Landing operations
int Runway::getNumLandRequests() const {
   return num_land_requests;
}

int Runway::getNumLandings() const {
   return num_landings;
}

int Runway::getNumLandAccepted() const {
   return num_land_accepted;
}

int Runway::getNumLandRefused() const {
   return num_land_refused;
}

int Runway::getLandWait() const {
   return land_wait;
}
// Takeoff operations
int Runway::getNumTakeoffRequests() const {
   return num_takeoff_requests;
}

int Runway::getNumTakeoffs() const {
   return num_takeoffs;
}

int Runway::getNumTakeoffAccepted() const {
   return num_takeoff_accepted;
}

int Runway::getNumTakeoffRefused() const {
   return num_takeoff_refused;
}

int Runway::getTakeoffWait() const {
   return takeoff_wait;
}

// Method to access idle time
int Runway::getIdleTime() const {
   return idle_time;
}

// Definition of the << operator overload for the Runway class
std::ostream& operator<<(std::ostream& os, const Runway& runway) {
   os << "Total land requests: " << runway.getNumLandRequests() << std::endl;
   os << "Total takeoff requests: " << runway.getNumTakeoffRequests() << std::endl;
   // Add other statistics as needed
   return os;
}

// Total print moved to Airport.cpp

