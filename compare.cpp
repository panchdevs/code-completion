#include<iostream>
#include<bits/stdc++.h>
#define q 1001
#define d 256
#define pl 4 //substring length 
#define window 4 //window size
using namespace std;
std::map<string, vector<pair<int, string> > > sig;

void resetHashFile()
{
	ofstream fileOn;
    string filex="HashTemp.txt";
    fileOn.open(filex.c_str() );
	for(int i=0;i<q;i++)
		fileOn << i<<"\n";
}


void find_min(int *min, int *min_pos, int hashes[],int i)
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

void match(string filex)
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
				find_min(&min, &min_pos, hashes, i);
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
				find_min(&min, &min_pos, hashes, i);
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
			string fileName="HashTemp.txt", append=filex, line, st[q];
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




void initialiseMap(string line, int hashValue)
{
	int i=0;
	while(i<line.length())
	{
		while(i<line.length() && line[i]!=' ') i++;
		int j=i;
		while(j<line.length() && line[j]!=',') j++;
		int k=j;
		while(k<line.length() && line[k]!=' ') k++;
		if(k>j && j>i)
		{
			sig[line.substr(i+1,j-i-1)].push_back(make_pair(hashValue,line.substr(j+1,k-j-1)));
		}
		i=j+1;
	}
}
void compare(string file1, string file2)
{
	int freq[q]={0};
	int i=0;
	while(i<sig[file1].size())
	{
		freq[sig[file1][i].first]++;
		i++;
	}
	int matched=0;
	i=0;
	while(i<sig[file2].size())
	{
		if(freq[sig[file2][i].first])
		{
			matched += 2;
			freq[sig[file2][i].first]--;
		}
		i++;
	}
	cout<<"File 1: "<<file1<<"\t File 2: "<<file2<<"\t Number of finger prints matched: "<<matched<<endl;
}
int main()
{
	resetHashFile();
	ifstream rf;
	string readfile="Hash.txt", writefile="HashTemp.txt", line;
	ofstream wf;
	rf.open(readfile.c_str() );
	wf.open(writefile.c_str() );
	while(getline(rf, line))
	{
		wf<<line<<"\n";
	}
	string compareFile;
	cout<<"Enter the file to be compared: ";
	cin>>compareFile;
	match(compareFile);
	string filex="HashTemp.txt";
	ifstream readFile;
	readFile.open(filex.c_str());
	int hashValue=0;
	while(getline(readFile, line))
	{
		initialiseMap(line, hashValue);
		hashValue++;
	}
	
	filex="fileList.txt";
	ifstream readFile2;
	readFile2.open(filex.c_str());
	while(getline(readFile2, line))
	{
		if(line!=compareFile)	compare(line,compareFile);
	}
	return 0;
}
