#include <iostream>

using namespace std ;
int fibonacci(int n)
{
	int a = 0 , b = 1 , c ;
	if(n == 1) return 0;
	else if (n == 2) return 1;
	else
	{
		for ( int i = 3 ; i <= n ; i ++ )
		{
			c = a + b ;
			a = b ;
			b = c ;
		}
		
	}
	return c;
}
int main ()
{
	int n ;
	cin >> n ;
	for ( int var = 1 ; var <= n ; var ++ )
		cout<<fibonacci(var)<<"\n";
	return 0;
}
