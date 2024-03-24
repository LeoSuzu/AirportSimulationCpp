//
// Created by Leo Suzuki on 18.3.2024.
//

#include "Airport.h"

// Functions to handle landing and takeoff of planes
void handleLandingAndTakeoff(int current_time, int flight_number, Runway* runway, int arriving_planes, int departing_planes);
void handleLandingOnly(int current_time, int flight_number, Runway* runway, int arriving_planes);
void handleTakeoffOnly(int current_time, int flight_number, Runway* runway, int departing_planes);
void handleLandingPrimary(int current_time, int flight_number, Runway* runway, int arriving_planes, int departing_planes);
void handleTakeoffPrimary(int current_time, int flight_number, Runway* runway, int arriving_planes, int departing_planes);
void handleAllRunways(int current_time, int flight_number,
    Runway* runway1, Runway* runway2, Runway* runway3, int number_arrivals, int number_departures);


// Create an airport with default values
Airport::Airport() : flight_number(0), runway1(nullptr), runway2(nullptr), runway3(nullptr) {}

// Change Random to Use Random from liblary later!!!
// Change Queue to Use Queue from liblary later!!!

// One runway is used for both landings and takeoffs
void Airport::airport_small() {

    // Create a runway
    runway1 = new Runway(queue_limit);

    // Loop through the simulation time
    for (int current_time = 0; current_time < end_time; ++current_time) {
        // Landings
        // int number_arrivals = lib_random.poissonGenerator(arrival_rate); // Liblary version
        int number_arrivals = random.poisson(arrival_rate);
        // Takeoffs
        // int number_departures = lib_random.poissonGenerator(departure_rate); // Liblary version
        int number_departures = random.poisson(departure_rate);

        // Runway handling function for landing and takeoff
        handleLandingAndTakeoff(current_time, flight_number, runway1, number_arrivals, number_departures);

        // Check activities for the runway
        handleRunwayActivity(runway1, current_time, flight_number,1);
    }

    // Print the results and delete the runway(s)
    printRunwayResults();
}
// Two runways are used, one for landings and one for takeoffs
void Airport::airport_medium_fixed() {
    // Create two runways
    runway1 = new Runway(queue_limit);
    runway2 = new Runway(queue_limit);

    // Loop through the simulation time
    for (int current_time = 0; current_time < end_time; ++current_time) {
        // Landings
        // int number_arrivals = lib_random.poissonGenerator(arrival_rate); // Liblary version
        int number_arrivals = random.poisson(arrival_rate); // Random class version
        // Handles landings only
        handleLandingOnly(current_time, flight_number, runway1, number_arrivals);

        // Takeoffs
        // int number_departures = lib_random.poissonGenerator(departure_rate); // Liblary version
        int number_departures = random.poisson(departure_rate); // Random class version
        // Handles takeoffs only
        handleTakeoffOnly(current_time, flight_number, runway2, number_departures);

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
    // Print total results and each runway and delete the runway(s)
    printRunwayResults();
}
// Two runways are used, one for primary landings and one for primary takeoffs with exception handling
void Airport::airport_medium_flexible()
{
    // Create two runways
    runway1 = new Runway(queue_limit);
    runway2 = new Runway(queue_limit);

    // Loop through the simulation time
    for (int current_time = 0; current_time < end_time; ++current_time) {
        // Generate random number of landings and takeoffs
        // int number_arrivals = lib_random.poissonGenerator(arrival_rate); // Liblary version
        int number_arrivals = random.poisson(arrival_rate); // Random class version
        // int number_departures = lib_random.poissonGenerator(departure_rate); // Liblary version
        int number_departures = random.poisson(departure_rate); // Random class version

        // Landing primary and takeoff secondary
        handleLandingPrimary(current_time, flight_number, runway1, number_arrivals, number_departures);
        // Takeoff primary and landing secondary
        handleTakeoffPrimary(current_time, flight_number, runway2, number_arrivals, number_departures);

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

    // Print the results and delete the runway(s)
    printRunwayResults();
}
// Three runways are used, one for primary landings, one for primary takeoffs, and one for primary landings with exceptions
void Airport::airport_large()
{
    // Create three runways: one for landing, one for takeoff, and one for flexible use
    runway1 = new Runway(queue_limit); // For landings
    runway2 = new Runway(queue_limit); // For takeoffs
    runway3 = new Runway(queue_limit); // For flexible use

    // Loop through the simulation time
    for (int current_time = 0; current_time < end_time; ++current_time) {

        int number_arrivals = random.poisson(arrival_rate);

        // Takeoffs on runway2 (reserved for takeoffs)
        int number_departures = random.poisson(departure_rate);

        // Handle all runways
        handleAllRunways(current_time, flight_number, runway1, runway2, runway3, number_arrivals, number_departures);

        // Check activities for all runways
        Plane moving_plane;
        Runway_activity activity1 = runway1->activity(current_time, moving_plane);
        Runway_activity activity2 = runway2->activity(current_time, moving_plane);
        Runway_activity activity3 = runway3->activity(current_time, moving_plane);

        // Handle runway activities
        if (activity1 == idle && activity2 == idle && activity3 == idle) {
            std::cout << current_time << ": Runways are idle." << std::endl;
        } else {
            // Handle activity for runway1
            handleRunwayActivity(runway1, current_time, flight_number, 1);

            // Handle activity for runway2
            handleRunwayActivity(runway2, current_time, flight_number, 2);

            // Handle activity for runway3
            handleRunwayActivity(runway3, current_time, flight_number, 3);
        }
    }

    // Print the results and delete the runway(s)
    printRunwayResults();
}

// Runway handling functions
// Landing and takeoff small airport
void handleLandingAndTakeoff(int current_time, int flight_number, Runway* runway, int arriving_planes, int departing_planes) {
    for (int i = 0; i < arriving_planes; ++i) {
        Plane current_plane(flight_number++, current_time, arriving);
        Error_code result = runway->can_land(current_plane);
        if (result != success) {
            current_plane.refuse();
        }
    }

    for (int j = 0; j < departing_planes; ++j) {
        Plane current_plane(flight_number++, current_time, departing);
        Error_code result = runway->can_depart(current_plane);
        if (result != success) {
            current_plane.refuse();
        }
    }
}

// medium airport with two runways dedicated to
void handleLandingOnly(int current_time, int flight_number, Runway* runway, int arriving_planes) {
    for (int i = 0; i < arriving_planes; ++i) {
        Plane current_plane(flight_number++, current_time, arriving);
        Error_code result = runway->can_land(current_plane);
        if (result != success) {
            current_plane.refuse();
        }
    }
}
void handleTakeoffOnly(int current_time, int flight_number, Runway* runway, int departing_planes) {
    for (int j = 0; j < departing_planes; ++j) {
        Plane current_plane(flight_number++, current_time, departing);
        Error_code result = runway->can_depart(current_plane);
        if (result != success) {
            current_plane.refuse();
        }
    }
}

// medium airport with two runways, one for primary landings and one for primary takeoffs
void handleLandingPrimary(int current_time, int flight_number,
    Runway* runway, int arriving_planes, int departing_planes) {
    // Loop through arriving planes
    for (int i = 0; i < arriving_planes; ++i) {
        Plane current_plane(flight_number++, current_time, arriving);
        Error_code result = runway->can_land(current_plane);
        if (result != success) {
            current_plane.refuse();
        }
    }

    // If the landing queue is still empty, handle takeoffs
    if (runway->landing_queue.empty()) {
        std::cout << "Arriving planes queue is empty. Handling takeoffs" << std::endl;
        // Loop through departing planes
        for (int j = 0; j < departing_planes; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            Error_code result = runway->can_depart(current_plane);
            if (result != success) {
                current_plane.refuse();
            }
        }
    }
}
void handleTakeoffPrimary(int current_time, int flight_number,
    Runway* runway, int arriving_planes, int departing_planes) {
    // Check if the landing queue is full
    if (runway->landing_queue.full()) {
        std::cout << "Arriving planes queue is full. Handling landings." << std::endl;
        // Loop through arriving planes until the landing queue is not full
        for (int i = 0; i < arriving_planes && !runway->landing_queue.full(); ++i) {
            Plane current_plane(flight_number++, current_time, arriving);
            Error_code result = runway->can_land(current_plane);
            if (result != success) {
                current_plane.refuse();
            }
        }
    }
    else {
        // Loop through departing planes
        for (int j = 0; j < departing_planes; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            // Check if the takeoff queue is empty
            if (runway->takeoff_queue.empty()) {
                // If the takeoff queue is empty, attempt takeoff
                Error_code result = runway->can_depart(current_plane);
                if (result != success) {
                    current_plane.refuse();
                }
            }
            else {
                // If the takeoff queue is not empty, handle landings instead
                Error_code result = runway->can_land(current_plane);
                if (result != success) {
                    current_plane.refuse();
                }
            }
        }
    }
}

// large airport with three runways, one for primary landings, one for primary takeoffs, and one for primary landings with exceptions
void handleAllRunways(int current_time, int flight_number,
    Runway* runway1, Runway* runway2, Runway* runway3, int number_arrivals, int number_departures) {
    // Landings on runway1 (reserved for landings)
    handleLandingOnly(current_time, flight_number, runway1, number_arrivals);

    // Takeoffs on runway2 (reserved for takeoffs)
    handleTakeoffOnly(current_time, flight_number, runway2, number_departures);

    // Use runway3 for landings unless landing queue is empty or more than 1 plane is waiting to land
    if (runway1->landing_queue.size() > 1) {
        std::cout << "Landing queue has more than one plane. Handling landings on runway3" << std::endl;
        handleLandingPrimary(current_time, flight_number, runway3, number_arrivals, 0);
    } else if (runway3->landing_queue.empty()) {
        std::cout << "Landing queue is empty. Handling takeoffs on runway3" << std::endl;
        handleTakeoffPrimary(current_time, flight_number, runway3, 0, number_departures);
    }
}

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

// Function to print the results of the simulation, calls runway statistics from object runway
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
            total_planes_queued_land_remain += current_runway->getQueueLandSize();
            total_planes_queued_takeoff_remain += current_runway->getQueueTakeoffSize();


            // Print the statistics of the current runway
            cout << endl;
            cout << "Runway statistics of Runway " << i + 1 << ":" << endl;
            cout << *current_runway << endl; // Note the use of *
            delete current_runway; // Delete the runway object
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
    std::cout << "Total number of planes left in landing queue: " << total_planes_queued_land_remain << std::endl;
    std::cout << "Total number of planes left in takeoff queue: " << total_planes_queued_takeoff_remain << std::endl;
    std::cout << "Percentage of time runway idle: " << (100.0 * total_idle_time) / end_time << "%" << std::endl;
    std::cout << "Average wait in landing queue: " << ((float)total_land_wait) / total_landings << " time units" << std::endl;
    std::cout << "Average wait in takeoff queue: " << ((float)total_takeoff_wait) / total_takeoffs << " time units" << std::endl;
    std::cout << "Average observed rate of planes wanting to land: " << ((float)total_land_requests) / end_time << " per time unit" << std::endl;
    std::cout << "Average observed rate of planes wanting to take off: " << ((float)total_takeoff_requests) / end_time << " per time unit" << std::endl;

}

void Airport::initialize(int version) {
    cout << "Defining test units to start test." << std::endl;
    cout << "One plane can land or depart in each unit of time." << std::endl;
    cout << "If airport has one runway it can handle 1 land or takeoff eatch time unit" << std::endl;

    // Queue limit set by user here
    cout << "Up to what number of planes can be waiting to land "
            "or take off at any time? :" << std::flush;
    cin >> queue_limit;

    // Simulation time set by user here
    cout << "How many units of time will the simulation run? :" << std::flush;
    cin >> end_time;
    end_time = end_time + 1;

    bool acceptable;
    bool continue_input = true;

    cout << "#################################################################################################" << endl;
    cout << endl;
    do {
        cout << "Airport has ";
        if (version == 1) {
            cout << "one runway for landing and takeoff." << endl;
            cout << "Recommended combined rate (arrival+departing) is 1." << endl;
        } else if (version == 2) {
            cout << "two runways. One for landing, second for departing." << endl;
            cout << "Recommended rates are 1 for arrivals and 1 for departures." << endl;
        } else if (version == 3) {
            cout << "two runways. One for primary landing, second for primary departing with exceptions." << endl;
            cout << "Recommended combined rate (arrival+departing) is 2." << endl;
        } else if (version == 4) {
            cout << "three runways. One for landing primary, second for departing, third for primary landing with exceptions." << endl;
            cout << "Recommended combined rate (arrival+departing) is 3." << endl;
        }

        if (version == 4) {
            cout << "Expected number of arrivals per unit time? (rate 0-3) :";
        } else if (version == 3) {
            cout << "Expected number of arrivals per unit time? (rate 0-2) :";
        } else {
            cout << "Expected number of arrivals per unit time? (rate 0-1) :";
        }

        cin >> arrival_rate;
        if (arrival_rate < 0) {
            continue_input = false;
            break;
        }

        if (version == 4) {
            cout << "Expected number of arrivals per unit time? (rate 0-2) :";
        } else {
            cout << "Expected number of arrivals per unit time? (rate 0-1) :";
        }

        cin >> departure_rate;
        if (departure_rate < 0) {
            continue_input = false;
            break;
        }

        if (arrival_rate + departure_rate > 10) {
            cerr << "Error: Arrival and departure rates exceed maximum. (10)" << endl;
            continue;
        }

        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            cerr << "Error: Arrival and departure rates must be nonnegative." << endl;
            continue;
        }

        acceptable = true;
    } while (!acceptable && continue_input);
}

