#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N,M;
vector<pair<int, int>> parent;
vector<vector<int>> nodes;

void make_tree()
{
    vector<bool> visit(N+1,0);
    queue<pair<int, int>> q;
    
    visit[1] = true;
    parent[1] = {1,0};
    q.push({1,0});
    while(!q.empty())
    {
        int cur = q.front().first;
        int depth = q.front().second;
        q.pop();
        
        for(const auto& node : nodes[cur])
        {
            int next = node;
            
            if(visit[next]) continue;
            
            visit[next] = true;
            parent[next] = {cur, depth+1};
            q.push({next, depth+1});
        }
    }
}

int Find(int u, int v)
{
    int u_depth = parent[u].second;
    int v_depth = parent[v].second;
    
    if(u_depth > v_depth) { swap(u, v); swap(u_depth, v_depth); }
    
    while(u_depth != v_depth)
    {
        v = parent[v].first;
        v_depth--;
    }
    
    while(u != v)
    {
        u = parent[u].first;
        v = parent[v].first;
    }
    
    return u;
}

void solve()
{
    scanf("%d", &N);
    parent = vector<pair<int, int>>(N+1);
    nodes = vector<vector<int>>(N+1);
    for(int i = 0; i < N-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        nodes[u].push_back(v);
        nodes[v].push_back(u);
    }
    
    make_tree();
    
    scanf("%d", &M);
    for(int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", Find(u, v));
    }
}

int main(int argc, char* argv[])
{
    solve();
    return 0;
}
