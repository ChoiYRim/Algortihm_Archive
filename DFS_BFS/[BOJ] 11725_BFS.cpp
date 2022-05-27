#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<int> parent;
vector<vector<int>> edges;

int main(int argc, char* argv[])
{
    scanf("%d", &N);
    parent = vector<int>(N+1, 0);
    edges = vector<vector<int>>(N+1);
    for(int i = 0; i < N-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    queue<int> q;
    
    q.push(1);
    parent[1] = 1;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        
        for(const auto& next : edges[cur])
        {
            if(parent[next]) continue;
            
            parent[next] = cur;
            q.push(next);
        }
    }
    
    for(int i = 2; i <= N; i++)
        printf("%d\n", parent[i]);
    return 0;
}
