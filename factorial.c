#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

int result_size; //Global as it's needed to be editable in many functions
int number_size;

int* ArrayConvert() // Convert number into reverse order array of its digits
{
	char number[400];
	scanf("%s", number); //input number to find the factorial for
	number_size = strlen(number);
	int* ptr = calloc(number_size, sizeof(int)); //covert char string entries to int and store in *ptr
	for (int i = (number_size - 1); i > -1; i--)
	{
		ptr[number_size - 1 - i] = (int)(number[i] - '0'); 
	}
	return ptr;
}
	
int* NumberSubtract(int* num)//Subracts 1 from array number
{
	if (num[number_size -1] == 0)//Check is num is non zero works on premise that num will have no leading 0s
	{
		return num; //If it is dont do anything
	}
	else //Otherwise subract one from last digit
	{
		num[0]--;
		for (int i = 0; i < number_size - 1; i++) 
		{
			if (num[i] < 0) //check if the subtraction makes the value negative if yes make the value 9 and take 1 from next cell
			{
				num[i] = 9;
				num[i+1]--;
			}
			else // if the the necessary subtractions didnt make any entry <0 exit out of the function
			{
				return num;
			}
		}
		if (num[number_size - 1] == 0) //check if subtractions left a leading 0 if yes reallocate memory to get rid of it
			number_size--;
			num = realloc(num, (number_size * sizeof(int)));
			return num;

	}
}

int* NumberMultiply(int* num1,int digits_num1, int* num2, int digits_num2) //Multiplies two array numbers using column multiplication method
{
	result_size = digits_num1 + digits_num2; //determine maximum size of result
	int* result = (int*)calloc(result_size, sizeof(int));
	for (int i = 0; i < digits_num2; i++) //Column multiplication loops
	{
		for (int j = 0; j < digits_num1; j++)
		{
			result[i+j] += num2[i] * num1[j];
			int mod = floorf(result[i+j] / 10); //Check whether to carry over and do so if needed
			result[i+j+1] += mod;
			result[i+j] -= (10*mod);
			
		}
	}
	for (int i = (result_size - 1); i > -1 ; i--) //Find out how many leading 0s
	{
		if (result[i] == 0)
		{
			(result_size)--;
		}
		else
		{
			break;
		}
	}
	result = realloc(result, (result_size * sizeof(int))); //Reallocate memory to get rid of leading 0s
	free(num2);
	return result;
}

int main()
{
	printf("Enter a number to factorial: "); //Input number to find the factorial for

	int* number_ptr = ArrayConvert();
	int* result = malloc(number_size*sizeof(int));
	result_size = number_size;
	memcpy(result, number_ptr, number_size * sizeof(int)); //Store input number in n *result
	number_ptr = NumberSubtract(number_ptr); //Make *number_ptr store n-1

	while (number_size>0) //Carry out factorial calculation
	{
		result = NumberMultiply(number_ptr, number_size, result, result_size);
		number_ptr = NumberSubtract(number_ptr);
	}

	for (int i = (result_size - 1); i > -1; i--)
	{
		printf("%d", result[i]);
	}

	printf("\nDigits = %d\n", result_size);
	free(number_ptr);
}




