#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "ctype.h"

int result_size;
int number_size;

/* Take user input and process depending on cases below

Case 0: Input is a positive number with no leading 0s
  Convert input into reverse order array of its digits.
Case 1: Input is positive but has leading 0s.
  Convert input into reverse order array of its digits.
  Once input is converted into the array number leading 0s are stripped off.
Case 2: Input is 0 or many 0s.
  Convert input into reverse order array of its digits.
  All 0s will then be stripped off leaving an empty output with number_size = 0.
Case 3: Input is a negative number.
  Each char of the input is checked with isdigit().
  "-" will not pass isdigit().
  Set number_size to -1 to handle output in main().
Case 4: Input contains none digit numbers.
  Acts the same as Case 3. */
int* array_convert()
{
  char number[400];
  scanf("%s", number);
  number_size = strlen(number);
  int* ptr = calloc(number_size, sizeof(int));
  for (int i = (number_size - 1); i > -1; i--)
  {
    if (isdigit(number[i]) > 0)
    {
      ptr[number_size - 1 - i] = (int)(number[i] - '0');
    }
    else
    {
      printf("ERROR: Input is not a positive integer or 0\n");
      number_size = -1;
      return ptr;
    }
  }

  // Get rid of leading 0s in input
  for (int i = (number_size - 1); i > -1 ; i--)
  {
    if (ptr[i] == 0)
    {
      (number_size)--;
    }
    else
    {
      break;
    }
  }
  ptr = realloc(ptr, (number_size * sizeof(int)));

  return ptr;
}

// Subracts 1 from array number using long subtraction method
int* number_subtract(int* num)
{
  num[0]--;
  for (int i = 0; i < number_size - 1; i++)
  {
    if (num[i] < 0)
    {
      num[i] = 9;
      num[i+1]--;
    }
    else
    {
      return num;
    }
  }

  //check if subtractions left a leading 0 and get rid of it
  if (num[number_size - 1] == 0)
  {
    number_size--;
    num = realloc(num, (number_size * sizeof(int)));
  }
  return num;
}

// Multiplies two array numbers using column multiplication method
int* number_multiply(int* num1,int digits_num1, int* num2, int digits_num2)
{
  // Determine maximum size of result
  result_size = digits_num1 + digits_num2;
  int* result = (int*)calloc(result_size, sizeof(int));

  for (int i = 0; i < digits_num2; i++)
  {
    for (int j = 0; j < digits_num1; j++)
    {
      result[i+j] += num2[i] * num1[j];
      // Check whether to carry over and do so if needed
      int mod = floorf(result[i+j] / 10);
      result[i+j+1] += mod;
      result[i+j] -= 10 * mod;
    }
  }

  //Get rid of leading 0s
  for (int i = (result_size - 1); i > -1 ; i--)
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
  result = realloc(result, (result_size * sizeof(int)));
  free(num2);
  return result;
}

int main()
{
  // Take in user input and convert to array number_ptr
  printf("Enter a number to factorial: ");
  int* number_ptr = array_convert();
  int* result_ptr;

  // Check what case the input satified
  if (number_size == -1)
  {
    // Input was not an allowed number
    return 0;
  }
  else if (number_size == 0)
  {
    // Input was 0
    result_ptr = malloc(sizeof(int));
    result_size = 1;
    result_ptr[0] = 1;
  }
  else
  {
    /* Input was an allowed number.
    Copy number into result then take away 1 from number and begin loop which
    sucessively multiplies result by number and takes 1 away from number until
    number is 0 to calculate the factorial. */
    result_ptr = malloc(number_size * sizeof(int));
    result_size = number_size;
    memcpy(result_ptr, number_ptr, number_size * sizeof(int));
    number_ptr = number_subtract(number_ptr);
    while (number_size > 0)
    {
      result_ptr = number_multiply(number_ptr, number_size, result_ptr, result_size);
      number_ptr = number_subtract(number_ptr);
    }
  }

  //Print resulting factorial
  for (int i = (result_size - 1); i > -1; i--)
  {
    printf("%d", result_ptr[i]);
  }
  printf("\nDigits = %d\n", result_size);
  free(number_ptr);
}
