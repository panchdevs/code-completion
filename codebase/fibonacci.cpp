#include <iostream>

using namespace std ;

int main ()
{
	int a = 0 , b = 1 , c , n ;
	cin >> n ;
	for ( int var = 0 ; var < n ; var ++ )
	{
		if ( var == 0 ) cout << a << "\n" ;
		else if ( var == 1 ) cout << b << "\n" ;
		else
		{
			c = a + b ;
			a = b ;
			b = c ;
			cout << c << "\n" ;
		}
	}
	return 0;
}
