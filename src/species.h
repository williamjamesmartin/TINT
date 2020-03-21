#include <stdlib.h>
#include <time.h>
#include <iostream>

class Species
{
	public:

	int size;
	int strength;
	
	void initiateSpecies()
	{
        	srand (time(NULL));

	        size = rand() % 10 + 1;

			strength = 10 - size;
	}

	void printTraits()
	{
		std::cout << size << ' ';

		std::cout << strength << ' ';
	}
};


