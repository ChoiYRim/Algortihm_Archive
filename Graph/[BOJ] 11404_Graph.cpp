#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll INF = 0x7fffffff;

int N,M;
vector<vector<ll>> edges;

void input()
{
    scanf("%d", &N);
    scanf("%d", &M);
    edges = vector<vector<ll>>(N+1,vector<ll>(N+1,INF));
    for(int i = 0; i < M; i++)
    {
        int a,b;
        ll c;
        scanf("%d%d%lld", &a, &b, &c);
        edges[a][b] = min(edges[a][b],c);
    }
}

void output()
{
    for(int mid = 1; mid <= N; mid++)
    {
        for(int from = 1; from <= N; from++)
        {
            for(int to = 1; to <= N; to++)
            {
                if(from == to) continue;
                if(edges[from][mid] == INF || edges[mid][to] == INF) continue;
                
                if(edges[from][to] > edges[from][mid]+edges[mid][to])
                {
                    edges[from][to] = edges[from][mid]+edges[mid][to];
                }
            }
        }
    }
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(edges[i][j] >= INF)
                printf("0 ");
            else
                printf("%lld ", edges[i][j]);
        }
        printf("\n");
    }
}

int main(int argc,char* argv[])
{
    input();
    output();
    return 0;
}
