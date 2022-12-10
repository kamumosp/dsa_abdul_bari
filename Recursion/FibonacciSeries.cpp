#include <iostream>
#include <cstdint>

using namespace std;

int fibonacci_loop(int n)
{
	if (n <= 1)
		return n;
	
	int t0 = 0, t1 = 1;
	for (int i = 2; i <= n; i++)
	{
		t1 = t1 + t0;
		t0 = t1 - t0;
	}
	return t1;
}

void fibonacci_series_loop(int arr[], int n)
{
	if (n >= 0)
		arr[0] = 0;
	if (n >= 1)
		arr[1] = 1;
	
	int t0 = 0, t1 = 1, fib = 0;
	for (int i = 2; i <= n; i++)
	{
		t1 = t1 + t0;
		t0 = t1 - t0;
		arr[i] = t1;
	}
}

int fibonacci_rec(int n)
{
	if (n <= 1)
		return n;
	
	return fibonacci_rec(n-2) + fibonacci_rec(n-1);
}

#define MAX_NUM	32
int feb_series[MAX_NUM] = {0};
int fibonacci_rec_fast(int n)
{
	if (n <= 1)
	{
		feb_series[n] = n;
		return n;
	}
	
	if (feb_series[n-2] == -1)
		feb_series[n-2] = fibonacci_rec_fast(n-2);
	
	if (feb_series[n-1] == -1)
		feb_series[n-1] = fibonacci_rec_fast(n-1);
	
	feb_series[n] = feb_series[n-2] + feb_series[n-1];
	return feb_series[n];
}

int32_t main ()
{
	cout << "fibonacci_loop" << endl;
	
	for (int i = 0; i < 16; i++)
	{
		cout << fibonacci_loop(i) << " ";
	}
	
	cout << "\nfibonacci_series_loop" << endl;
	int arr[16] = {0};
	
	fibonacci_series_loop(arr, 15);

	for (int i = 0; i < 16; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\nfibonacci_rec" << endl;
	
	for (int i = 0; i < 16; i++)
	{
		cout << fibonacci_rec(i) << " ";
	}
	
	cout << "\nfibonacci_rec_fast" << endl;
	for (int i = 0; i < MAX_NUM; i++)
		feb_series[i] = -1;
	
	for (int i = 0; i < 16; i++)
	{
		cout << fibonacci_rec_fast(i) << " ";
	}
	
	cout << endl;
	return 0;
}
