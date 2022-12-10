#include <iostream>
#include <cstdint>

using namespace std;

void funcB(int n);
void funcA(int n)
{
	if (n > 0)
	{
		printf ("%d ", n);
		funcB(n-1);
	}
}
void funcB(int n)
{
	if (n > 1)
	{
		printf ("%d ", n);
		funcA(n/2);
	}
}

int32_t main ()
{
	cout << "Hello, World!!!" << endl;
	
	funcA(21);
	
	return 0;
}
