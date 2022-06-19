#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 0x7fffffff;

int T, N, K, W;
vector<int> buildings, dp;
vector<vector<int>> before;

void input()
{
    cin >> N >> K;
    dp = vector<int>(N+1, INF);
    buildings = vector<int>(N+1, 0);
    before = vector<vector<int>>(N+1); // before[i] : i를 짓기 위해 선행해서 지어야할 건물 리스트
    for(int i = 1; i <= N; i++) cin >> buildings[i];
    for(int i = 0; i < K; i++)
    {
        int from, to;
        cin >> from >> to;
        before[to].push_back(from);
    }
    cin >> W;
}

int solve(int cur)
{
    if(dp[cur] != INF)
        return dp[cur];
    
    int total = 0;
    
    dp[cur] = buildings[cur];
    for(const int& building : before[cur])
    {
        total = max(total, solve(building));
    }
    dp[cur] += total;
    
    return dp[cur];
}

int main(int argc, char* argv[])
{
    cin >> T;
    while(T--)
    {
        buildings.clear();
        before.clear();
        
        input();
        cout << solve(W) << endl;
    }
    
    return 0;
}
