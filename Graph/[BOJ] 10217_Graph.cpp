#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;
const int INF = 987654321;

struct Edge
{
    int _to;
    int _cost;
    int _time;
};

struct Node
{
    int cur;
    int cur_cost;
    int cur_time;
    
    inline bool operator<(const Node& n) const { return cur_cost < n.cur_cost; }
    inline bool operator>(const Node& n) const { return cur_cost > n.cur_cost; }
};

int T,N,M,K;
vector<vector<Edge>> edges;

void input()
{
    edges.clear();
    scanf("%d%d%d", &N, &M, &K); // 도시의 개수, 감내할 수 있는 최고 비용, 간선 개수
    edges = vector<vector<Edge>>(N+1);
    for(int i = 0; i < K; i++)
    {
        int u,v,c,d;
        scanf("%d%d%d%d", &u, &v, &c, &d);
        edges[u].push_back({v,c,d});
    }
}

string solve()
{
    int result = INF;
    vector<vector<int>> dp(N+1,vector<int>(M+1,INF)); // dp[city][cost] = time
    priority_queue<Node,vector<Node>,greater<Node>> pq;
    
    dp[1][0] = 0;
    pq.push({1,0,0});
    while(!pq.empty())
    {
        int cur = pq.top().cur;
        int cur_cost = pq.top().cur_cost;
        int cur_time = pq.top().cur_time;
        pq.pop();
        
        if(dp[cur][cur_cost] < cur_time)
            continue;
        
        for(const auto& edge : edges[cur])
        {
            int next = edge._to;
            
            if(cur_cost+edge._cost > M) continue;
            
            if(dp[next][cur_cost+edge._cost] > cur_time+edge._time)
            {
                dp[next][cur_cost+edge._cost] = cur_time+edge._time;
                pq.push({next,cur_cost+edge._cost,dp[next][cur_cost+edge._cost]});
            }
        }
    }
    
    for(int i = 1; i <= M; i++)
        result = min(result,dp[N][i]);
    if(result == INF)
        return "Poor KCM";
    return to_string(result);
}

int main(int argc,char* argv[])
{
    scanf("%d", &T);
    while(T--)
    {
        input();
        cout << solve() << endl;
    }
    
    return 0;
}
