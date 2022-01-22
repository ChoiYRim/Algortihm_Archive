#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
using ll = long long;

struct Node
{
    int cur;
    ll weight;
    
    inline bool operator<(const Node& n) const { return weight < n.weight; }
    inline bool operator>(const Node& n) const { return weight > n.weight; }
};

int T,N,M,S,D;
vector<ll> ps;
vector<vector<pair<int,ll>>> nodes;

inline bool comp(const pair<int,ll>& p1,const pair<int,ll>& p2) { return p1.first < p2.first; }

auto dijkstra()
{
    priority_queue<Node,vector<Node>,greater<Node>> pq;
    vector<ll> dist(N+1,LONG_LONG_MAX);
    
    dist[S] = 0;
    pq.push({S,0});
    while(!pq.empty())
    {
        int cur = pq.top().cur;
        ll weight = pq.top().weight;
        pq.pop();
        
        if(cur == D)
            break;
        
        for(auto& node : nodes[cur]) // cur과 연결된 노드들
        {
            int next = node.first; // next 노드
            ll wait_time = 0;
            ll next_p = ps[next]; // next의 신호주기
            ll time_to_next = weight+node.second; // next까지 도달하는데 걸리는 시간
            
            // nodes[next] : next와 연결된 노드들
            size_t target;
            auto con_size = nodes[next].size();
            auto cur_idx = time_to_next / next_p % con_size;
            
            for(target = 0; target < con_size; target++)
            {
                if(nodes[next][target].first == cur)
                    break;
            }
            
            if(next != D && target != cur_idx)
            {
                wait_time = (target+con_size-cur_idx) % con_size * next_p - time_to_next % next_p;
            }
            
            if(dist[next] > time_to_next + wait_time)
            {
                dist[next] = time_to_next + wait_time;
                pq.push({next,dist[next]});
            }
        }
    }
    
    return dist[D] == LONG_LONG_MAX ? -1 : dist[D];
}

int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> T;
    while(T--)
    {
        nodes.clear();
        
        cin >> N >> M >> S >> D;
        ps = vector<ll>(N+1,0);
        nodes = vector<vector<pair<int,ll>>>(N+1);
        for(auto i = 0; i < M; i++)
        {
            int u,v; ll w;
            cin >> u >> v >> w;
            nodes[u].push_back({v,w});
            nodes[v].push_back({u,w});
        }
        for(int i = 1; i <= N; i++)
        {
            ll p;
            cin >> p;
            ps[i] = p;
            sort(nodes[i].begin(),nodes[i].end(),comp);
        }
        
        cout << dijkstra() << '\n';
    }

    return 0;
}
