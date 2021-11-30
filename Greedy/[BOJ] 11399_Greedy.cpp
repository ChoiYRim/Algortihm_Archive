#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N;
vector<pair<int,int>> v;

inline bool comp(pair<int,int>& p1,pair<int,int>& p2) { return (p1.second < p2.second); }

int main()
{
    int ans = 0,sum = 0;
    
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        v.push_back({i,tmp});
    }
    
    sort(v.begin(),v.end(),comp);
    for(int i = 0; i < N; i++)
    {
        sum += v[i].second;
        ans += sum;
    }
    
    cout << ans << '\n';
    return 0;
}
