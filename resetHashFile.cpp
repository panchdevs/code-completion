#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>
using namespace std;
string st[100];
int lineNo,i;
int main()
{
    ofstream fileOn;
    string filex="hash.txt";
    fileOn.open(filex.c_str() );
	for(i=0;i<101;i++)
		fileOn << i<<"\n";
    return 0;
}
