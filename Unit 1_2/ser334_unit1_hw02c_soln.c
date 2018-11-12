////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <string.h>

//macros: constants
#define CHUNK_LENGTH (20+1)  //each chunk has twenty characters, we add 1 so
						   //there is space for the null terminator.
#define NUMBER_OF_CHUNKS 4 //the message is spread across 4 chunks.
#define DECRYPTION_SHIFT 5 //this is the ASCII table shift used for decryption.

//forward declarations
void sort_chunks();
void decrypt_chunks();
void display_chunks();

char chunks[NUMBER_OF_CHUNKS][CHUNK_LENGTH];

int main()
{
	//copy message into memory.
	strcpy(chunks[0], "2i1%fsi%fs%jstwrtzx%");
	strcpy(chunks[1], "1'H%nx%vznwp~1%kqf|j");
	strcpy(chunks[2], "4R3%Wnyhmnj%%%%%%%%%");
	strcpy(chunks[3], "3xzhhjxx3'%2%Ijssnx%");

	//the format of a chunk is a single number indicating its order in overall
	//message followed by twenty encrypted characters.


	//reorder chunks in message by sorting them based on the first digital
	//they contain. looking above, one can see they are currently in the order
	//2, 1, 4, 3 but should be ordered 1, 2, 3, 4. 
	sort_chunks();

	//shift the characters in the message to produce the original characters.
	decrypt_chunks();

	//display the decrypted message.
	display_chunks();


	return 0; 
}

//given two strings, swaps their contents in memory.
void swap_strings(char* x, char* y)
{
	//create a temporary holding place for the data so we don't lose it.
	char temp[CHUNK_LENGTH];

	strcpy(temp, x);
	strcpy(x, y);
	strcpy(y, temp);
}

//sorts the strings the global chunks variable by the first character they contain.
void sort_chunks()
{
	int follower, active;
	int index_minimum;

	//loop over each string that needs to be sorted
	for (active = 0; active < NUMBER_OF_CHUNKS; active++)
	{	
		//we need to find the minimum ordered element, then by placing it first we
		//know it will be in its sorted position.

		//assume the first thing we see is the minimum.
		index_minimum = active;

		//loop over ever element that follows it.
		for (follower = active + 1; follower < NUMBER_OF_CHUNKS; follower++)
		{
			//fetch the ids from the chunks - these specify order.
			int follower_id = chunks[follower][0];
			int minimum_id = chunks[index_minimum][0];
			
			//if we encounter a chunk with a lower id, then we remember it.
			if (follower_id < minimum_id)
				index_minimum = follower;
		}

		//whatever element we found had the lowest id is moved to the active
		//position. that element is now in its final sorted position.
		swap_strings(chunks[active], chunks[index_minimum]);
	}
}

//for each string in the global chunks variable, shifts the characters in it by
//DECRYPTION_SHIFT.
void decrypt_chunks()
{
	int i, j;

	//loop over each string that needs to be decrypted
	for(i = 0; i < NUMBER_OF_CHUNKS; i++)
	{
		//store a pointer to the active string
		char* str = chunks[i];

		//loop over every character in the active string except the terminator
		for(j = 0; j < CHUNK_LENGTH - 1; j++)

			//get the character and subtract DECRYPTION_SHIFT. Since this is C,
			//this causes the character's ASCII character number to change. It
			//remains a character but is shifted in the ASCII table.
			*(str + j) = *(str + j) - DECRYPTION_SHIFT;
	}
}

//displays the strings in the global chunks variable
void display_chunks()
{
	int i;

	for(i = 0; i < NUMBER_OF_CHUNKS; i++)
	{
		//since chunks[i] is a pointer to the first character in the string,
		//adding one skips us past the first character.
		printf("%s", chunks[i]+1);
	}
}