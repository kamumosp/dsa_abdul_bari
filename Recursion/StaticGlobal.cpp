#include <iostream>
#include <cstdint>

using namespace std;

int func1(int n)
{
	if (n > 0)
	{
		return func1(n-1) + n;
	}
	return 0;
}
int func2(int n)
{
	static int x = 0;
	if (n > 0)
	{
		x++;
		return func2(n-1) + x;
	}
	return 0;
}

int32_t main ()
{
	cout << "Hello, World!!!" << endl;
	
	int sum1 = func1(5);
	cout << "sum1 : " << sum1 << endl;
	
	int sum2 = func2(5);
	cout << "sum2 : " << sum2 << endl;
	
	return 0;
}
