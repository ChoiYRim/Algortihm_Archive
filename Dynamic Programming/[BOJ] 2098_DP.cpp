#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

int N;
vector<vector<int>> v;
vector<vector<int>> dp;

void input()
{
    scanf("%d", &N);
    v = vector<vector<int>>(N+1,vector<int>(N+1,0));
    dp = vector<vector<int>>(N+1,vector<int>((1 << (N+1)),INF));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &v[i][j]);
        }
    }
}

int traveling_sales_person(int cur,int visit)
{
    if(visit == ((1 << N)-1))
    {
        if(v[cur][0])
            return v[cur][0];
        return INF;
    }
    if(dp[cur][visit] != INF)
        return dp[cur][visit];
    
    for(int i = 0; i < N; i++)
    {
        if(v[cur][i] == 0)
            continue;
        if((visit & (1 << i)) == (1 << i))
            continue;
        
        dp[cur][visit] = min(dp[cur][visit],v[cur][i]+traveling_sales_person(i, visit | (1 << i)));
    }
    
    return dp[cur][visit];
}

int main(int argc,char* argv[])
{
    input();
    printf("%d\n", traveling_sales_person(0,1));
    return 0;
}
