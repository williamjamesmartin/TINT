#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "species.h"
#include <algorithm>

int map[30][30];
int speciesCount = 2;	//had to make this global to iniate species in the takeStep function

bool checkMate(Species& x, int a, int b)		//returns True or False depending on whether or not species b is a potential mate
{
	int hungera = x.list[a-2][4];

	int hungerb = x.list[b-2][4];

	if(abs(x.list[a-2][1] - x.list[b-2][1]) < x.list[a-2][1]*0.5 && hungera > 10 && hungerb > 10)		//within 10% of the original value
    {
		return true;
	}
	else
	{
		return false;
	}
}

void takeStep(Species& x, int id, int i, int j)		//determines actions based on vision in front of an individual
{
	double v = x.list[id-2][3];						//vision stat

	double initialHunger = x.list[id-2][4];			//hunger before moving

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
				x.incHunger(id-2);
				goto loopEnd;						//using a break statement in this case would only break out of the innermost loop. goto is the most efficient
			}
			else if(map[index][ind] >= 2)			//Special encounter
			{
				if(checkMate(x,id,map[index][ind]))
				{
					x.initOffspring(speciesCount, id-2, map[index][ind]-2);
					x.decHunger(id-2);
					speciesCount++;
					
					for(int index = i - (int)ceil(v); index < i + (int)ceil(v); index++)
					{
						for(int ind = j - (int)ceil(v) - (int)ceil(v); ind < j + (int)ceil(v); ind++)
						{
							if(map[i][j] == 0)
							{
								map[i][j] = speciesCount;	//gives birth to offspring in nearest empty space
							}
						}
					}
					
					goto loopEnd;
				}
				else if(x.list[id-2][1] > x.list[(map[index][ind])-2][1])	//Better size wins out
				{
					map[index][ind] = id;			//kills the smaller species
					map[i][j] = 0;
					x.incHunger(id-2);
					goto loopEnd;
				}
			}
		}
	}

	if(x.list[id-2][4] == initialHunger)	//in the case of running through the whole loop and finding no food
	{
		x.decHunger(id-2);

		if(x.list[id-2][4] == 0)			//dies of hunger
		{
			map[i][j] = 0;
		}
	}

	loopEnd: ;									//does nothing, ends loop
		
}	

void nextEpoch(Species& x)		//applies the takeStep function to every species on the map
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
	Species one;

	one.initiateSpecies(speciesMax);

	srand (time(NULL));

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
			//initializes a 50 x 50 square map by setting random points of a resource or "food" denoted by a 1. All other points are empty as denoted by the number 0 
		{	
			applier = rand() % 100 + 1;					

			if (applier >= 90)
			{
				map[i][j] = 1;
			}
			else if (applier >= 88 && applier < 90)
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

	nextEpoch(one);
	nextEpoch(one);
	nextEpoch(one);
	nextEpoch(one);
	nextEpoch(one);
	nextEpoch(one);
	nextEpoch(one);

	return 0;
}