#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
using ll = long long;
int parent[10001] = {0,};

struct Edge
{
    int from;
    int to;
    ll weight;
    
    Edge() { }
    
    Edge(int _from,int _to,ll _weight) : from(_from), to(_to), weight(_weight) { }
    
    bool operator<(const Edge& e) const
    {
        return weight < e.weight;
    }
    
    bool operator>(const Edge& e) const
    {
        return weight > e.weight;
    }
};

void input(int& V,int& E,vector<Edge>& edge_list)
{
    cin >> V >> E;
    for(int i = 0; i < E; i++)
    {
        int u,v; ll w; cin >> u >> v >> w;
        edge_list.push_back({u,v,w});
    }
    for(int i = 1; i <= V; i++)
        parent[i] = i;
}

auto find(int node_idx)
{
    if(node_idx == parent[node_idx])
        return node_idx;
    return find(parent[node_idx]);
}

auto union_set(int x,int y)
{
    int root_x = find(x);
    int root_y = find(y);
    
    if(root_x < root_y)
    {
        parent[root_y] = root_x;
        return;
    }
    
    parent[root_x] = root_y;
}

int main()
{
    int V,E;
    ll sum = 0;
    vector<Edge> edge_list;
    
    input(V,E,edge_list);
    
    priority_queue<Edge,vector<Edge>,greater<Edge>> pq; // min heap
    for(auto& edge : edge_list)
        pq.push(edge);
    
    while(!pq.empty())
    {
        Edge node = pq.top();
        pq.pop();
        
        if(find(node.from) != find(node.to))
        {
            union_set(node.from, node.to);
            sum += node.weight;
        }
    }
    
    cout << sum << endl;
    return 0;
}
