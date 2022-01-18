#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct App
{
    int byte;
    int cost;
};

int N,M;
vector<App> app;

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    app = vector<App>(N);
    for(int i = 0; i < N; i++)
    {
        int byte; cin >> byte;
        app[i].byte = byte;
    }
    for(int i = 0; i < N; i++)
    {
        int cost; cin >> cost;
        app[i].cost = cost;
    }
}

int solve()
{
    int dp[10001] = {0,}; // dp[i] : 내가 고른 app들의 cost 합이 i일 때 byte값
    
    for(int i = 0; i < N; i++)
    {
        int cost = app[i].cost;
        for(int j = 10000; j >= cost; j--) // dp[i] = dp[i-app[j].cost]+app[j].byte
        {
            if(dp[j-cost] < 0)
                continue;
            dp[j] = max(dp[j],dp[j-cost]+app[i].byte);
        }
    }
    
    for(int i = 0; i < 10001; i++)
    {
        if(dp[i] >= M)
            return i;
    }
    
    return -1;
}

int main()
{
    input();
    
    cout << solve() << std::endl;
    return 0;
}
