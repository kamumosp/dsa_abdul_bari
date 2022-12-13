#include <iostream>
#include <cstdint>

using namespace std;

//	int32_t p[] = {5, 6, 8, 10, 11, 15, 18};
void PrintMissingElements(int32_t *p, int32_t size)
{
	int32_t prev = p[0];
	
	cout << "Missing elements : ";
	for (int i = 1; i < size; i++)
	{
		if (p[i] != (prev + 1))
		{
			for (int j = prev+1; j < p[i]; j++)
				cout << j << ", ";
		}
		prev = p[i];
	}
}

// 	int32_t p[] = {25, 16, 16, 10, 10, 10, 1, 4, 15, 8, 8, 20, 20};
void DuplicateElements(int32_t *p, int32_t size, int32_t  max)
{
	int32_t h[max+1] = {0};
	
	for (int i = 0; i < size; i++)
	{
		h[p[i]]++;
	}
	
	cout << "Duplicate Elements : ";
	for (int i = 0; i < (max+1); i++)
	{
		if (h[i] > 1)
			cout << i << ", ";
	}
	cout << endl;
}

// 	int32_t p[] = {1, 2, 3, 4, 5, 6, 10, 20, 30, 7, 8, 9};
void TwoNumberSumK(int32_t *p, int32_t size, int32_t  max, int32_t  sum)
{
	int32_t h[max+1] = {0};
	
	cout << "Pair of Elements : " << endl;
	for (int i = 0; i < size; i++)
	{
		if ((sum - p[i]) >= 0)
		{
			if (h[sum - p[i]] > 0)
			{
				cout << "[" << p[i] << ", " << (sum - p[i]) << "]" << endl;
			}
		}
		h[p[i]]++;
	}
}

int32_t main()
{
	int32_t p[] = {1, 2, 3, 4, 5, 6, 10, 20, 30, 7, 8, 9};
	int32_t	size = sizeof(p)/sizeof(p[0]);
	
	cout << "Array Size : " << size << endl;
	
//	PrintMissingElements(p, size);
//	DuplicateElements(p, size, 25);
	TwoNumberSumK(p, size, 30, 10);
	return 0;
}
