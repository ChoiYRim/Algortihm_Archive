#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<vector<int>> triangle, dp;

void input()
{
    int cnt = 0;
    
    cin >> N;
    dp = vector<vector<int>>(N+1);
    triangle = vector<vector<int>>(N+1);
    for(int i = 1; i <= N; i++)
    {
        cnt++;
        dp[i] = vector<int>(cnt, 0);
        triangle[i] = vector<int>(cnt, 0);
        
        for(int j = 0; j < cnt; j++)
            cin >> triangle[i][j];
    }
}

int solve()
{
    int cnt = 0;
    
    dp[1][0] = triangle[1][0];
    for(int depth = 2; depth <= N; depth++)
    {
        cnt++;
        
        for(int idx = 0; idx <= cnt; idx++)
        {
            if(idx > 0 && idx <= cnt-1)
            {
                dp[depth][idx] = max(dp[depth][idx], dp[depth-1][idx-1]+triangle[depth][idx]);
                dp[depth][idx] = max(dp[depth][idx], dp[depth-1][idx]+triangle[depth][idx]);
            }
            else if(idx == 0)
            {
                dp[depth][idx] = max(dp[depth][idx], dp[depth-1][idx]+triangle[depth][idx]);
            }
            else
            {
                dp[depth][idx] = max(dp[depth][idx], dp[depth-1][idx-1]+triangle[depth][idx]);
            }
        }
    }
    
    return *max_element(dp[N].begin(), dp[N].end());
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
