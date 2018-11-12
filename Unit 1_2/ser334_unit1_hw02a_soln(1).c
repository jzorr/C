////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>

int main(void)
{
	float sum = 0;
	float height = 0;
	float radius = 0;
	int count = 0;

	int i = 0;

	printf("How many cylinders would you like to sum?\n");
	scanf("%i", &count);

	for(i = 0; i < count; i++)
	{
		printf("How high is cylinder %i?\n", i+1);
		scanf("%f", &height);

		printf("What is cylinder %i's radius?\n", i+1);
		scanf("%f", &radius);

		sum += height * 3.14159265 * radius * radius; //alternatively, use the pow math function.
	}

	printf("Total Sum is: %f\n", sum);

	return 0;
}