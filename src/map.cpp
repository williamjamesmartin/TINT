#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "species.h"

int main()
{
	int map[20][20];
	int speciesMax = 20;
	int applier;
	int speciesCount = 2;
	Species one;

	one.initiateSpecies(speciesMax);

	srand (time(NULL));

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
		{	
			applier = rand() % 10 + 1;					
			
			if (applier >= 9)
			{
				map[i][j] = 1;
			}
			else if (applier >= 7 && applier <= 9)
			{
				if (speciesCount < (2 + speciesMax))
				{
					map[i][j] = speciesCount;

					speciesCount++;
				}
				else
				{
					map[i][j] = 0;
				}	
			}
			else
			{
				map[i][j] = 0;
			}
			
			std::cout << map[i][j] << ' ';	
		}

		std::cout << '\n';
	}

	return 0;
}
