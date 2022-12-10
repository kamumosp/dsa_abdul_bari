#include <iostream>
#include <cstdint>

using namespace std;

void toh(int n, char a, char b, char c)
{
	if (n > 0)
	{
		toh (n-1, a, c, b);
		cout << "moved from " << a << " to " << c << endl;
		toh (n-1, b, a, c);
	}
}

int32_t main ()
{
	cout << "Tower of Hanoi" << endl;
		
	toh(4, 'a', 'b', 'c');
	
	return 0;
}
