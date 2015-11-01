#include <iostream>

using namespace std ;
int V0 (int V1 )
{
int V2 =0,V3 =1,V4 ;
if (V1 ==1)return 0;
else if (V1 ==2)return 1;
else 
{
LOOP(int V5 =3;V5 <=V1 ;V5 ++)
{
V4 =V2 +V3 ;
V2 =V3 ;
V3 =V4 ;
}

}
return V4 ;
}
int main ()
{
int V1 ;
cin >>V1 ;
LOOP(int V6 =1;V6 <=V1 ;V6 ++)
cout <<V0 (V6 )<<V1 ;
return 0;
}
