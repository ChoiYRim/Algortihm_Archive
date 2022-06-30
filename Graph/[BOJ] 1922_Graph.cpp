#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Union
{
public:
    Union() = default;
    Union(int n) { nodes.reserve(n); }
    
    void make_set(int _id)
    {
        nodes.emplace_back(_id);
    }
    
    int find(int _id)
    {
        if(_id != nodes[_id].parent)
            return find(nodes[_id].parent);
        return _id;
    }
    
    void djsjoint(int _id1, int _id2)
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
    
    bool range(int _id) { return (_id >= 0 && _id < nodes.size()); }
    
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

struct Edge
{
    int from;
    int to;
    int weight;
    
    Edge(int _from, int _to, int _weight) : from(_from), to(_to), weight(_weight) { }
    
    inline bool operator<(const Edge& edge) const { return weight < edge.weight; }
    inline bool operator>(const Edge& edge) const { return weight > edge.weight; }
};

int N, M;
vector<Edge> edge_list;

void input()
{
    cin >> N;
    cin >> M;
    edge_list.reserve(M);
    for(int i = 0; i < M; i++)
    {
        int from, to, weight; cin >> from >> to >> weight;
        edge_list.emplace_back(Edge(from-1, to-1, weight));
    }
}

int solve()
{
    int ans = 0;
    Union disjoint_set(N);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    
    for(const auto& edge : edge_list) pq.push(edge);
    
    for(int i = 0; i < N; i++) disjoint_set.make_set(i);
    
    while(!pq.empty())
    {
        int u = pq.top().from;
        int v = pq.top().to;
        int w = pq.top().weight;
        pq.pop();
        
        if(disjoint_set.find(u) != disjoint_set.find(v))
        {
            disjoint_set.djsjoint(u, v);
            ans += w;
        }
    }
    
    return ans;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
