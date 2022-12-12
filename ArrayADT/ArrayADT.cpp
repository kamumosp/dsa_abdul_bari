#include <iostream>
#include <cstdint>

using namespace std;

void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

class Array
{
	int32_t *A;
	
	int32_t size;
	int32_t length;
	
public:
	Array(): A(NULL), size(0), length(0) {};
	
	Array(int sz): A(NULL), size(sz), length(0) 
	{
		A = new int32_t[sz];
	}
	
	Array(int *arr, int sz, int len) 
	{
		A = new int32_t[sz];
		size = sz;
		
		for (int i = 0; i < len; i++)
			A[i] = arr[i];
		
		length = len;
	};
	
	~Array()
	{
		if (A)
			delete []A;
	}
	
	void Display(string str)
	{
		cout << str;
		for (int i = 0; i < length; i++)
			cout << A[i] << " ";
		
		cout << endl;
	}

	void Append(int x)
	{
		if (length < size)
			A[length++] = x;
	}

	void Insert(int index, int x)
	{
		int i;
		if (index >= 0 && index <= length)
		{
			for (i = length; i > index; i--)
				A[i] = A[i-1];
			
			A[index] = x;
			length++;
		}
	}

	int Delete(int index)
	{
		if (index >= 0 && index < length)
		{
			int x = A[index];
			for (int i = index; i < length-1; i++)
				A[i] = A[i+1];
			
			length--;
			return x;
		}

		return 0;
	}

	int LinearSearch(int key)
	{
		for (int i = 0; i < length; i++)
		{
			if (key == A[i])
			{
				Swap (&A[i], &A[0]);
				return i;
			}
		}
		return -1;
	}

	int BinarySearch(int key)
	{
		int l = 0, mid = 0, h = 0;
		
		l = 0;
		h = length - 1;

		while (l <= h)
		{
			mid = (l + h) / 2;
			if (key == A[mid])
				return mid;
			else if (key < A[mid])
				h = mid - 1;
			else
				l = mid + 1;
		}
		return -1;
	}	
	
	/*
	int RBinSearch(int l,int h,int key)
	{
		int mid = 0;

		if (l <= h)
		{
			mid = (l + h) / 2;
			if (key == A[mid])
				return mid;
			else if(key < A[mid])
				return RBinSearch(l, mid-1, key);
			else
				return RBinSearch(mid+1, h, key);
		}
		return -1;
	}
	*/
	
	int Get(int index)
	{
		if (index >= 0 && index < length)
			return A[index];
		return -1;
	}
	
	void Set(int index, int x)
	{
		if (index >= 0 && index < length)
			 A[index] = x;
	}

	int Max()
	{
		int max = A[0];

		for (int i = 1; i < length; i++)
		{
			if (A[i] > max)
				max = A[i];
		}
		return max;
	}

	int Min()
	{
		int min = A[0];

		for (int i = 1; i < length; i++)
		{
			if (A[i] < min)
				min = A[i];
		}
		return min;
	}

	int Sum()
	{
		int s=0;

		for (int i = 0; i < length; i++)
			s += A[i];

		return s;
	}

	float Avg()
	{
		return (float)Sum() / length;
	}

	void Reverse()
	{
		for (int i = 0, j = length - 1; i < j; i++, j--)
		{
			Swap(&A[i],&A[j]);
		}
	}

	void InsertSort(int x)
	{
		if (length < size)
		{
			int i = length - 1;
			while((i >= 0) && (A[i] > x))
			{
				A[i + 1] = A[i];
				i--;
			}
			
			A[i + 1] = x;
			length++;			
		}
	}
	
	bool isSorted()
	{
		for (int i = 0; i < (length - 1); i++)
		{
			if (A[i] > A[i+1])
				return false;
		}
		return true;
	}
	
	void ReArrangeNegPos()
	{
		int i = 0, j = length - 1; 
		while (i < j)
		{
			while ((i < j) && (A[i] < 0)) i++;
			while ((j > i) && (A[j] >= 0)) j--;

			if (i < j)
				Swap(&A[i], &A[j]);
		}
	}
	
	void Merge(Array *arr1, Array *arr2)
	{
		if (A) delete []A;
		
		A = new int32_t[arr1->size + arr2->size];
		size = arr1->size + arr2->size;
		
		int32_t i = 0, j = 0, k = 0;
		
		while ((i < arr1->length) && (j < arr2->length))
		{
			if (arr1->A[i] < arr2->A[j])
				A[k++] = arr1->A[i++];
			else
				A[k++] = arr2->A[j++];
		}
		
		while (i < arr1->length)
			A[k++] = arr1->A[i++];
		
		while (j < arr2->length)
			A[k++] = arr2->A[j++];

		length = arr1->length + arr2->length;
	}

	void Union(Array *arr1, Array *arr2)
	{
		if (A) delete []A;
		
		A = new int32_t[arr1->size + arr2->size];
		size = arr1->size + arr2->size;
		
		int32_t i = 0, j = 0, k = 0;
		
		while ((i < arr1->length) && (j < arr2->length))
		{
			if (arr1->A[i] < arr2->A[j])
				A[k++] = arr1->A[i++];
			else if (arr1->A[i] > arr2->A[j])
				A[k++] = arr2->A[j++];
			else
			{
				A[k++] = arr1->A[i++];
				j++;
			}
		}
		
		while (i < arr1->length)
			A[k++] = arr1->A[i++];
		
		while (j < arr2->length)
			A[k++] = arr2->A[j++];

		length = k;
	}
	
	void Intersection(Array *arr1, Array *arr2)
	{
		if (A) delete []A;
		
		A = new int32_t[arr1->size + arr2->size];
		size = arr1->size + arr2->size;
		
		int32_t i = 0, j = 0, k = 0;
		
		while ((i < arr1->length) && (j < arr2->length))
		{
			if (arr1->A[i] < arr2->A[j])
				i++;
			else if (arr1->A[i] > arr2->A[j])
				j++;
			else
			{
				A[k++] = arr1->A[i++];
				j++;
			}
		}
		
		length = k;
	}

	void Diff(Array *arr1, Array *arr2)
	{
		if (A) delete []A;
		
		A = new int32_t[arr1->size + arr2->size];
		size = arr1->size + arr2->size;
		
		int32_t i = 0, j = 0, k = 0;
		
		while ((i < arr1->length) && (j < arr2->length))
		{
			if (arr1->A[i] < arr2->A[j])
				A[k++] = arr1->A[i++];
			else if (arr1->A[i] > arr2->A[j])
				j++;
			else
			{
				i++;
				j++;
			}
		}
		
		while (i < arr1->length)
			A[k++] = arr1->A[i++];

		length = k;
	}
};


int32_t main()
{
	int32_t p[] = {5, 10, 25, 30, 45};
	int32_t q[] = {10, 20, 30, 40, 50};
	
	Array *arr1 = new Array(p, 10, 5);
	Array *arr2 = new Array(q, 10, 5);
	
	Array *arr3 = new Array();
	Array *arr4 = new Array();
	Array *arr5 = new Array();
	
	arr3->Union(arr1, arr2);
	arr4->Intersection(arr1, arr2);
	arr5->Diff(arr1, arr2);
	
	arr1->Display("Array 1 : ");
	arr2->Display("Array 2 : ");
	arr3->Display("Union Array : ");
	arr4->Display("Intersection Array : ");
	arr5->Display("Diff Array : ");
	
	delete arr1, arr2, arr3, arr4;
	
//	Array *array = new Array(p, 10, 5);
	
//	array->Display("Input : ");
	
//	cout << "Array is Sorted? : " << (array->isSorted() ? "true" : "false") << endl;
	
//	array->InsertSort(2);

//	array->ReArrangeNegPos();
	
//	array->Display("Output : ");
	
//	delete array;
	
	return 0;
}
