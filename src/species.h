#ifndef SPECIES_H
#define SPECIES_H

class Species
{
	public:
		float size;
		float visibility;
		float strength;

		void initiateSpecies()
		{
				srand (time(NULL));

				size = rand() % 10 + 1;

				strength = 10 - size;

				visibility = rand() % 3 + 1;
		}

		void printTraits()
		{
			std::cout << size << ' ';

			std::cout << strength << ' ';
			
			std::cout << visibility << '\n';
		}
};

#endif

