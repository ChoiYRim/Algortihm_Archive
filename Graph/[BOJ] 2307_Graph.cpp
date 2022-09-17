#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

int N, M;
vector<int> dist, before;
vector<vector<bool>> block;
vector<vector<pair<int, int>>> edges;

void input()
{
    scanf("%d%d", &N, &M);
    dist = vector<int>(N+1, INF);
    before = vector<int>(N+1, 0);
    block = vector<vector<bool>>(N+1, vector<bool>(N+1, 0));
    edges = vector<vector<pair<int, int>>>(N+1);
    for(int i = 0; i < M; i++)
    {
        int from, to, cost;
        scanf("%d%d%d", &from, &to, &cost);
        
        edges[from].push_back({to, cost});
        edges[to].push_back({from, cost});
        block[from][to] = block[to][from] = 1;
    }
}

int get_fastest_time()
{
    dist = vector<int>(N+1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[1] = 0;
    before[1] = 1;
    pq.push({0, 1});
    while(!pq.empty())
    {
        int from = pq.top().second;
        pq.pop();
        
        for(auto& edge : edges[from])
        {
            int to = edge.first;
            int cost = edge.second;
                        
            if(!block[from][to]) continue;
            if(dist[to] > dist[from]+cost)
            {
                dist[to] = dist[from]+cost;
                before[to] = from;
                pq.push({dist[to], to});
            }
        }
    }
    
    return dist[N];
}

int solve()
{
    int result = 0;
    int dijkstra_time = get_fastest_time();
    queue<int> path;
    
    path.push(N);
    while(!path.empty())
    {
        int cur = path.front();
        path.pop();
        
        int pre = before[cur];
        if(pre == cur) break;
        path.push(pre);
        
        block[pre][cur] = block[cur][pre] = 0;
        int delay = get_fastest_time();
        if(delay >= INF) { result = -1; break; }
        result = max(result, delay-dijkstra_time);
        block[cur][pre] = block[pre][cur] = 1;
    }
    
    return result;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
