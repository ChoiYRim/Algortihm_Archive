#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

struct Node
{
    int cur;
    int cost;
    
    inline bool operator<(const Node& n) const { return cost < n.cost; }
    inline bool operator>(const Node& n) const { return cost > n.cost; }
};

int N,M,S,E;
vector<vector<pair<int,int>>> edges;

void input()
{
    cin >> N;
    cin >> M;
    edges = vector<vector<pair<int,int>>>(N+1);
    for(int i = 0; i < M; i++)
    {
        bool exist = false;
        int from,to,cost; cin >> from >> to >> cost;
        for(auto& edge : edges[from]) if(edge.first == to) { exist = true; edge.second = min(edge.second,cost); break; }
        if(!exist) edges[from].push_back({to,cost});
    }
    cin >> S >> E;
}

void get_path(vector<int>& ansv, const vector<int>& prev)
{
    int end_point = E;
    
    ansv.push_back(end_point);
    while(end_point != S)
    {
        end_point = prev[end_point];
        ansv.push_back(end_point);
    }
}

void solve()
{
    int len;
    vector<int> ansv;
    vector<int> prev(N+1,INF);
    vector<int> dist(N+1,INF);
    priority_queue<Node,vector<Node>,greater<Node>> pq;
    
    dist[S] = 0;
    pq.push({S,0});
    while(!pq.empty())
    {
        int cur = pq.top().cur;
        pq.pop();
        
        if(cur == E) continue;
        
        for(const auto& edge : edges[cur])
        {
            int to = edge.first;
            int cost = edge.second;
            
            if(dist[to] > dist[cur]+cost)
            {
                prev[to] = cur;
                dist[to] = dist[cur]+cost;
                pq.push({to,dist[to]});
            }
        }
    }
    
    cout << dist[E] << endl;
    get_path(ansv, prev);
    len = static_cast<int>(ansv.size());
    cout << len << endl; for(int i = len-1; i >= 0; i--) cout << ansv[i] << " ";
    cout << endl;
}

int main(int argc,char* argv[])
{
    input();
    solve();
    return 0;
}
