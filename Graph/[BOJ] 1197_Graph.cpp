#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

template <typename T>
class Union
{
public:
    Union(int vertecies)
    {
        nodes.reserve(vertecies);
    }
    
    void make_set(int _id)
    {
        nodes.emplace_back(_id);
    }
    
    int find(int _id)
    {
        if(nodes[_id].parent != _id)
            return find(nodes[_id].parent);
        return _id;
    }
    
    void disjoint(int _id1, int _id2)
    {
        int id1_root = find(_id1);
        int id2_root = find(_id2);
        
        if(id1_root == id2_root)
            return;
        if(nodes[id1_root].rank > nodes[id2_root].rank)
            swap(id1_root, id2_root);
        
        nodes[id1_root].parent = id2_root;
        nodes[id2_root].rank++;
    }
    
    virtual ~Union() { }
    
private:
    struct Node
    {
        int id;
        int rank;
        int parent;
        
        Node(int _id) : id(_id), rank(0), parent(_id) { }
        
        inline bool operator!=(const Node& node) const { return id != node.id; }
    };
    
    vector<Node> nodes;
};

template <typename T>
struct Edge
{
    int from;
    int to;
    T weight;
    
    Edge() = default;
    
    Edge(int _from, int _to, T _weight) : from(_from), to(_to), weight(_weight) { }
    
    inline bool operator<(const Edge& edge) const { return weight < edge.weight; }
    
    inline bool operator>(const Edge& edge) const { return weight > edge.weight; }
};

template <typename T>
class Graph
{
public:
    Graph(int _vertecies) : vertecies(_vertecies) { }
    
    int get_vertex() { return vertecies; }
    
    auto& get_edges() { return edge_list; }
    
    auto get_edges_from_v(int v)
    {
        vector<Edge<T>> edges_fromt_v;
        
        for(auto edge : edge_list)
        {
            if(edge.from == v)
                edges_fromt_v.emplace_back(edge);
        }
        
        return edges_fromt_v;
    }
    
    bool range(int v) { return (v >= 0 && v < vertecies); }
    
    void add_edge(const Edge<T>&& edge)
    {
        if(range(edge.from) && range(edge.to))
        {
            edge_list.emplace_back(edge);
        }
    }
    
private:
    int vertecies;
    vector<Edge<T>> edge_list;
};

auto get_minimum_spanning_tree(Graph<ll>& graph)
{
    Graph<ll> tmp(graph.get_vertex());
    Union<ll> dset(graph.get_vertex());
    priority_queue<Edge<ll>, vector<Edge<ll>>, greater<Edge<ll>>> pq;
    
    auto edge_list = graph.get_edges();
    for(const auto& edge : edge_list) pq.push(edge);
    
    for(int i = 0; i < graph.get_vertex(); i++) dset.make_set(i);
    
    while(!pq.empty())
    {
        int from = pq.top().from;
        int to = pq.top().to;
        ll weight = pq.top().weight;
        pq.pop();
        
        if(dset.find(from) != dset.find(to)) // no cycle
        {
            tmp.add_edge(Edge<ll>(from, to, weight));
            dset.disjoint(from, to);
        }
    }
    
    return tmp;
}

int main(int argc, char* argv[])
{
    int v, e;
    ll sum = 0;
    
    cin >> v >> e;
    Graph<ll> g(v);
    for(int i = 0; i < e; i++)
    {
        int from, to;
        ll weight;
        cin >> from >> to >> weight;
        g.add_edge(Edge<ll>(from-1, to-1, weight));
    }
    
    Graph<ll> mst = get_minimum_spanning_tree(g);
    auto edge_list = mst.get_edges();
    for(const auto& edge : edge_list)
    {
        sum += edge.weight;
    }
    
    cout << sum << endl;
    return 0;
}
