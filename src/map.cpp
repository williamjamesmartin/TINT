#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "species.h"

int main()
{
	int map[50][50];
	
	srand (time(NULL));

	for (int i = 0; i < (sqrt(sizeof(map)/4)); i++)
	{		
		for (int j = 0; j < (sqrt(sizeof(map)/4)); j++)
		{			
			if ((rand() % 1000 + 1) > 990)
			{
				map[i][j] = 1;
			}	
			else
			{
				map[i][j] = 0;
			}
			
			std::cout << map[i][j] << " ";	
		}

		std::cout << "\n";

	}

	return 0;
}
