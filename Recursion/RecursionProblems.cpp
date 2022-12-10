#include <iostream>
#include <cstdint>

using namespace std;

void foo1 (int n, int sum)
{
int k = 0, j = 0;

if (n == 0) return;

k = n % 10;

j = n/10;

sum = sum + k;

foo1 (j, sum);

printf("%d", k);

}

int main1 ()

{

int a = 2048, sum = 0;

foo1 (a, sum);

printf("%d\n", sum);

	
	return 0;
}

int f (int &x, int c) 
{
	c = c - 1;

	if (c == 0) return 1; 

	x = x + 1; 

	cout << "x = " << x << endl;
	
	int val = f(x,c) * x;

	cout << "x = " << x << ", val = " << val << endl;

	return val;
}

int32_t main()
{
	int p = 5;
	cout << "value : " << f(p,p);
	return 0;
}
