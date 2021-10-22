#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

int N;
vector<pair<ll,pair<ll,ll>>> v;

bool comp(pair<ll,pair<ll,ll>>& p1,pair<ll,pair<ll,ll>>& p2)
{
    if(p1.first == p2.first)
        return p1.second.first < p2.second.first;
    return p1.first > p2.first;
}

int main(int argc, const char * argv[])
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        ll tmp,two_cnt = 0,three_cnt = 0,num;
        
        cin >> num;
        
        tmp = num;
        while(tmp % 2 == 0)
        {
            tmp /= 2;
            two_cnt++;
        }
        
        tmp = num;
        while(tmp % 3 == 0)
        {
            tmp /= 3;
            three_cnt++;
        }
        
        v.push_back({three_cnt,{two_cnt,num}});
    }
    
    sort(v.begin(),v.end(),comp);
    
    for(int i = 0; i < (int)v.size(); i++)
        cout << v[i].second.second << " ";
    cout << '\n';
    return 0;
}
