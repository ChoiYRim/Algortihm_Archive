// BellmanFord Algorithm - 음수 가중치 고려

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits> // INT_MAX를 사용하기 위함

using namespace std;

struct Edge
{
    int start;
    int end;
    int weight;
};

int N,M;

vector<long long> BellmanFord(vector<Edge> edges,int V,int start)
{
    vector<long long> distance(V+1,INT_MAX);
    distance[start] = 0;
    
    for(int i = 0; i < V-1; i++)
    {
        // 전체 Edge에 대해 반복
        for(auto& e : edges)
        {
            // Edge의 시작 정점의 거리 값이 INT_MAX라면 Skip
            if(distance[e.start] == INT_MAX)
                continue;
            
            // 인접한 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면
            // 거리 값을 업데이트함
            if(distance[e.end] > distance[e.start] + e.weight)
            {
                distance[e.end] = distance[e.start] + e.weight;
            }
        }
    }
    
    for(auto& e : edges)
    {
        if(distance[e.start] == INT_MAX)
            continue;
        if(distance[e.end] > distance[e.start] + e.weight)
        {
            cout << -1 << '\n';
            exit(0);
        }
    }
    
    return distance;
}

int main(int argc, const char * argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<Edge> edges;
    
    cin >> N >> M;
    for(int i = 0; i < M; i++)
    {
        int src,dst,weight;
        cin >> src >> dst >> weight;
        edges.push_back({src-1,dst-1,weight});
    }
    
    vector<long long> result = BellmanFord(edges,N,0);
    
    for(int i = 1; i < N; i++)
    {
        if(result[i] == INT_MAX)
            cout << -1 << '\n';
        else
            cout << result[i] << '\n';
    }
    return 0;
}
