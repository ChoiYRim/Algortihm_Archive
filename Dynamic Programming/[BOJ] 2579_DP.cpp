#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<int> steps;
vector<vector<int>>dp;

int main(int argc,char* argv[])
{
    cin >> N;
    dp = vector<vector<int>>(2,vector<int>(N+1,0));
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        steps.push_back(tmp);
    }
    
    dp[0][1] = steps[0];
    dp[0][2] = steps[1]+dp[0][1]; dp[1][2] = steps[1];
    for(int i = 3; i <= N; i++)
    {
        // 0 : -1 이전에 계단 밟음
        dp[0][i] = dp[1][i-1]+steps[i-1];
        
        // 1 : -2 이전에 계단 밟음
        dp[1][i] = max(dp[0][i-2],dp[1][i-2])+steps[i-1];
    }
    
    cout << max(dp[0][N],dp[1][N]) << endl;
    return 0;
}
