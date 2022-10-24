#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int parent;
    int rank;
    int dist;
};

int N;
vector<int> edges[3001];
Node nodes[3001];
vector<int> result, visit;

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        nodes[i+1] = {i+1, 0, 0};
        
        int from, to; cin >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    
    result = vector<int>(N+1, 0);
    visit = vector<int>(N+1, 0);
}

int Find(int u)
{
    if(u == nodes[u].parent)
        return u;
    return Find(nodes[u].parent);
}

bool disjoint(int u, int v)
{
    int up = Find(u);
    int vp = Find(v);
    
    if(up == vp) return false;
    if(nodes[up].rank > nodes[vp].rank) swap(up, vp);
    
    nodes[vp].rank++;
    nodes[up].parent = vp;
    return true;
}

void output()
{
    for(int i = 1; i <= N; i++) printf("%d ", result[i]);
    printf("\n");
}

bool dfs(int cur, const int& sp, const int& ep)
{
    if(cur == ep)
    {
        return true;
    }
    
    for(const int& next : edges[cur])
    {
        if(cur == sp && next == ep) continue;
        if(!visit[next])
        {
            visit[next] = 1;
            if(dfs(next, sp, ep)) return true;
            visit[next] = 0;
        }
    }
    
    return false;
}

void solve()
{
    int u = 0, v = 0;
    
    // 1. MST 생성 + 순환 간선 찾기
    for(int from = 1; from <= N; from++)
    {
        for(auto& to : edges[from])
        {
            if(to > from) continue;
            
            if(!disjoint(from, to))
            {
                u = from;
                v = to;
            }
        }
    }
    
    // 2. u에서 v로 가는 순환 경로 찾기
    if(u != 0 && v != 0)
    {
        visit[u] = 1;
        dfs(u, u, v);
        
        for(int i = 1; i <= N; i++)
        {
            if(visit[i]) continue;
            
            queue<pair<int, int>> q;
            vector<bool> tmp(N+1, 0);
            
            tmp[i] = 1;
            q.push({i, 0});
            while(!q.empty())
            {
                int cur = q.front().first;
                int dist = q.front().second;
                q.pop();
                
                if(visit[cur])
                {
                    result[i] = dist;
                    break;
                }
                
                for(const auto& next : edges[cur])
                {
                    if(tmp[next]) continue;
                    
                    tmp[next] = 1;
                    q.push({next, dist+1});
                }
            }
        }
    }
    
    return;
}

int main(int argc, char* argv[])
{
    input();
    solve();
    output();
    return 0;
}
