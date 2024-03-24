//
// Created by Leo Suzuki on 18.3.2024.
//

// Airport.h
#ifndef AIRPORT_H
#define AIRPORT_H

#include "Runway.h"
#include "Plane.h"
#include "Utility.h"
#include "Random.h"

class Airport {
public:
    Airport();

    void airport_small();
    void airport_medium_fixed();
    void airport_medium_flexible();
    void airport_large();

    static void handleRunwayActivity(Runway *runway, int current_time, int &flight_number, int runway_number);
    void initialize(int version);

private:

    /* Testing only
    static constexpr int end_time_fixed = 2000;             // Example fixed value
    static constexpr int queue_limit_fixed = 10;            // Example fixed value
    static constexpr double arrival_rate_fixed = 0.6;       // Example fixed value
    static constexpr double departure_rate_fixed = 0.4;     // Example fixed value
    */

    Utility lib_random;
    Random random;

    Runway* runway1;
    Runway* runway2;
    Runway* runway3;


    int end_time;
    int queue_limit;
    double arrival_rate;
    double departure_rate;
    int flight_number;

    // TOTAL RESULT
    // Initialize variables to accumulate combined results
    int total_land_requests = 0;
    int total_takeoff_requests = 0;
    int total_land_accepted = 0;
    int total_takeoff_accepted = 0;
    int total_land_refused = 0;
    int total_takeoff_refused = 0;
    int total_landings = 0;
    int total_takeoffs = 0;
    int total_land_wait = 0;
    int total_takeoff_wait = 0;
    int total_idle_time = 0;
    int total_planes_queued_land_remain = 0;
    int total_planes_queued_takeoff_remain = 0;

    void printRunwayResults();
};

#endif // AIRPORT_H
