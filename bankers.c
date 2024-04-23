#include <stdio.h>

#define PROCESSES 5
#define RESOURCES 3

int ans[PROCESSES];
int flag[PROCESSES] = {0,0,0,0,0};

int allocated[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix
                { 2, 0, 0 }, // P1
                { 3, 0, 2 }, // P2
                { 2, 1, 1 }, // P3
                { 0, 0, 2 } }; // P4

int max_req[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix
              { 3, 2, 2 }, // P1
              { 9, 0, 2 }, // P2
              { 2, 2, 2 }, // P3
              { 4, 3, 3 } }; // P4

int available[3] = { 3, 3, 2 }; // Available Resources

int idx = 0;	// Index for ans
int iteration_flag=0;	// Check if there is any execution in a loop

int main()
{
	do
	{
		iteration_flag = 0;	// Set to 0 in every loop
		for (int i = 0; i < PROCESSES; i++)
		{
			if (flag[i] == 0)
			{
				flag[i] = 1;
				int need[RESOURCES];
				for (int j = 0; j < RESOURCES; j++)
				{
					need[j] = max_req[i][j] - allocated[i][j];
					if (need[j] > available[j])
					{
						flag[i] = 0;
						break;
					}
				}
				if (flag[i] == 1)
				{
					for(int k = 0; k < RESOURCES; k++)
					{
						available[k] = available[k]+allocated[i][k];			
					}	
					ans[idx] = i;	
					idx++;
					iteration_flag = 1;	
				}
			}
		}
	}while (iteration_flag==1);
	
	for (int i = 0; i < PROCESSES; i++)
	{
		if (flag[i] == 0)
		{
			printf("Safe state not possible");
			return -1;	
		}		
	}
	
	printf("Safe state is: ");
	for (int i = 0; i < PROCESSES - 1 ; i++)
	{
		printf("P%d->",ans[i]);
	}
	printf("P%d\n", ans[PROCESSES-1]);
	return 0;
}
