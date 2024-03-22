//
// Created by Leo Suzuki on 18.3.2024.
//

#include "Airport.h"



// airport_large();
/*
airport ave three runways, one always reserved for each of
landing and takeoff and the third used for landings unless the landing queue
is empty, in which case it can be used for takeoffs.
*/


Airport::Airport() : flight_number(0), runway1(nullptr), runway2(nullptr), runway3(nullptr) {
    // Initialize member variables using values stored in the class
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
}

void Airport::initialize(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate) {
    // No need to redefine variables, use class member variables directly
    this->end_time = end_time_fixed;
    this->queue_limit = queue_limit_fixed;
    this->arrival_rate = arrival_rate_fixed;
    this->departure_rate = departure_rate_fixed;
}

// One runway is used for both landings and takeoffs
void Airport::airport_small() {

    runway1 = new Runway(queue_limit);

    for (int current_time = 0; current_time < end_time; ++current_time) {
        int number_arrivals = lib_random.poissonGenerator(arrival_rate);
        for (int i = 0; i < number_arrivals; ++i) {
            Plane current_plane(flight_number++, current_time, arriving);
            Error_code result = runway1->can_land(current_plane);
            if (result != success) {
                current_plane.refuse();
            }
        }

        int number_departures = lib_random.poissonGenerator(departure_rate);
        for (int j = 0; j < number_departures; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            Error_code result = runway1->can_depart(current_plane);
            if (result != success) {
                current_plane.refuse();
            }
        }
        // Call function to handle runway activity
        handleRunwayActivity(runway1, current_time, flight_number,1);
    }

    printRunwayResults();
}

void Airport::airport_medium_fixed() {
    // Create two runways, one for landings and one for takeoffs
    runway1 = new Runway(queue_limit);
    runway2 = new Runway(queue_limit);

    for (int current_time = 0; current_time < end_time; ++current_time) {
        int number_arrivals = lib_random.poissonGenerator(arrival_rate);
        for (int i = 0; i < number_arrivals; ++i) {
            Plane current_plane(flight_number++, current_time, arriving);
            Error_code result = runway1->can_land(current_plane); // Use runway1 for landing
            if (result != success) {
                current_plane.refuse();
            }
        }

        int number_departures = lib_random.poissonGenerator(departure_rate);
        for (int j = 0; j < number_departures; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            Error_code result = runway2->can_depart(current_plane); // Use runway2 for departure
            if (result != success) {
                current_plane.refuse();
            }
        }

        // Check activities for both runways
        Plane moving_plane;
        Runway_activity activity1 = runway1->activity(current_time, moving_plane);
        Runway_activity activity2 = runway2->activity(current_time, moving_plane);

        // Handle runway activities
        if (activity1 == idle && activity2 == idle) {
            std::cout << current_time << ": Runways are idle." << std::endl;
        } else {
            // Handle activity for runway1
            handleRunwayActivity(runway1, current_time, flight_number, 1);

            // Handle activity for runway2
            handleRunwayActivity(runway2, current_time, flight_number, 2);
        }
    }

    // Shutdown and delete runways
    printRunwayResults();
}

airport_medium_flexible()
{

};
/*
Airport two runways, one usually used for
landings and one usually used for takeoffs. If one of the queues is empty, then
both runways can be used for the other queue. Also, if the landing queue is
full and another plane arrives to land, then takeoffs will be stopped and both
runways used to clear the backlog of landing planes.
*/


// Function to handle runway activity for a specific runway
void Airport::handleRunwayActivity(Runway *runway, int current_time, int &flight_number, int runway_number) {
    Utility utility;
    Plane moving_plane;
    Runway_activity activity = runway->activity(current_time, moving_plane);

    // Output runway-specific activity message based on the runway identifier
    switch (activity) {
    case idle:
        std::cout << current_time << ": Runway " << runway_number << " is idle." << std::endl;
        break;
    case land:
        std::cout << current_time << ": Plane landing on Runway " << runway_number << "." << std::endl;
        moving_plane.land(current_time);
        break;
    case takeoff:
        std::cout << current_time << ": Plane taking off from Runway " << runway_number << "." << std::endl;
        moving_plane.fly(current_time);
        break;
    }
}

void Airport::printRunwayResults() {
    // Combine results from all runways using a for loop
    for (int i = 0; i < 3; ++i) {
        Runway* current_runway = nullptr;
        if (i == 0) {
            current_runway = runway1;
        } else if (i == 1) {
            current_runway = runway2;
        } else if (i == 2) {
            current_runway = runway3;
        }

        if (current_runway != nullptr) {
            total_land_requests += current_runway->getNumLandRequests();
            total_takeoff_requests += current_runway->getNumTakeoffRequests();
            total_land_accepted += current_runway->getNumLandAccepted();
            total_takeoff_accepted += current_runway->getNumTakeoffAccepted();
            total_land_refused += current_runway->getNumLandRefused();
            total_takeoff_refused += current_runway->getNumTakeoffRefused();
            total_landings += current_runway->getNumLandings();
            total_takeoffs += current_runway->getNumTakeoffs();
            total_land_wait += current_runway->getLandWait();
            total_takeoff_wait += current_runway->getTakeoffWait();
            total_idle_time += current_runway->getIdleTime();

            // Print the statistics of the current runway
            cout << endl;
            cout << "Runway statistics of Runway " << i + 1 << ":" << endl;
            cout << *current_runway << endl; // Note the use of *
        }
    }
    // Print combined results
    std::cout << "Combined Results from All Runways:" << std::endl;
    std::cout << "Total number of planes processed: " << (total_land_requests + total_takeoff_requests) << std::endl;
    std::cout << "Total number of planes asking to land: " << total_land_requests << std::endl;
    std::cout << "Total number of planes asking to take off: " << total_takeoff_requests << std::endl;
    std::cout << "Total number of planes accepted for landing: " << total_land_accepted << std::endl;
    std::cout << "Total number of planes accepted for takeoff: " << total_takeoff_accepted << std::endl;
    std::cout << "Total number of planes refused for landing: " << total_land_refused << std::endl;
    std::cout << "Total number of planes refused for takeoff: " << total_takeoff_refused << std::endl;
    std::cout << "Total number of planes that landed: " << total_landings << std::endl;
    std::cout << "Total number of planes that took off: " << total_takeoffs << std::endl;
    std::cout << "Total number of planes left in landing queue: " << 0 << std::endl; // You might need to modify this
    std::cout << "Total number of planes left in takeoff queue: " << 0 << std::endl; // You might need to modify this
    std::cout << "Percentage of time runway idle: " << (100.0 * total_idle_time) / end_time << "%" << std::endl;
    std::cout << "Average wait in landing queue: " << ((float)total_land_wait) / total_landings << " time units" << std::endl;
    std::cout << "Average wait in takeoff queue: " << ((float)total_takeoff_wait) / total_takeoffs << " time units" << std::endl;
    std::cout << "Average observed rate of planes wanting to land: " << ((float)total_land_requests) / end_time << " per time unit" << std::endl;
    std::cout << "Average observed rate of planes wanting to take off: " << ((float)total_takeoff_requests) / end_time << " per time unit" << std::endl;

}

/* NOT USE FOR TEST RUN
void Airport::initialize(int &end_time, int &queue_limit,
                         double &arrival_rate, double &departure_rate) {
    std::cout << "This program simulates an airport with only one runway." << std::endl
              << "One plane can land or depart in each unit of time." << std::endl;
    std::cout << "Up to what number of planes can be waiting to land "
              << "or take off at any time? " << std::flush;
    std::cin >> queue_limit;

    std::cout << "How many units of time will the simulation run? " << std::flush;
    std::cin >> end_time;

    bool acceptable;
    do {
        std::cout << "Expected number of arrivals per unit time? " << std::flush;
        std::cin >> arrival_rate;
        std::cout << "Expected number of departures per unit time? " << std::flush;
        std::cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            std::cerr << "Error: Arrival and departure rates must be nonnegative." << std::endl;
            acceptable = false;
        } else if (arrival_rate + departure_rate > 1.0) {
            std::cerr << "Safety Warning: This airport will become saturated." << std::endl;
            std::cerr << "Please adjust arrival and departure rates. " << std::endl;
            acceptable = false;
        } else {
            acceptable = true;
        }
    } while (!acceptable);
}
*/

