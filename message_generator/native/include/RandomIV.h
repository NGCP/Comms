#ifndef RANDOMIV_H
#define RANDOMIV_H

//#include <random>
#include <stdlib.h>
using namespace std;

class RandomIV
{
private:

	int min;
	int max;

	/** Random IV*/
	//std::random_device rd;
	//std::mt19937 mt;
	//std::uniform_int_distribution<int> distribution;

	unsigned char next()
	{
		return rand() % 255;
		//return  distribution(mt);
	}

public:
	RandomIV(int min, int max)
	{		
		//mt = mt19937(rd);
		//distribution = uniform_int_distribution<int>(min, max);
	}

	~RandomIV()
	{
		
	}

	void randomIV(unsigned char arr[], int size)
	{
		for (int x = 0; x < size; x++)
		{
			arr[x] = next();
		}
	}


};


static RandomIV gRandomIV = RandomIV(0, 255);
#endif