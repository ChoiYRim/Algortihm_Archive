#include <deque>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N, L;
vector<ll> v;

void input()
{
    scanf("%d%d", &N, &L);
    v = vector<ll>(N+1);
    for(int i = 1; i <= N; i++) scanf("%lld", &v[i]);
    
}

void solve()
{
    deque<pair<int, ll>> dq;
    
    for(int i = 1; i <= N; i++)
    {
        if(!dq.empty())
        {
            if(dq.front().first < i-L+1) dq.pop_front();
        }
        while(!dq.empty() && dq.back().second > v[i]) dq.pop_back();
        dq.push_back({i, v[i]});
        
        printf("%lld ", dq.front().second);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    input();
    solve();
    return 0;
}
