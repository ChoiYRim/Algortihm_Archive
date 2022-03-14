#include <queue>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

struct Node
{
    int from;
    ll cost;
    
    inline bool operator<(const Node& n) const { return cost < n.cost; }
    inline bool operator>(const Node& n) const { return cost > n.cost; }
};

struct Edge
{
    int to;
    ll cost;
};

void init(int n,int m,int t,vector<vector<Edge>>& edges,vector<int>& dst)
{
    edges = vector<vector<Edge>>(n+1);
    dst = vector<int>(t);
    
    for(int i = 0; i < m; i++)
    {
        int a,b;
        ll d;
        scanf("%d%d%lld", &a, &b, &d);
        edges[a].push_back({b,d});
        edges[b].push_back({a,d});
    }
    for(int i = 0; i < t; i++)
    {
        int x;
        scanf("%d", &x);
        dst[i] = x;
    }
}

void dijkstra(int start,vector<ll>& dist,const vector<vector<Edge>>& edges)
{
    priority_queue<Node,vector<Node>,greater<Node>> pq;
    
    pq.push({start,dist[start]});
    while(!pq.empty())
    {
        int from = pq.top().from;
        pq.pop();
        
        for(const auto& edge : edges[from])
        {
            int to = edge.to;
            ll to_cost = edge.cost;
            
            if(dist[to] > dist[from]+to_cost)
            {
                dist[to] = dist[from]+to_cost;
                pq.push({to,dist[to]});
            }
        }
    }
}

vector<int> solve(int n,int s,int g,int h,const vector<vector<Edge>>& edges,vector<int>& dsts)
{
    int new_start = 0;
    vector<int> ret;
    vector<ll> dist_from(n+1,LONG_LONG_MAX);
    vector<ll> dist_close(n+1,LONG_LONG_MAX);
    vector<ll> straight(n+1,LONG_LONG_MAX); // 출발점에서 도착지로 straight
    
    straight[s] = 0;
    dijkstra(s, straight, edges);
    
    dist_from[s] = 0;
    dijkstra(s, dist_from, edges);
    if(dist_from[g] <= dist_from[h])
    {
        new_start = h;
        dist_close[h] = 0;
        dijkstra(h, dist_close, edges);
    }
    else
    {
        new_start = g;
        dist_close[g] = 0;
        dijkstra(g, dist_close, edges);
    }
        
    sort(dsts.begin(),dsts.end());
    for(int i = 0; i < dsts.size(); i++)
    {
        int dst = dsts[i];
        if(dist_from[new_start]+dist_close[dst] == straight[dst])
            ret.push_back(dst);
    }
    
    return ret;
}

void output(const vector<int>& result)
{
    for(const auto& ele : result)
        printf("%d ", ele);
    printf("\n");
}

int main(int argc,char* argv[])
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        vector<vector<Edge>> edges;
        vector<int> dst;
        
        int n,m,t; // 정점, 간선, 예상 목적지 개수
        scanf("%d%d%d", &n, &m, &t);
        int s,g,h; // 출발지, [g,h] 교차로 -> 무조건 지나야함
        scanf("%d%d%d", &s, &g, &h);
        
        init(n,m,t,edges,dst);
        auto result = solve(n, s, g, h, edges, dst);
        output(result);
    }
    
    return 0;
}
