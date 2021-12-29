#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MAX 16

using namespace std;

int N;
int W[MAX][MAX];
int dp[MAX][1 << MAX];
int answer;
const int MAX_NUM = 987654321;

int dfs(int curCity,int curBit)
{
    if(curBit == answer) // 모든 도시를 방문했다면
    {
        if(W[curCity][0] == 0) // 마지막으로 방문한 도시에서 시작 도시로 가는 길이 없다면
            return MAX_NUM; // Fail
        else
            return W[curCity][0]; // 마지막 경로를 더해주기 위해 return
    }

    if(dp[curCity][curBit] != -1) // 이미 방문한 적이 있다면 - 저장되어 있는 최소값 리턴
        return dp[curCity][curBit];
    dp[curCity][curBit] = MAX_NUM; // 방문한 적 없다면 최대값

    for (int i = 0; i < N; i++)
    {
        if(W[curCity][i] == 0) // 경로 없음
            continue;
        if((curBit & (1 << i)) == (1 << i))  // 방문한 경력이 있음
            continue;

        // dfs로 모든 도시 방문
        dp[curCity][curBit] = min(dp[curCity][curBit],W[curCity][i] + dfs(i, curBit | 1 << i));
    }

    return dp[curCity][curBit];
}

int main(void)
{
    memset((int *)W,0,sizeof(W));
    memset((int *)dp,-1,sizeof(dp));

    scanf("%d", &N);

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            scanf("%d", &W[i][j]);

    answer = (1 << N) - 1; // 1111111....1

    // dp[M][N] : M에서 N까지의 최소 비용 경로
    // 반드시 한 도시를 한번만 방문해야함.

    printf("%d\n", dfs(0,1));

    return 0;
}
