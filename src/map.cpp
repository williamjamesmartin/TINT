#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "species.h"

int main()
{
	double map[50][50];
	
	Species one;

	one.initiateSpecies(20);

	srand (time(NULL));

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
		{			
			if ((rand() % 100 + 1) > 90)
			{
				map[i][j] = 1;
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
