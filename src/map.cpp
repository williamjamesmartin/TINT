#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "species.h"
#include <algorithm>
#include <fstream>

int map[30][30];
int speciesCount = 2;	//had to make this global to iniate species in the takeStep function

bool checkMate(Species& x, int a, int b)		//returns True or False depending on whether or not species b is a potential mate
{
	double hungera = x.list[a-2][4];

	double hungerb = x.list[b-2][4];

	if(abs(x.list[a-2][1] - x.list[b-2][1]) < x.list[a-2][1]*0.1 && hungera > 10 && hungerb > 10)		//within 10% of the original value
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

					for(int spawn = i - (int)ceil(v); spawn < i + (int)ceil(v); spawn++)
					{
						for(int egg = j - (int)ceil(v) - (int)ceil(v); egg < j + (int)ceil(v); egg++)
						{
							if(spawn == i && egg == j) 		//if map[i][j], pass
							{
								continue;
							}
							else if(spawn < 0 || egg < 0 || spawn > (sqrt(sizeof(map)/4) - 1) || egg > (sqrt(sizeof(map)/4) - 1)) 		//check bounds for when map[i][j] is in a corner or edge, avoids segmentation error
							{
								continue;
							}
							else if(map[spawn][egg] == 0)
							{
								map[spawn][egg] = speciesCount;	//gives birth to offspring in nearest empty space
								speciesCount++;
								goto loopEnd;
							}
						}
					}
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
	std::vector<int> fileTester;
	int fileCounter = 0;

	one.initiateSpecies(speciesMax);

	srand (time(NULL));

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
			//initializes a square map by setting random points of a resource or "food" denoted by a 1. All other points are empty as denoted by the number 0 
		{	
			applier = rand() % 100 + 1;					

			if (applier >= 80)
			{
				map[i][j] = 1;
			}
			else if (applier >= 76 && applier < 80)
			{
				if (speciesCount < (speciesMax + 2))
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

	for (int i = 0; i < 20; i++)
	{
		nextEpoch(one);
		
		for (int k = 0; k < (sqrt(sizeof(map)/4)); k++)
		{
			for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
			{
				applier = rand() % 100 + 1;

				if (applier > 95 && map[k][j] == 0)
				{
					map[k][j] = 1;
				}		
			}
		}
		
		one.printSpecies();

		std::cout << speciesCount << std::endl;
	}

	std::ofstream myFile("output.csv", std::ios::app);

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
		{
			if (map[i][j] >= 2)
			{
				myFile << one.list[map[i][j]-2][0] << "," << one.list[map[i][j]-2][1] << "," << one.list[map[i][j]-2][3] << "," << 1 << std::endl;

				fileTester.push_back(map[i][j]-2);
			}
		}
	}
	
	for (int i = 0; i < one.list.size(); i++)
	{
		for (int k = 0; k < fileTester.size(); k++)
		{
			if (i != fileTester[k])
			{
				fileCounter++;
			}
		}
		
		if (fileCounter == fileTester.size())
		{
			myFile << one.list[i][0] << "," << one.list[i][1] << "," << one.list[i][3] << "," << 0 << std::endl;
		}

		fileCounter = 0;
	}

	myFile.close();

	return 0;
}
