#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 1000*1000+1;

int N;
vector<vector<int>> costs;
vector<vector<int>> dp;

void input()
{
    cin >> N;
    dp = vector<vector<int>>(N+1,vector<int>(3,0));
    for(int i = 0; i < N; i++)
    {
        vector<int> cost;
        for(int j = 0; j < 3; j++)
        {
            int house; cin >> house;
            cost.push_back(house);
        }
        costs.push_back(cost);
    }
}

int solve()
{
    int result = INF;
    
    for(int color = 0; color < 3; color++)
    {
        for(int i = 0; i < 3; i++)
        {
            if(i != color)
            {
                dp[0][i] = INF;
                continue;
            }
            
            dp[0][i] = costs[0][i];
        }
        
        for(int i = 1; i < N; i++)
        {
            dp[i][0] = min(dp[i-1][1],dp[i-1][2])+costs[i][0];
            dp[i][1] = min(dp[i-1][0],dp[i-1][2])+costs[i][1];
            dp[i][2] = min(dp[i-1][0],dp[i-1][1])+costs[i][2];
        }
        
        for(int i = 0; i < 3; i++)
        {
            if(i == color) continue; // 끝 집 색이 첫 집 색과 동일
            
            result = min(result,dp[N-1][i]);
        }
    }
    
    return result;
}

int main(int argc,char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
