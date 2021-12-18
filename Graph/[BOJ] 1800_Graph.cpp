#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

const int kMax = 987654321;

struct Node
{
    int v;
    int e;
};

struct comp
{
    bool operator()(const Node& n1,const Node& n2)
    {
        return n1.e > n2.e;
    }
};

int N,P,K,ans = -1;
std::vector<int> dist;
std::vector<Node> v[1024];

bool dijkstra(int cost)
{
    std::priority_queue<Node,std::vector<Node>,comp> pq;
    std::fill(dist.begin(), dist.end(), kMax);
    
    dist[1] = 0;
    pq.push({1,0});
    while(!pq.empty())
    {
        int vertex = pq.top().v;
        int edge = pq.top().e;
        pq.pop();
        
        if(dist[vertex] < edge) // 현재 정점까지 오는 거리 비용이
            continue;
        
        for(auto node : v[vertex])
        {
            int next_edge = edge + (node.e > cost);
            
            if(next_edge < dist[node.v])
            {
                dist[node.v] = next_edge;
                pq.push({node.v,next_edge});
            }
        }
    }
    
    return dist[N] <= K;
}

int main()
{
    int left = 0,right = 0,mid;

    std::cin >> N >> P >> K;
    dist = std::vector<int>(N+1,kMax);
    for(int i = 0; i < P; i++)
    {
        int c1,c2,cost; std::cin >> c1 >> c2 >> cost;
        v[c1].push_back({c2,cost});
        v[c2].push_back({c1,cost});
        right = std::max(right,cost);
    }
    
    while(left <= right)
    {
        mid = (left+right) >> 1;
        
        if(dijkstra(mid))
        {
            ans = mid;
            right = mid-1;
        }
        else
            left = mid+1;
    }
    
    std::cout << ans << '\n';
    return 0;
}
