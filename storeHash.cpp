#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>
#define d 256
#define q 101

using namespace std;
int overallTotal,matched,check[101];

void find_min(int *min, int *min_pos, int hashes[],int i,int window)
{
	*min = 99999999;
    int j = i;
    while(j<(window + i))
    {
		if(*min>=hashes[j])
		{
			*min = hashes[j];
        	*min_pos = j;
    	}
    	j++;
	}
}

void match(string filex, int pl, int window)
{
    int tl;
    ifstream fileOne;
    fileOne.open(filex.c_str() );
    string text;
    int k = 0;
    std::map <int, vector<int> > sig;
	while(getline(fileOne, text))
    {
    	tl = text.size();
		int h = 1;
		int p = 0;
		int t = 0;
		int hashes[tl-pl];
		for(int i=0; i<pl-1;i++)
		h = (h*d)%q;
		for(int i=0; i<=pl-1;i++)
		{
			t = (t*d + text[i])%q;
		}
		for(int i=0; i< tl-pl; i++)
		{
			if(i < tl - pl)
			{
				hashes[i] = t;
				t = (d*(t - text[i]*h) + text[i+pl])%q;
				if(t < 0) t = t+q;
	        }
		}
    	int min_pos = -1, j = 0, min;
    	for(int i=0;i<(tl - pl);i++)
    	{
    		if(i == 0) 
    		{
				find_min(&min, &min_pos, hashes, i, window);
		  		sig[k].push_back(min);
			}
			else if(i < (min_pos + window) )
			{
		   		if(hashes[i] == min) min_pos = i;
		   		else if(hashes[i] < min)
		   		{
					min = hashes[i];
					min_pos = i;
					sig[k].push_back(min);
				}
			}
			else if(i >= (min_pos + window))
			{
				i -= (window - 1) ;
				find_min(&min, &min_pos, hashes, i, window);
				sig[k].push_back(min);
			}
		}
		k++;
	}
	
	cout<<"\nsignature is \n";
	int count = 0;
	for(int i=0;i<k;i++)
	{
		cout<<"line no. "<<i<<"\nHashes ";
		for(int j = 0;j<sig[i].size();j++)
		{
			cout<<sig[i][j]<<" ";
			
			ifstream readFile;
			string fileName="Hash.txt", append=filex, line, st[101];
			readFile.open(fileName.c_str() );
			int lineNo=0;
			while(getline(readFile, line))
			{
				st[lineNo++]=line;
			}
			ofstream writeFile;
			append += ",";
			append += i+'0';
			st[sig[i][j]] += " ";
			st[sig[i][j]] += append;
			writeFile.open(fileName.c_str() );
			for(int k=0;k < lineNo;k++)
				writeFile << st[k] << "\n";
		}
    	cout<<"\n";
    }
}

void resetHashFile()
{
	ofstream fileOn;
    string filex="hash.txt";
    fileOn.open(filex.c_str() );
	for(int i=0;i<101;i++)
		fileOn << i<<"\n";
}

int main()
{

	string fileName="fileList.txt",pat,line;
	int pl,window;
	cout<<"Enter substring length "; cin>>pl;
	cout<<"Enter window size "; cin>>window;
	resetHashFile();
	ifstream readFile;
	readFile.open(fileName.c_str() );
	while(getline(readFile, line))
	{
		match(line,pl,window);
	}
	return 0;
}