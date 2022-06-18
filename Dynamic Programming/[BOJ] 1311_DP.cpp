#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 0x7fffffff;

int N, ans;
vector<vector<int>> table, dp;

void input()
{
    ans = INF;
    
    cin >> N;
    table = vector<vector<int>>(N+1, vector<int>(N));
    dp = vector<vector<int>>(N+1, vector<int>(1<<N, INF));
    dp[0] = vector<int>(1<<N, 0);
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> table[i][j];
        }
    }
}

int solve(int worker, int done)
{
    if(worker > N)
        return 0;
    if(dp[worker][done] != INF)
        return dp[worker][done];
    
    for(int job = 0; job < N; job++)
    {
        int cur = (1<<job);
        
        if(done & cur)
            continue;
        
        dp[worker][done] = min(dp[worker][done], table[worker][job]+solve(worker+1, done|cur));
    }
    
    return dp[worker][done];
}

int main(int argc, char* argv[])
{
    input();
    cout << solve(1, 0) << endl;
    return 0;
}
