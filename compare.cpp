#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>
#include <dirent.h>
#include "winnow.h"

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
	int total = i;
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
	total += i;
	cout<<"\nFile: "<<file1<<"\t Matching Percentage: "<<(float)(matched*100)/total;
}
int main()
{
	string filex="hash.txt",line;
	ifstream readFile;
	readFile.open(filex.c_str());
	int hashValue=0;
	while(getline(readFile, line))
	{
		initialiseMap(line, hashValue);
		hashValue++;
	}
	
	string newFile;
	cout<<"Enter the file to be compared: ";
	cin>>newFile;

	map <int, vector<int> > sig_of_new_file;
	sig_of_new_file = creatSignature(newFile);

	vector<string> file_list;
	createFileList(argv[1], file_list);			//Give Directory name as command line argument
	string s1 = ".", s2 = "..",s;
	std::vector<string>::iterator it;

	for(it = file_list.begin();it!=file_list.end();it++)
	{	s = *it;
		if((s.compare(s1) != 0) && (s.compare(s2) != 0))
		{	s = (string)argv[1]+"/"+s;
			cout<<s<<"\n";
			compare(s,newFile);
		}
	}

	return 0;
}
