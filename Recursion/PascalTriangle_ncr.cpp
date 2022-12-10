#include <iostream>
#include <cstdint>

using namespace std;

int ncr(int n, int r)
{
	if (r == 0 || n == r)
		return 1;
	
	return ncr(n-1, r-1) + ncr(n-1, r);
}

int32_t main ()
{
	cout << "Pascal's Triangle" << endl;
	
	for (int i = 0; i < 10; i++)
	{
		cout << "n = " << i << "\t";
		for (int j = 0; j <= i; j++)
		{
			cout << " " << ncr(i, j);
		}
		cout << endl;
	}
	return 0;
}
