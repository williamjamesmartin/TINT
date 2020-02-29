#include <iostream>
#include <stdio.h>
#include <time.h>

int main()
{

	int arr[50][50];
	
	srand (time(NULL));

	int width = 50, height = 50;

	for (int i = 0; i < width; i++)
	{
		
		for (int j = 0; j < height; j++)
		{
			
			if ((rand() % 10 + 1) > 9)
			{
				arr[i][j] = 1;
			}	
			else
			{
				arr[i][j] = 0;
			}
					
			
			std::cout << arr[i][j];	
		}

	}

	return 0;

}
