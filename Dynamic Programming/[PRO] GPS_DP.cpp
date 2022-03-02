#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
const int INF = 987654321;

vector<vector<int>> edges;
vector<vector<int>> dp; // dp[a][b] = c -> a지점이 b가 됐을 때 c번 수정해야함.

void init(int n,const vector<vector<int>>& edge_list)
{
    edges = vector<vector<int>>(n+1,vector<int>(0));
    for(const auto& edge : edge_list)
    {
        int from = edge[0];
        int to = edge[1];
        
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
}

int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log)
{
    init(n,edge_list); // 초기화
    
    dp = vector<vector<int>>(k,vector<int>(n+1,INF));
    
    dp[0][gps_log[0]] = 0; // 시작 경로는 고정
    for(int i = 1; i < k; i++)
    {
        for(int v = 1; v <= n; v++)
        {
            if(dp[i-1][v] == INF) continue;
                        
            for(const auto& next : edges[v])
            {
                if(gps_log[i] != next)
                    dp[i][next] = min(dp[i][next],dp[i-1][v]+1);
                else
                    dp[i][next] = min(dp[i][next],dp[i-1][v]);
            }
        }
    }
    
    if(dp[k-1][gps_log[k-1]] >= INF)
        return -1;
    return dp[k-1][gps_log[k-1]];
}

int main()
{
    cout << solution(7, 10, {{1, 2},{1, 3},{2, 3},{2, 4},{3, 4},{3, 5},{4, 6},{5, 6},{5, 7},{6, 7}}, 6, {1,2,3,3,6,7}) << endl;
    return 0;
}
