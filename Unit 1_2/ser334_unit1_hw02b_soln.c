
/*
 * 	File : ser334_unit1_hw02b_soln.c
 *	Created on: August 29, 2017
 *	Author: Nagarjuna Kalluri
 */

////////////////////////////////////////////////////////////////////////////////
//Includes
#include <stdio.h>

// Forward declarations
int termination(int);

int main(void){

	int input;

	// Getting input from the user
	printf("\n Please enter a number : ");
	scanf("%d",&input);

	// Checking for positive integers
	if(input > 0){
		// Calling termination from main on an input integer given by the user
		input = termination(input);

		printf("\n The input number is reduced to %d \n\n", input);
	}
	else{
		printf("\n The input number does not satisfy collatz conjecture \n\n");
	}

	return 0;
}

// Termination program
int termination(int input){

	int count = 0;

	// Algorithm Implementation
	while(input != 1){
		if(input %2 == 0){
			// Even Number
			input /= 2;
		}
		else{
			// Odd Number
			input = 3*input + 1;
		}
		// Incrementing the iteration count
		count++;
	}

	// Displaying how many iterations are executed for the input
	printf("\n The number of iterations required for '%d' to satisfy the collatz conjecture is : %d \n",input, count);

	return input;
}
