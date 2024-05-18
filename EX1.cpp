/*
		Stav Macri 324084722 - סתיו מכרי
		Nadav Swartz 208296400 - נדב שוורץ
*/


#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void merge(int array[], int const left, int const mid, int const right)
{
	int const sub_One = mid - left + 1;
	int const sub_Two = right - mid;

	int* l_Array = new int[sub_One];
	int* r_Array = new int[sub_Two];


	for (int i = 0; i < sub_One; i++)
	{
		l_Array[i] = array[left + i];
	}
	for (int j = 0; j < sub_Two; j++)
	{
		r_Array[j] = array[mid + 1 + j];
	}

	int index_sub_One = 0;
	int index_sub_Two = 0;
	int index_Merged = left;

	while (index_sub_One < sub_One && index_sub_Two < sub_Two)
	{
		if (l_Array[index_sub_One] <= r_Array[index_sub_Two])
		{
			array[index_Merged] = l_Array[index_sub_One];
			index_sub_One++;
		}
		else
		{
			array[index_Merged] = r_Array[index_sub_Two];
			index_sub_Two++;
		}
		index_Merged++;
	}

	while (index_sub_One < sub_One)
	{
		array[index_Merged] = l_Array[index_sub_One];
		index_sub_One++;
		index_Merged++;
	}

	while (index_sub_Two < sub_Two)
	{
		array[index_Merged] = r_Array[index_sub_Two];
		index_sub_Two++;
		index_Merged++;
	}
	delete[] l_Array;
	delete[] r_Array;
}

void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}


int binarySearch(int arr[], int size, int target, long& count2)
{
	int left = 0;
	int right = size - 1;
	int mid;

	if (target < arr[left] || target > arr[right])
	{
		return 0;
	}

	while (left <= right)
	{
		count2++;
		mid = left + (right - left) / 2;
		if (arr[mid] == target)
		{
			return 1;
		}
		else if (arr[mid] < target)
		{
			left = mid + 1;
		}
		else
			right = mid - 1;
	}
	return 0;
}


int findSum1(int V[], int W[], int n, int s)
{

	int i, j, k;
	long count1 = 0;

	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			for (k = 0; k < n * n; k++)
			{
				count1++;
				if (V[i] + V[j] + W[k] == s)
				{
					return count1;
				}
			}
		}
	}
	return count1;


}


int findSum2(int V[], int W[], int n, int s)
{

	int i, j;
	int target;
	long count2 = 0;

	mergeSort(W, 0, n * n - 1);

	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			target = s - V[i] - V[j];
			if (binarySearch(W, n * n, target, count2))
			{
				return count2;
			}
		}
	}
	return count2;
}




int findSum3(int V[], int W[], int n, int s)
{
	int i;
	long count3 = 0;
	int sum;
	int left = 0;
	int right = n * n - 1;

	mergeSort(W, 0, n * n - 1);

	for (i = 0; i < n; i++)
	{
		while (left < right)
		{
			count3++;
			sum = W[left] + W[right];
			if (sum == s - V[i])
			{
				return count3;
			}
			else if (sum < s - V[i])
			{
				left++;
			}
			else
			{
				right--;
			}
		}
	}
	return count3;
}



int main()
{
	int x = 500; // הבדיקה נעשתה על 5 מערכים
	int i, j;
	int s, n;
	int* V;
	int* W;


	long Sum1_Counters = 0;
	long Sum2_Counters = 0;
	long Sum3_Counters = 0;

	srand(time(0)); // for random number generation

	for (int i = 0; i < x; i++)
	{
		n = rand() % 101 + 200;
		V = new int[n];
		W = new int[n * n];

		for (j = 0; j < n; j++)
		{
			V[j] = rand() % 20001 - 10000;
		}
		for (j = 0; j < n * n; j++)
		{
			W[j] = rand() % 20001 - 10000;
		}

		s = rand() % 60001 - 30000;
	

		Sum1_Counters += findSum1(V, W, n, s);
		Sum2_Counters += findSum2(V, W, n, s);
		Sum3_Counters += findSum3(V, W, n, s);
	}

	cout << " The output is made on 5 pairs of arrays " << endl;
	cout << " 200 <= n <= 300: " << endl;
	cout << " findSum1: " << Sum1_Counters << endl;
	cout << " findSum2: " << Sum2_Counters << endl;
	cout << " findSum3: " << Sum3_Counters << endl;
}
