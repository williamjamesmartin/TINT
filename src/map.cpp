#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "species.h"
#include <algorithm>

int map[20][20];

void takeStep(Species x, int id, int i, int j)		//determines actions based on vision in front of an individual
{
	double v = x.list[id-2][3];						//vision stat

	double initialHunger = x.list[id-2][4];			//hunger before moving

	std::cout << initialHunger << std::endl << std::endl;

	for(int index = i - (int)ceil(v); index < i + (int)ceil(v); index++)
	{
		for(int ind = j - (int)ceil(v) - (int)ceil(v); ind < j + (int)ceil(v); ind++)
		{
			if(index == i && ind == j) 				//if map[i][j], pass
			{
				continue;
			}
			else if(index < 0 || ind < 0 || index > (sqrt(sizeof(map)/4) - 1) || ind > (sqrt(sizeof(map)/4) - 1)) 		//check bounds for when map[i][j] is in a corner or edge, avoids segmentation error
			{
				continue;
			}
			else if(map[index][ind] == 1)			//Consume resource
			{
				map[index][ind] = id;
				map[i][j] = 0;
				x.list[(double)(id-2)][4]++;
				goto hunger;						//using a break statement in this case would only break out of the innermost loop. goto is the most efficient
			}
			else if(map[index][ind] >= 2)			//Special encounter. Better size wins out
			{
				if(x.list[id-2][1] > x.list[(map[index][ind])-2][1])
				{
					map[index][ind] = id;			//kills the smaller species
					map[i][j] = 0;
					x.list[(double)(id-2)][4]++;
					goto hunger;
				}
			}
		}
	}

	hunger:
		if(x.list[id-2][4] == initialHunger)	//in the case of running through the whole loop and finding no food
		{
			x.list[id-2][4]--;

			if(x.list[id-2][4] == 0)			//dies of hunger
			{
				map[i][j] = 0;
			}
		}
}	

void nextEpoch(Species x)		//applies the takeStep function to every species on the map
{
	std::vector<int> check;		//vector containing the ids of species that have taken a step. Array size should correspond to speciesMax

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
		{
			if (map[i][j] >= 2)
			{
				std::vector<int>::iterator it = std::find(check.begin(), check.end(), map[i][j]);
				
				if (it != check.end())	//species id found in vector, ensures that a species that has moved does not move again
				{
					continue;
				}
				else					//applies takeStep function to species and adds id to vector 'check'
				{
					int id = map[i][j];
					takeStep(x,id,i,j);
					check.push_back(id);
				}
			}
		}
	}

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)		//prints map
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
		{
			std::cout << map[i][j] << ' ';	
		}
		std::cout << '\n';
	}

	std::cout << '\n';

}

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
			applier = rand() % 100 + 1;					

			if (applier >= 97)
			{
				map[i][j] = 1;
			}
			else if (applier >= 90 && applier < 97)
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

	std::cout << '\n';

	for (int i = 0; i < 4; i++)
	{
		nextEpoch(one);

		one.printSpecies();
	}

	return 0;
}