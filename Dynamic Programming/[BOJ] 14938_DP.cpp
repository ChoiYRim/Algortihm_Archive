#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, M, R;
vector<int> items;
vector<vector<int>> dp;
//vector<vector<pair<int, int>>> roads;

void input()
{
    cin >> N >> M >> R;
    items = vector<int>(N);
//    roads = vector<vector<pair<int, int>>>(N);
    dp = vector<vector<int>>(N, vector<int>(N, 0x1fffffff));
    
    for(int i = 0; i < N; i++) cin >> items[i];
    for(int i = 0; i < R; i++)
    {
        int from, to, len; cin >> from >> to >> len;
        dp[from-1][to-1] = dp[to-1][from-1] = len;
//        roads[from-1].push_back({to-1, item});
//        roads[to-1].push_back({from-1, item});
    }
}

int solve()
{
    int result = 0;
    
    for(int mid = 0; mid < N; mid++)
    {
        for(int from = 0; from < N; from++)
        {
            for(int to = 0; to < N; to++)
            {
                if(dp[from][to] > dp[from][mid]+dp[mid][to])
                    dp[from][to] = dp[from][mid]+dp[mid][to];
            }
        }
    }
    
    for(int i = 0; i < N; i++)
    {
        int item = items[i];
        
        for(int j = 0; j < N; j++)
        {
            if(i == j) continue;
            
            if(dp[i][j] <= M)
                item += items[j];
        }
        
        result = max(result, item);
    }
    
    return result;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
