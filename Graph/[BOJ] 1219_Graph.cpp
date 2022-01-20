#include <queue>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N,M,start,last;
vector<ll> pays;
vector<pair<int,pair<int,ll>>> edges;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> start >> last >> M;
    for(int i = 0; i < M; i++)
    {
        int src,dst;
        ll weight;
        cin >> src >> dst >> weight;
        edges.push_back({src,{dst,weight}});
    }
    for(int i = 0; i < N; i++)
    {
        ll pay; cin >> pay;
        pays.push_back(-pay);
    }
    for(auto& e : edges)
    {
        int dst = e.second.first;
        ll& weight = e.second.second;
        
        weight += pays[dst];
    }
    
    bool cycle = false;
    vector<ll> dist(N,LONG_LONG_MAX);
    dist[start] = pays[start];
    
    // N-1번 반복
    for(int i = 0; i < N-1; i++)
    {
        for(auto& e : edges)
        {
            int src = e.first;
            int dst = e.second.first;
            ll weight = e.second.second;
            
            if(dist[src] == LONG_LONG_MAX)
                continue;
            
            if(dist[dst] > dist[src]+weight)
            {
                dist[dst] = dist[src]+weight;
            }
        }
    }
    
    if(dist[last] == LONG_LONG_MAX)
    {
        cout << "gg" << endl;
        return 0;
    }
    
    vector<ll> new_dist = dist;
    for(auto& e : edges)
    {
        int src = e.first;
        int dst = e.second.first;
        ll weight = e.second.second;
        
        if(dist[src] == LONG_LONG_MAX)
            continue;
        
        if(dist[dst] > dist[src]+weight)
        {
            cycle = true;
            new_dist[dst] = new_dist[src]+weight;
        }
    }
    
    if(cycle)
    {
        for(auto i = 0; i < dist.size(); i++)
        {
            if(dist[i] != new_dist[i]) // 사이클이 발생한 지점
            {
                bool on = false,off = false; // 시작점이 cycle에 닿을 수 있어? / cycle에서 도착점에 갈 수 있음?
                
                if(dist[i] != LONG_LONG_MAX) // 시작점이 cycle에 갈 수 있음
                    on = true;
                 
                bool visit[64] = {0,};
                queue<int> q;
                
                visit[i] = true;
                q.push(i);
                while(!q.empty())
                {
                    int cur = q.front();
                    q.pop();
                    
                    if(cur == last)
                    {
                        off = true;
                        break;
                    }
                    
                    for(auto& e : edges)
                    {
                        if(e.first != cur)
                            continue;
                        
                        int next = e.second.first;
                        
                        if(!visit[next])
                        {
                            visit[next] = true;
                            q.push(next);
                        }
                    }
                }
                
                if(on && off)
                {
                    cout << "Gee" << endl;
                    return 0;
                }
            }
        }
    }
    cout << -dist[last] << endl;
    return 0;
}
