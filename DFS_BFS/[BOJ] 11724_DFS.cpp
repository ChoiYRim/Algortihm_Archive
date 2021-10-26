#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N,M,ans = 0;
vector<int> graph[1024];
bool visit[1024] = {0,};

void DFS(int cur)
{
    visit[cur] = true;
    for(int i = 0; i < (int)graph[cur].size(); i++)
    {
        int next = graph[cur][i];
        
        if(!visit[next])
            DFS(next);
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++)
    {
        int u,v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    for(int i = 1; i <= N; i++)
    {
        if(!visit[i])
        {
            DFS(i);
            ans++;
        }
    }
    
    cout << ans << '\n';
    return 0;
}
