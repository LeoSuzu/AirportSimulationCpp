//
// Created by Leo Suzuki on 18.3.2024.
//

#include "Utility.h"

Utility::Utility() {
	generator.seed(42); // USE THIS FOR REAL RANDOMNESS std::random_device()()
}

int Utility::poissonGenerator(double mean) {
	std::poisson_distribution<int> poisson_dist(mean);
	return poisson_dist(generator);
}

bool Utility::user_says_yes()
{
	int c;
	bool initial_response = true;

	do {  //  Loop until an appropriate input is received.
		if (initial_response)
			cout << " (y,n)? " << flush;

		else
			cout << "Respond with either y or n: " << flush;

		do { //  Ignore white space.
			c = cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');
		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}


