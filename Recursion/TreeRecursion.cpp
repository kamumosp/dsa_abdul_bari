#include <iostream>
#include <cstdint>

using namespace std;

void func(int n)
{
	if (n > 0)
	{
		printf ("%d ", n);
		func(n-1);
		func(n-1);
	}
}

int32_t main ()
{
	cout << "Hello, World!!!" << endl;
	
	func(4);
	
	return 0;
}
