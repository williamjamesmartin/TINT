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
		double posTest;

		void initiateSpecies(int x)
		{
			srand (time(NULL));
			
			for (int i = 0; i < x; i++)
				//initiates a species by giving it random traits such as size, speed and vision where size and vision are inversely proportional

			{
				std::vector<float> temp;

				size = ((double) rand() / (RAND_MAX)) * 5;

				speed = ((double) rand() / (RAND_MAX)); // Unused variable, for further development

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

		void initOffspring(int count, int a, int b)
		{
			std::vector<float> temp;

			posTest = rand() % 1 + (-1);
			
			if(posTest > 0)
			{
				size = ((list[a][1] + list[b][1])/2) * ((double) rand() / (RAND_MAX)) * 0.1;

				speed = ((list[a][2] + list[b][2])/2) * ((double) rand() / (RAND_MAX)) * 0.1;

				vision = ((list[a][3] + list[b][3])/2) * ((double) rand() / (RAND_MAX)) * 0.1;

				hunger = 10;

				temp.push_back(count);

				temp.push_back(size);

				temp.push_back(speed);

				temp.push_back(vision);

				temp.push_back(hunger);

				list.push_back(temp);
			}
			else
			{
				size = ((list[a][1] + list[b][1])/2) * -((double) rand() / (RAND_MAX)) * 0.1;

				speed = ((list[a][2] + list[b][2])/2) * -((double) rand() / (RAND_MAX)) * 0.1;

				vision = ((list[a][3] + list[b][3])/2) * -((double) rand() / (RAND_MAX)) * 0.1;

				hunger = 10;

				temp.push_back(count + 1);

				temp.push_back(size);

				temp.push_back(speed);

				temp.push_back(vision);

				temp.push_back(hunger);

				list.push_back(temp);
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

		void incHunger(int i)
		{
			list[i][4]++;
		}
		
		void decHunger(int i)
		{
			list[i][4]--;
		}

};

#endif
