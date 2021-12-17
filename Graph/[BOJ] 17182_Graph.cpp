#include <iostream>

const int kMax = 0x7fffffff;

int N,K,ans = kMax;
int arr[16][16] = {0,};
int visit[16]  = {0, };

inline int MIN(int a,int b) { return (a > b ? b : a); }

void dfs(int depth,int node,int cost)
{
    if(ans < cost)
        return;
    if(depth >= N)
    {
        ans = MIN(ans,cost);
        return;
    }
    
    for(int next = 0; next < N; next++) // 완전 탐색
    {
        if(!visit[next])
        {
            visit[next] = 1;
            dfs(depth+1,next,cost+arr[node][next]);
            visit[next] = 0;
        }
    }
}

int main()
{
    std::cin >> N >> K;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            std::cin >> arr[i][j];
        }
    }
    
    // Floyd - Warshall
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < N; k++)
            {
                arr[i][j] = MIN(arr[i][j],arr[i][k]+arr[k][j]);
            }
        }
    }
    
    visit[K] = 1;
    dfs(1,K,0);
    std::cout << ans << '\n';
    return 0;
}
