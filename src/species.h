#ifndef SPECIES_H_
#define SPECIES_H_

class Species
{
	public:
		std::vector<std::vector<float>> list;
		double size;
		double speed;
		double vision;

		void initiateSpecies(int x)
		{
			srand (time(NULL));

			for (int i = 0; i < x; i++)
			{
				std::vector<float> temp;

				size = abs(rand());

				speed = 1 - size;

				vision = rand() * 3;

				temp.push_back(i + 2);

				temp.push_back(size);

				temp.push_back(speed);

				temp.push_back(vision);

				list.push_back(temp);
			}
			
			for (int i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list[i].size(); j++)
				{
					cout << list[i][j];
				}
			}
		}
};

#endif
