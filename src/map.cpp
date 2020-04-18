#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "species.h"

int map[20][20];

int main()
{
	int speciesMax = 20;
	int applier;
	int speciesCount = 2;
	Species one;

	one.initiateSpecies(speciesMax);

	srand (time(NULL));

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
			//initializes a 50 x 50 square map by setting random points of a resource or "food" denoted by a 1. All other points are empty as denoted by the number 0 
		{	
			applier = rand() % 10 + 1;					
			
			if (applier >= 9)
			{
				map[i][j] = 1;
			}
			else if (applier >= 7 && applier < 9)
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

	void takeStep(Species x, int y, int i, int j)	//determines actions based on vision in front of an individual
	{
		double v = x.list[y-2][3];

			for(int index = i - (int)ceil(v); index < i + (int)ceil(v); index++)
			{
				for(int ind = j - (int)ceil(v); ind < j + (int)ceil(v); ind++)
				{
					if(index == i && ind == j) 			//if map[i][j], pass
					{
						continue;
					}
					
					else if(map[index][ind] == 1)		//Consume resource
					{
						map[i - (int)ceil(v)][j - (int)ceil(v)] = map[i][j];
						map[i][j] = 0;
						x.list[(double)y][4]++;
					}

					else if(map[index][ind] >= 2)		//Special encounter. Better speed wins out
					{
						if(x.list[y-2][2] > x.list[map[index][ind]-2][2])
						{
							map[i - (int)ceil(v)][j - (int)ceil(v)] = map[i][j];	//right now this code kills the slower species **will fix**
							map[i][j] = 0;
							x.list[(double)y][4]++;
						}

						else
						{
							continue;
						}
					}
				}
			}
	}

	void nextEpoch(Species x, int y, int i, int j)	//applies the takeStep function to every species on the map
	{
		for (int i = 0; i < (sqrt(sizeof(map) / 4)); i++)
		{
			for (int j = 0; j < (sqrt(sizeof(map) / 4)); j++)
			{
				if (map[i][j] >= 2)
				{
					takeStep(x,y,i,j);
				}
			}
		}
	}