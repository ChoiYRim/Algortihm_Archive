#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N,M,K;
vector<vector<int>> dp;

void print()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            printf("%5d ", dp[i][j]);
        printf("\n");
    }
}

void init()
{
    scanf("%d%d%d", &N, &M, &K);
    dp = vector<vector<int>>(N,vector<int>(M,0));
    for(int i = 0; i < N; i++)
        dp[i][0] = 1;
    for(int i = 0; i < M; i++)
        dp[0][i] = 1;
    for(int i = 1; i < N; i++)
    {
        for(int j = 1; j < M; j++)
            dp[i][j] = dp[i-1][j]+dp[i][j-1];
    }
}

int solve()
{
    int y = (K-1)/M;
    int x = (K-1)%M;
    
    if(K == 0)
    {
        y = 0;
        x = 0;
    }
    
    return dp[y][x]*dp[N-1-y][M-1-x];
}

int main(int argc,char* argv[])
{
    init();
    //print();
    printf("%d\n", solve());
    return 0;
}
