#include<iostream>
#include<bits/stdc++.h>
using namespace std;
std::map<string, vector<pair<int, string> > > sig;
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
	int freq[101]={0};
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
	string filex="Hash.txt",line;
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
	string compareFile;
	cout<<"Enter the file to be compared: ";
	cin>>compareFile;
	while(getline(readFile2, line))
	{
		if(line!=compareFile)	compare(line,compareFile);
	}
	return 0;
}
