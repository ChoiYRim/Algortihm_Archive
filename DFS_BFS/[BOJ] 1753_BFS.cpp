#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

const int kInf = 987654321;
const int kVertex = 20010;

int vertex, edge, start;
int u, v, w;
std::vector<std::pair<int,int>> graph[kVertex];
std::priority_queue<std::pair<int,int>> pq;

int main(int argc, char *argv[])
{
    std::cin >> vertex >> edge >> start;

    for(int i = 1; i <= edge; ++i)
    {
        std::cin >> u >> v >> w;
        graph[u].push_back({v,w});
    }
    
    int location,weight;
    std::vector<int> dist(vertex+1, kInf);

    dist[start] = 0;
    pq.push(std::make_pair(0, start));

    while (!pq.empty())
    {
        weight = -pq.top().first;
        location = pq.top().second;
        pq.pop();
        
        if(dist[location] < weight)
            continue;
        
        for(int i = 0; i < (int)graph[location].size(); i++)
        {
            int next_location = graph[location][i].first;
            int next_weight = graph[location][i].second;
            
            dist[next_location] = std::min(dist[next_location],weight+next_weight);
            pq.push({-1*next_weight,next_location});
        }
    }

    for(int i = 1; i < vertex+1; ++i)
        dist[i] == kInf ? std::cout << "INF\n" : std::cout << dist[i] << '\n';

    return 0;
}
