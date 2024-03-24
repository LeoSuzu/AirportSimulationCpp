//
// Created by Leo Suzuki on 18.3.2024.
//

#ifndef RANDOM_H
#define RANDOM_H

#include "Utility.h"



const int max_int = INT_MAX;

class Random {
public:
   Random(bool pseudo = true);

   // Declare random-number generation methods here.
   int random_integer(int low, int high);
   double random_real();
   int poisson(double mean);

private:
   int reseed(); //  Re-randomize the seed.
   int seed, multiplier, add_on; //  constants for use in arithmetic operations
};



#endif //RANDOM_H
