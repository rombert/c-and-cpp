#include <stdio.h>
#include <stdlib.h>

// returns the maximum element from an array
int max(int elements[], int size);
// calculates the fibonacci sequence up for n using a recursive algorithm
int fibonacci_recursive(int n);
// calculates the fibonacci sequence up for n using an iterative algorithm
int fibonacci_iterative(int n);
void harness_search(int haystack[], int size, int needle, char* description, int(*impl)(int haystack[], int size, int needle));
// searches for an element in an array and returns the position ( -1 if not found )
int search(int haystack[], int size, int needle);
// binary search
int search_binary(int haystack[], int size, int needle);

int main(int argc, char* argv[])
{
	int input[] = { 5, -1, 4, 12 };
	int input_size = 4;

	int input_sorted[] = { -4, 1, 22, 66, 89, 120, 238 };
	int input_sorted_size = 7;
	
	// 2. function pointers
	// direct invocation
	printf("Max is %d\n", max(input, input_size));
	// function pointer invocation
	int(*sortfunc)(int elements[], int size) = max;
	printf("Max (function pointer) %d\n", sortfunc(input, input_size));

	// 3. recursivity
	printf("recursive fibonacci(12) = %d\n", fibonacci_recursive(12));
	printf("iterative fibonacci(12) = %d\n", fibonacci_iterative(12));

	// 4. search
	// 4a. simple search 
	harness_search(input, input_size, 4, "search", search);
	harness_search(input, input_size, 2, "search", search);
	// 4b. binary search
	harness_search(input_sorted, input_sorted_size, 89, "search_binary", search_binary);
	harness_search(input_sorted, input_sorted_size, 500, "search_binary", search_binary);
	harness_search(input_sorted, input_sorted_size, -40, "search_binary", search_binary);
	harness_search(input_sorted, input_sorted_size, 140, "search_binary", search_binary);

	return 0;
}

int max(int elements[], int size)
{
	if (size < 1) 
	{
		return NULL;
	}

	int max = elements[0];
	for (int i = 1; i < size; i++)
	{
		if (elements[i] > max)
		{
			max = elements[i];
		}
	}

	return max;
}

int fibonacci_recursive(int n)
{
	if (n == 0 || n == 1)
	{
		return n;
	}

	return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_iterative(int n)
{

	// TODO - should be possible to use it in a queue manner and only hold the last 2 values
	int* accumulator = (int *) malloc( (n+1) * sizeof(int)) ;

	for (int i = 0; i <= n; i++)
	{
		if (i == 0 || i == 1)
		{
			accumulator[i] = i;
		}
		else {
			accumulator[i] = accumulator[i - 1] + accumulator[i - 2];
		}
	}

	int result = accumulator[n];

	free(accumulator);

	return result;
}

void harness_search(int haystack[], int size, int needle, char* description, int(*impl)(int haystack[], int size, int needle)) {
	printf("%s(%d) = %d\n", description, needle, impl(haystack, size, needle));
}

int search(int haystack[], int size, int needle)
{
	int i;
	// loop until either we reach the end OR find the needle in the haystack
	for (i = 0; i < size && haystack[i] != needle; i++);

	// if position is smaller than size, then we found the needle ; otherwise return -1
	return i < size ? i : -1;
}

int search_binary_helper(int haystack[], int left, int right, int needle)
{
	if (left > right) {
		return -1;
	}

	int mid = (left + right) / 2;
	int mid_value = haystack[mid];

	// key has been found
	if (mid_value == needle)
	{
		return mid;
	} // key is in upper subset
	else if (mid_value < needle)
	{
		return search_binary_helper(haystack, mid + 1, right, needle);
	} // key is in lower subset
	else 
	{
		return search_binary_helper(haystack, left, mid - 1, needle);
	}
}

int search_binary(int haystack[], int size, int needle) {
	return search_binary_helper(haystack, 0, size - 1, needle);
}