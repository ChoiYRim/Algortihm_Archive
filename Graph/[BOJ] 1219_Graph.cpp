#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
using ll = long long;

struct Edge
{
    int from;
    int to;
    ll cost;
};

int N,M,S,E;
vector<ll> pays;
vector<Edge> edges;

void input()
{
    scanf("%d%d%d%d", &N, &S, &E, &M);
    for(int i = 0; i < M; i++)
    {
        int from,to;
        ll cost;
        scanf("%d%d%lld", &from, &to, &cost);
        edges.push_back({from,to,cost});
    }
    for(int i = 0; i < N; i++)
    {
        ll pay;
        scanf("%lld", &pay);
        pays.push_back(-pay);
    }
    for(auto& edge : edges)
    {
        int to = edge.to;
        ll& cost = edge.cost;
        
        cost += pays[to];
    }
}

string bellman_ford()
{
    bool is_cycle = false;
    vector<ll> dist(N,LONG_LONG_MAX),new_dist;
    
    dist[S] = pays[S];
    for(int i = 0; i < N-1; i++)
    {
        for(auto& edge : edges)
        {
            int from = edge.from;
            int to = edge.to;
            ll cost = edge.cost;
            
            if(dist[from] == LONG_LONG_MAX) continue;
            
            if(dist[to] > dist[from]+cost)
            {
                dist[to] = dist[from]+cost;
            }
        }
    }
    if(dist[E] == LONG_LONG_MAX)
        return "gg";
    
    new_dist = dist;
    for(auto& edge : edges)
    {
        int from = edge.from;
        int to = edge.to;
        ll cost = edge.cost;
        
        if(dist[from] == LONG_LONG_MAX) continue;
        
        if(dist[to] > dist[from]+cost)
        {
            is_cycle = true;
            new_dist[to] = new_dist[from]+cost;
        }
    }
    
    if(is_cycle)
    {
        for(int i = 0; i < dist.size(); i++)
        {
            if(dist[i] != new_dist[i])
            {
                bool reach = false;
                vector<bool> visit(N+1,0);
                queue<int> q;
                
                visit[i] = true;
                q.push(i);
                while(!q.empty())
                {
                    int cur = q.front();
                    q.pop();
                    
                    if(cur == E)
                    {
                        reach = true;
                        break;
                    }
                    
                    for(auto& edge : edges)
                    {
                        if(edge.from != cur) continue;
                        
                        int next = edge.to;
                        if(!visit[next])
                        {
                            visit[next] = true;
                            q.push(next);
                        }
                    }
                }
                if(reach)
                    return "Gee";
            }
        }
    }
    
    return to_string(-dist[E]);
}

int main(int argc,char* argv[])
{
    input();
    cout << bellman_ford() << endl;
    return 0;
}
