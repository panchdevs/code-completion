#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#define ll long long
using namespace std;

long long int read_int(){
	char r;
	bool start=false,neg=false;
	long long int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10;
		start=true;
		if(r=='-')neg=true;
		else ret+=r-'0';
	}
	if(!neg)
		return ret;
	else
		return -ret;
}

int check_negative(std::vector<int>& v)
{
    int f = 1;
    std::vector<int>::iterator it = v.begin();
    for(;it < v.end(); it++)
    {
        if(*it > 0) f=0;
    }
    return f;
}

int find_max(std::vector<int>& v)
{
    std::vector<int>::iterator it = v.begin();
    int m = v[0];
    for(;it < v.end(); it++) if(*it > m) m = *it;
    return m;
}

long long max_sum(std::vector<int>& v)
{
    std::vector<int>::iterator it = v.begin();
    long long int sum_now = *it; long long int sum_max = *it;

    if(!check_negative(v))
    { for(it++;it < v.end(); it++ )
      {
        sum_now += *it;
        if(sum_now > sum_max) sum_max = sum_now;
        if(sum_now < 0) sum_now = 0;
      }
      return sum_max;
    }
    else
    {
      return find_max(v);
    }
}
int main()
{
	int t;
	t = read_int();
	while(t--)
	{
		int n,p_sum = 0;
		n = read_int();
		std::map<long long,vector<int> > mp;
		std::vector<int> v;
		mp[0].push_back(-1);
		for(int i=0; i<n;i++)
        {
            int j;
            //cin >> j;
            j = read_int();
            v.push_back(j);
        }
        ll sk,cnt = 0;
        sk = max_sum(v);
        for(int i=0; i<n; i++)
        {
            p_sum += v[i];
            if(mp.find(p_sum - sk) != mp.end())
            {
                std::vector<int>::iterator it = mp[p_sum - sk].begin();
                for(;it < mp[p_sum - sk].end(); it++)
                    cnt++;
            }
            mp[p_sum].push_back(i);
        }
        cout<<sk<<" "<<cnt<<"\n";
	}
	return 0;

}
