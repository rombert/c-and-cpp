#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	char* nume;
	int grupa;
	int an_studiu;
} STUDENT;

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
// merge sort
void sort_merge(int haystack[], int size);
// write a fixed-size matrix to a file
void write_matrix_to_file(int matrix[4][4], char* file_name);
// read a fixed-size matrix from a file
void read_matrix_from_file(int matrix[4][4], char* file_name);
// append a student's data to the file
void student_append(STUDENT student, char* file_name);
// print all students to STDOUT
void student_print_all(char* file_name);
// finds ecuation root using the bisection method
float bisection(float a, float b, float(*fun)(float x));
// equation for the bisection method
float equation(float x);

int gcd(int a, int b);

//
// Utilities
//

// prints all values of an array
void print_array(int values[], int size);
// print all values of a (fixed-size) matrix
void print_matrix(int matrix[4][4]);

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

	// 4. merge
	int to_sort[] = { 9, -1, 3, 11, 4, 99, 11, 0 };
	int to_sort_size = 8;

	printf("Performing merge sort\n");
	printf("- unsorted: ");
	print_array(to_sort, to_sort_size);
	sort_merge(to_sort, to_sort_size);
	printf("- sorted: ");
	print_array(to_sort, to_sort_size);

	// 5. file access
	int matrix[4][4] = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ -1, -2, -3, -4 },
		{ 9, 78, 12, -1 }
	};
	write_matrix_to_file(matrix, "matrix.txt");
	int matrix_out[4][4];
	read_matrix_from_file(matrix_out, "matrix.txt");
	printf("Matrix read from file:\n");
	print_matrix(matrix_out);

	// 6/7. binary file access
	// delete 'db' before using
	unlink("students.dat");
	STUDENT student1;
	student1.an_studiu = 1;
	student1.grupa = 1014;
	student1.nume = "Salut";

	STUDENT student2;
	student2.an_studiu = 2;
	student2.grupa = 1084;
	student2.nume = "Pa";
	
	student_append(student1, "students.dat");
	student_append(student2, "students.dat");

	student_print_all("students.dat");

	// XX. bisection method
	// f(x) = x^3 - x - 2
	// f(1) = -2
	// f(2) = -4
	int res = bisection(1, 2, equation);
	printf("Bisected x to be %d\n", res);

	printf("GCD: %d\n", gcd(299792458, 6447287));

	return EXIT_SUCCESS;
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

int search_binary(int haystack[], int size, int needle) 
{
	return search_binary_helper(haystack, 0, size - 1, needle);
}

void sort_merge_helper_merge(int haystack[], int left, int mid, int right)
{
	// i is index for haystack[left;mid]
	// j is index for haystack[mid+1;right]
	// k is index for buffer
	int i, j, k; 
	int* buffer = (int*) malloc((right - left + 1) * sizeof(int));

	// IMPL note: haystack elements are processed [left; right]
	// while buffer elements are processed [0; (right-left)];

	// populate all elements between (left -> mid), (mid+1 -> right) with the smallest element
	for (i = left, j = mid + 1, k = 0; i <= mid && j <= right; k++)
	{
		buffer[k] = (haystack[i] < haystack[j]) ? haystack[i++] : haystack[j++];
	}

	// now we copy the leftover elements; not that only one of the two while loops below
	// will be processed per method invocation
	// by definition leftover elements are larger than the ones already processed so it's
	// safe to append them at the end

	// finish copying 'left' elements which were not processed
	while (i <= mid)
	{
		buffer[k++] = haystack[i++];
	}
	// finish copying 'right' elements which were not processed
	while (j <= right)
	{
		buffer[k++] = haystack[j++];
	}

	// copy buffer into the assigned area of the haystack
	for (i = 0; i < k; i++)
	{
		haystack[left + i] = buffer[i];
	}

	free(buffer);

	//for(i=left;i<=right;i++) 
	//{
	//   haystack[i]=buffer[i-left];
	//}
}

void sort_merge_helper_sort(int haystack[], int left, int right)
{
	// already processed?
	if (left >= right) {
		return;
	}

	int mid = (left + right) / 2;
	sort_merge_helper_sort(haystack, left, mid);
	sort_merge_helper_sort(haystack, mid + 1, right);
	sort_merge_helper_merge(haystack, left, mid, right);
}

void sort_merge(int haystack[], int size)
{
	sort_merge_helper_sort(haystack, 0, size - 1);
}

void write_matrix_to_file(int matrix[4][4], char* file_name)
{
	FILE* out = fopen(file_name, "w");
	if (!out)
	{
		printf("Unable to open file for writing\n");
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fprintf(out, "%d,", matrix[i][j]);
		}
	}
	fclose(out);
}

void read_matrix_from_file(int matrix[4][4], char* file_name)
{
	FILE* out = fopen(file_name, "r");
	if (!out)
	{
		printf("Unable to open file for reading\n");
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fscanf(out, "%d,", &matrix[i][j]);
		}
	}
}

void student_append(STUDENT student, char* file_name)
{
	FILE* out = fopen(file_name, "ab");
	if (!out)
	{
		printf("Unable to open file\n");
		return;
	}

	// move to end of file
	fwrite(&student, sizeof(STUDENT), 1, out);
	fclose(out);
}

float equation(float x)
{
	return x*x*x - x - 2;
}

float bisection(float a, float b, float(*fun)(float x))
{
	int max_iter = 10;
	float allowed_error = 0.01;
	float x, new_x, iter = 0;
	// initial guess
	x = (a + b) / 2;
	do {
		if (fun(a) * fun(x) < 0) {
			b = x;
		}
		else {
			a = x;
		}
		new_x = (a + b) / 2;
		iter++;
		if (fabs(new_x - x) < allowed_error) {
			break;
		}
		x = new_x;
		
	} while (iter < max_iter);

	return x;
}

int gcd(int a, int b) {
	if (a == 0)
	{
		return b;
	}

	return gcd(b %a, a);
}

void print_array(int values[], int size) {
	printf("[");
	for (int i = 0; i < size; i++)
	{
		printf("%d", values[i]);
		if (i != size - 1)
		{
			printf(",");
		}
	}
	printf("]\n");
}

void print_matrix(int matrix[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%5d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void student_print_all(char* file_name)
{
	FILE* db = fopen(file_name, "rb");
	if (!db)
	{
		printf("Unable to open file for reading\n");
		return;
	}
	
	// TODO - lists last record twice
	while (!feof(db))
	{
		STUDENT student;
		fread(&student, sizeof(STUDENT), 1, db);
		printf("Read STUDENT: %d, %d, %s\n", student.an_studiu, student.grupa, student.nume);
	}
}