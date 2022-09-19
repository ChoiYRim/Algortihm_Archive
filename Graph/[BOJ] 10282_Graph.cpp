#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

int T, N, D, C;
vector<vector<pair<int, int>>> graph;

int solve()
{
    int cnt = 1, result = 0;
    vector<int> pre(N+1, 0), visit(N+1, 0), dist(N+1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    pre[C] = C;
    dist[C] = 0;
    visit[C] = 1;
    pq.push({0, C});
    while(!pq.empty())
    {
        //int cur_cost = pq.top().first;
        int cur_comp = pq.top().second;
        pq.pop();
        
        for(auto& node : graph[cur_comp])
        {
            int next_comp = node.first;
            int cost = node.second;
            
            if(dist[next_comp] > dist[cur_comp]+cost)
            {
                if(!visit[next_comp])
                {
                    visit[next_comp] = 1;
                    cnt++;
                }
                
                pre[next_comp] = cur_comp;
                dist[next_comp] = dist[cur_comp]+cost;
                pq.push({dist[next_comp], next_comp});
            }
        }
    }
    
    for(int i = 1; i <= N; i++)
    {
        int idx = i, sum = 0;
        while(pre[idx] != idx)
        {
            sum += dist[idx]-dist[pre[idx]];
            idx = pre[idx];
        }
        
        result = max(result, sum);
    }
    
    cout << cnt << " ";
    
    return result;
}

int main(int argc, char* argv[])
{
    cin >> T;
    while(T--)
    {
        cin >> N >> D >> C;
        
        graph = vector<vector<pair<int, int>>>(N+1);
        for(int i = 0; i < D; i++)
        {
            int from, to, cost; cin >> to >> from >> cost;
            graph[from].push_back({to, cost});
        }
        
        cout << solve() << endl;
    }
    
    return 0;
}
