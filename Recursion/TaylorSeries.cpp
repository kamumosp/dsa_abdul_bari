#include <iostream>
#include <cstdint>

using namespace std;

double taylor(int x, int n)
{
	static double curr = 1;
	if (n > 1) {
		double prev = taylor(x, n-1);
//		cout << "curr bef : " << curr << ", x = " << x << ", n = " << n << endl;
		curr = (curr * x)/(n-1);
//		cout << "curr aft : " << curr << endl;
		return prev + curr;
	}

	return 1;
}

double taylor_loop(int x, int n)
{
	double retvalue = 1;
	double term = 1;
	int i = 1;
	while (i < n) {
		term = (term * x/i);
		retvalue += term;
		i++;
	}

	return retvalue;
}

double taylor_horner_loop(int x, int n)
{
	double retvalue = 1;
	int i = n-1;
	while (i > 0) {
		retvalue = 1 + (x*retvalue/i);
		i--;
	}

	return retvalue;
}
double taylor_horner(int x, int n)
{
	static double retvalue = 1;
	if (n <= 1)
		return retvalue;
	
	retvalue = 1 + (x*retvalue/(n-1));
	
	return taylor_horner(x, n-1);
}

int32_t main ()
{
	cout << "Hello, World!!!" << endl;
	double taylorout = taylor(4,20);
	cout << "taylor = " << taylorout << endl;
	cout << "taylor_loop = " << taylor_loop(4,20) << endl;
	cout << "taylor_horner = " << taylor_horner(4,20) << endl;
	cout << "taylor_horner_loop = " << taylor_horner_loop(4,20) << endl;
	return 0;
}
