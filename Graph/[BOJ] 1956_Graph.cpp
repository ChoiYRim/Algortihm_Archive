#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

int V,E;
vector<vector<int>> edges;
vector<vector<int>> dp;

void input()
{
    scanf("%d%d", &V, &E);
    dp = vector<vector<int>>(V+1,vector<int>(V+1,INF));
    for(int i = 0; i < E; i++)
    {
        int from,to,cost;
        scanf("%d%d%d", &from, &to, &cost);
        dp[from][to] = cost;
    }
}

int solve()
{
    for(int mid = 1; mid <= V; mid++)
    {
        for(int from = 1; from <= V; from++)
        {
            for(int to = 1; to <= V; to++)
            {
                if(dp[from][mid] == INF || dp[mid][to] == INF)
                    continue;
                dp[from][to] = min(dp[from][to],dp[from][mid]+dp[mid][to]);
            }
        }
    }
    
    bool is_exist = false;
    int result = INF;
    
    for(int from = 1; from <= V; from++)
    {
        for(int to = 1; to <= V; to++)
        {
            if(from != to)
            {
                if(dp[from][to] != INF && dp[to][from] != INF)
                {
                    is_exist = true;
                    result = min(result,dp[from][to]+dp[to][from]);
                }
            }
        }
    }
    
    if(is_exist)
        return result;
    return -1;
}

int main(int argc,char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
