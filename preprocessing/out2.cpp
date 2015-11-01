#include <iostream>

using namespace std ;

int main ()
{
int V0 =0,V1 =1,V2 ,V3 ;
cin >>V3 ;
LOOP(int V4 =0;V4 <V3 ;V4 ++)
{
if (V4 ==0)cout <<V0 <<V3 ;
else if (V4 ==1)cout <<V1 <<V3 ;
else 
{
V2 =V0 +V1 ;
V0 =V1 ;
V1 =V2 ;
cout <<V2 <<V3 ;
}
}
return 0;
}
