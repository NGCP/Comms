#ifndef _RANDOM_NUMBERS_H_
#define _RANDOM_NUMBERS_H_

#pragma once 

#define RANDOM_VERSION       1

namespace Random { 
#if (RANDOM_VERSION > 0)

#define SEEDXDEFAULT              3 
#define RANDOM_START              0
#define RANDOM_SPECIFIED_BOUND  255
#define NUMBER_RAND_MAX        1000
#define RANDOM_ARRAY_SIZE	   1001

/** Random Array used to store the pseudorandom numbers. */

extern int random_array[RANDOM_ARRAY_SIZE];

typedef unsigned int size_t;
/** Our Random Number Generator */
class RandomNumberGen {
   typedef unsigned char _Byte; 
   /** Stored seed for use in the number generator */
   int seed;
public:
   /** Number gen specifies seed, minimum value, and max value. */
   RandomNumberGen(int seed, int min, int max) : seed(seed) { }
   /** Number gen specifies only seed */
   RandomNumberGen(int seed) : seed(seed) { }
   RandomNumberGen(const RandomNumberGen& rand);
   RandomNumberGen(void);
   /** Generates numbers into an array randomly. */
   /* TODO(Someone): We may need to increase the bounds since it is currently
      generating only from 0 to 1000. */
   template<class _Ty>
   void generate_numbers(_Ty* _array, int start_index, int end_index) { 
      for(size_t i = start_index; i < end_index; ++i) {
         _array[i] = generate_random();
      }
   }
   /** Generates numbers into an array randomly. TODO(Someone): We need to fix the max 
       max bounds, as it is generating numbers over it. */
   template<class _Ty>
   void generate_numbers(_Ty* _array, int start_index, int end_index, int min, int max) { 
      for(size_t i = start_index; i < end_index; ++i) {
         _array[i] = (generate_random() % max) + min;
      }
   }

   int generate_number(void) { return generate_random(); }   

private:
   int generate_random(void);
   void calculate_new_seed(void);
};

typedef RandomNumberGen RandoGen;
typedef RandomNumberGen RandGen;
typedef RandomNumberGen Random;
#else
 #error Version is not compatible with this random number generator!
#endif /* RANDOM_VERSION */

} // Random namespace 
#endif /* _RANDOM_NUMBERS_H_ */
