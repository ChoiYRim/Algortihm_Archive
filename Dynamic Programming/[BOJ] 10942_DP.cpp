#include <cstdio>

int N,M;
int v[2001] = {0,};
int dp[2001][2001] = {0,}; // [s][cnt] : s번째 수부터 s+cnt-1까지의 수가 팰린드롬인가?

int main()
{
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
    {
        scanf("%d", &v[i]);
        dp[0][i] = 1;
        dp[1][i] = 1;
    }
    
    for(int cnt = 2; cnt <= N; cnt++) // 개수
    {
        for(int s = 1; s <= N; s++) // 시작점
        {
            int e = s+cnt-1;
            
            if(v[s] == v[e] && dp[cnt-2][s+1])
                dp[cnt][s] = 1;
        }
    }
    
    scanf("%d", &M);
    for(int i = 0; i < M; i++)
    {
        int s,e;
        scanf("%d %d", &s, &e);
        int cnt = e-s+1;
        printf("%d\n", dp[cnt][s]);
    }
    return 0;
}
