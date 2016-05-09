#include <random_numbers.h>
#include <ctime>


namespace Random {

/** Constructor for our default constructor. */
RandomNumberGen::RandomNumberGen(void) : seed(SEEDXDEFAULT) {
   std::time_t tim = std::time(nullptr);
   seed = static_cast<size_t>(tim);
}

RandomNumberGen::RandomNumberGen(const RandomNumberGen& rand) { }

/** Generates the pseudorandom number for use. Currently only supports numbers between 0 and 1000. */
int RandomNumberGen::generate_random(void) { 
   size_t number = 0;
   size_t index = (static_cast<size_t>(seed * 51 ^ 101) | std::time(0)) % 993;
   number = random_array[index];
   calculate_new_seed();
   return number % 1000;
}

/** Calculates the new seed to be used for furthur pseudo-randomization */
void RandomNumberGen::calculate_new_seed(void) { 
   for (size_t i = 0; i < 5; ++i) { 
      seed += (i * 801233) ^ static_cast<size_t>(std::time(nullptr)) % 10217;
   } 
}
} // Random namespace 
