#ifndef SPECIES_H_
#define SPECIES_H_

class Species
{
	public:
		std::vector<std::vector<float>> list;
		double size;
		double speed;
		double vision;
		double hunger;

		void initiateSpecies(int x)
		{
			srand (time(NULL));
			
			for (int i = 0; i < x; i++)
				//initiates a species by giving it random traits such as size, speed and vision where size and vision are inversely proportional

			{
				std::vector<float> temp;

				size = ((double) rand() / (RAND_MAX)) * 5;

				speed = ((double) rand() / (RAND_MAX));

				vision = 5 - size;

				hunger = 10;

				temp.push_back(i + 2);

				temp.push_back(size);

				temp.push_back(speed);

				temp.push_back(vision);

				temp.push_back(hunger);

				list.push_back(temp);
			}
			
			for (int i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list[i].size(); j++)
				{
					std::cout << list[i][j] << '\n';
				}
				
				std::cout << '\n';
			}
		}

		void printSpecies()
		{
			for (int i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list[i].size(); j++)
				{
					std::cout << list[i][j] << '\n';
				}
				
				std::cout << '\n';
			}
		}

};

#endif
