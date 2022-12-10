#include <iostream>
#include <cstdint>

using namespace std;

int sum(int n)
{
	if (n > 0)
		return sum(n-1) + n;

	return 0;
}

int fact(int n)
{
	if (n > 1)
		return fact(n-1) * n;

	return 1;
}

int expo(int a, int b)
{
	if (b > 1)
		return expo(a,b-1) * a;

	return a;
}

int power(int a, int b)
{
	if (b <= 1)
		return a;

	if (b & 1)
		return a * power(a*a, b/2);

	return expo(a*a,b/2);
}

int32_t main ()
{
	cout << "Hello, World!!!" << endl;
	
	cout << "sum = " << sum(1) << endl;
	cout << "fact = " << fact(1) << endl;
	cout << "expo = " << expo(2,16) << endl;
	return 0;
}
