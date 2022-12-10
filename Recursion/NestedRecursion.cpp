#include <iostream>
#include <cstdint>

using namespace std;

int func(int n)
{
	if (n > 100)
		return (n-10);
	else
		return func(func(n + 11));
	
}

int32_t main ()
{
	cout << "Hello, World!!!" << endl;
	
	cout << "value = " << func(51);
	
	return 0;
}
