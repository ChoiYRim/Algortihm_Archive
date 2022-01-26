#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

int N,K;
vector<int> dp;
vector<pair<int,int>> bags;

inline bool comp(const pair<int,int>& p1,const pair<int,int>& p2) { return p1.first < p2.first; }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> K;
    dp = vector<int>(K+1,0);
    for(int i = 0; i < N; i++)
    {
        int w,v; cin >> w >> v;
        bags.push_back({w,v});
    }
    sort(bags.begin(),bags.end(),comp);
}

int solve()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = K; j >= bags[i].first; j--)
        {
            dp[j] = max(dp[j],dp[j-bags[i].first]+bags[i].second);
        }
    }
    
    return dp[K];
}

int main()
{
    input();
    
    cout << solve() << endl;
    return 0;
}

