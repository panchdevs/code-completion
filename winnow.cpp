#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>
#define d 256
#define q 101

using namespace std;

void find_min(int *min, int *min_pos, int hashes[],int i,int window)
{
    *min = 99999999;
    int j = i;
    while(j<(window + i))
    {
      if(*min>=hashes[j])
      { *min = hashes[j];
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
        //p = (p*d + pat[i])%q;
        t = (t*d + text[i])%q;
      }
      for(int i=0; i< tl-pl; i++)
      {
        if(i < tl - pl)
        {
           t = (d*(t - text[i]*h) + text[i+pl])%q;
           if(t < 0) t = t+q;
           hashes[i] = t;
          // cout<<hashes[i]<<" ";
        }
      }
     int min_pos = -1, j = 0, min;
     for(int i=0;i<(tl - pl);i++)
     {
        if(i == 0) 
        { find_min(&min, &min_pos, hashes, i, window);
        	//cout<<min<<"\n";
          sig[k].push_back(min);
        }
        else if(i < (min_pos + window) )
        {
           if(hashes[i] == min) min_pos = i;
           else if(hashes[i] < min)
           {
             min = hashes[i];
             min_pos = i;
             //cout<<min<<"\n";
             sig[k].push_back(min);
           }
        }
        else if(i >= (min_pos + window))
        {
          i -= (window - 1) ;
          find_min(&min, &min_pos, hashes, i, window);
          //cout<<min<<"\n";
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
    		{ cout<<sig[i][j]<<" "; count++; }
    	cout<<"\n";
    }
    cout<<"total hashes are "<<count<<"\n";
}

int main() {

	string text,pat ; int pl,window;
	cout<<"enter substring lenght "; cin>>pl;
	cout<<"enter window size "; cin>>window;
	for(int i=0;i<2;i++)
	{ cout<<"enter file 1 "; cin>>text;
	  match(text,pl,window);
	 }
	return 0;
}
