// 답지 참조

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int N, M;
const int P = 100000;
const ll S = 1E9;
const ll INF = 1E18;
vector<pair<ll, int>> adj[200005];
ll dist[200005];
priority_queue<pair<ll, int>> pq;

void add_edge(int u, int v, ll w)
{
    adj[u].push_back({w, v});
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    while (M--)
    {
        int u, v, t, k;
        cin >> u >> v >> t >> k;
        
        add_edge(u, v, t);
        add_edge(v, u, t);
        
        add_edge(P+u, P+v, t);
        add_edge(P+v, P+u, t);
        
        add_edge(u, P+v, S+t-k);
        add_edge(v, P+u, S+t-k);
    }
    
    for (int i = 1; i <= P+N; i++)
        dist[i] = INF;
    
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty())
    {
        ll _; int u;
        tie(_, u) = pq.top();
        pq.pop();
        _ = -_; // 기본 pq가 최소 힙이기 때문에
        
        if (_ > dist[u])
            continue;
        
        for (auto p: adj[u])
        {
            ll w; int v;
            tie(w, v) = p;
            
            ll dist_v = dist[u] + w;
            
            if (dist_v < dist[v])
            {
                pq.push({-dist_v, v});
                dist[v]  = dist_v;
            }
        }
    }
    
    for (int i = 2; i <= N; i++)
        cout << dist[i+P] - S << '\n';
}
