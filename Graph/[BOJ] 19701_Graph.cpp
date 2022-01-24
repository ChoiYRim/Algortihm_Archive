#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;
using ll = long long;
const ll INF = LONG_LONG_MAX;

int V,E;
const int MAX = 1E9;
vector<vector<pair<int,ll>>> graph;

struct Edge
{
    int idx;
    ll weight;
    
    inline bool operator<(const Edge& e) const { return weight < e.weight; }
    inline bool operator>(const Edge& e) const { return weight > e.weight; }
};

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> V >> E;
    graph = vector<vector<pair<int,ll>>>(2*(V+1));
    for(int i = 0; i < E; i++)
    {
        int u,v,t,k;
        cin >> u >> v >> t >> k;
        
        // 2개의 층으로 나눔
        // 1.
        graph[u].push_back({v,t});
        graph[v].push_back({u,t});
        
        // 2.
        graph[u+V+1].push_back({v+V+1,t});
        graph[v+V+1].push_back({u+V+1,t});
        
        // 3. 돈가쓰를 먹었을 경우 (MAX를 더하는건 음수 가중치를 방지하기 위한 의미없는 수)
        graph[u].push_back({v+V+1,MAX+t-k});
        graph[v].push_back({u+V+1,MAX+t-k});
    }
}

int main()
{
    input();
    
    vector<ll> dist(2*V+2,INF);
    priority_queue<Edge,vector<Edge>,greater<Edge>> pq;
    
    dist[1] = 0;
    pq.push({1,0});
    while(!pq.empty())
    {
        int cur = pq.top().idx;
        ll weight = pq.top().weight;
        pq.pop();
        
        for(auto& edge : graph[cur])
        {
            int next = edge.first;
            ll weight_to_next = edge.second;
            
            if(dist[next] > weight+weight_to_next)
            {
                pq.push({next,weight+weight_to_next});
                dist[next] = weight+weight_to_next;
            }
        }
    }
    
    for(size_t i = 2; i <= V; i++)
        cout << dist[i+V+1] - MAX << '\n';
    return 0;
}
