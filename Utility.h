//
// Created by Leo Suzuki on 18.3.2024.
//

#ifndef UTILITY_H
#define UTILITY_H


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <queue>
#include <random>

#include <random>
#include <iostream>

using namespace std;

enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error
};

class Utility {
public:
	Utility();
	static bool user_says_yes();

	// Function to generate random number from Poisson distribution
	int poissonGenerator(double mean);
private:
	std::default_random_engine generator; // Random number generator
};
#endif //UTILITY_H
