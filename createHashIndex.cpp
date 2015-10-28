#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>
#include <dirent.h>
#include "winnow.h"

#define d 256
#define q 101
#define substring_length 3
#define window_length 4

using namespace std;

int overallTotal,matched,check[q];

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

void winnowing_rolling_hash(string text, map <int, vector<int> > &sig,int no_of_lines)
{
	int h = 1, p = 0, t = 0, k = no_of_lines;
	int tl = text.size(), pl = substring_length, window = window_length;
	int hashes[tl-pl];
	
	for(int i=0; i<pl-1;i++)
		h = (h*d)%q;

	for(int i=0; i<=pl-1;i++)
		t = (t*d + text[i])%q;

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

}
map <int, vector<int> > create_signature(string filex)
{
    int tl, pl = substring_length, window = window_length;
    int no_of_lines = 0;
    string text;
    std::map <int, vector<int> > sig;

    ifstream fileOne;
    fileOne.open(filex.c_str() );
    
	
	while(getline(fileOne, text))
    {
    	winnowing_rolling_hash(text, sig, no_of_lines);
    	no_of_lines++;
    }
		
	
	//cout<<"\nsignature is \n";
	int count = 0;
	for(int i = 0; i < no_of_lines; i++)
	{
		//cout<<"line no. "<<i<<"\nHashes ";
		for(int j = 0; j < sig[i].size(); j++)
		{
			//cout<<sig[i][j]<<" ";
			
			ifstream readFile;
			string fileName="hash.txt", append=filex, line, st[q];
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
    	//cout<<"\n";
    }

    return sig;
}

void resetHashFile()
{
	ofstream fileOn;
    string filex="hash.txt";
    fileOn.open(filex.c_str() );
	for(int i=0;i<q;i++)
		fileOn << i<<"\n";
}

void createFileList(char *directory, vector<string> &file_list)
{
    DIR *dir;
 	struct dirent *ent;
 	if ((dir = opendir (directory)) != NULL) 
 	{
  		while ((ent = readdir (dir)) != NULL) 
    	{
    		file_list.push_back(ent->d_name);
    		//printf ("%s\n", ent->d_name);
    	}
  		closedir (dir);
	} 
	else 
	{
  		perror ("");
  		//return EXIT_FAILURE;
	}
}

int main(int argc, char *argv[])
{

	/*string fileName="fileList.txt",pat,line;
	int pl,window;
	cout<<"Enter substring length "; cin>>pl;
	cout<<"Enter window size "; cin>>window;
	*/
	resetHashFile();
	map <int, vector<int> > signature;
	vector<string> file_list;
	createFileList(argv[1], file_list);			//Give Directory name as command line argument
	string s1 = ".", s2 = "..",s;
	std::vector<string>::iterator it;

	for(it = file_list.begin();it!=file_list.end();it++)
	{	s = *it;
		if((s.compare(s1) != 0) && (s.compare(s2) != 0))
		{	s = (string)argv[1]+"/"+s;
			cout<<s<<"\n";
			signature = create_signature(s);
		}
	}
	
	return 0;
}
