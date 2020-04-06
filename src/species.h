#ifndef SPECIES_H_
#define SPECIES_H_

class Species
{
	public:
		int size;
		int visibility;
		int strength;

		void initiateSpecies()
		{
				srand (time(NULL));

				speciesLocator

				size = rand() % 10 + 1;

				strength = 10 - size;

				visibility = rand() % 3 + 1;
		}

		void printTraits()
		{
			std::cout << size << ' ';

			std::cout << strength << ' ';
			
			std::cout << visibility << ' ';

			std::cout << speciesNum << '\n';
		}
};

class speciesLocator
{
	public:
		std::vector<int> list;
};

#endif
