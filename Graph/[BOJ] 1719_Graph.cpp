#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

int N, M;
vector<vector<int>> result;
vector<vector<pair<int, int>>> edges;

void input()
{
    cin >> N >> M;
    
    edges = vector<vector<pair<int, int>>>(N+1);
    result = vector<vector<int>>(N+1, vector<int>(N+1, 0));
    for(int i = 0; i < M; i++)
    {
        int from, to, weight; cin >> from >> to >> weight;
        edges[from].push_back({to, weight});
        edges[to].push_back({from, weight});
    }
}

void print(int from, vector<pair<int, vector<int>>>& dist)
{
    printf("[From %d] : ", from);
    for(int i = 1; i < dist.size(); i++) printf("%d ", dist[i].first);
    printf("\n");
}

void solve()
{
    for(int from = 1; from <= N; from++)
    {
        vector<pair<int, vector<int>>> dist(N+1, {INF, {}});
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            
        dist[from].first = 0;
        pq.push({0, from});
        while(!pq.empty())
        {
            //int cost = pq.top().first;
            int cur = pq.top().second;
            pq.pop();
                
            for(auto& edge : edges[cur])
            {
                int next = edge.first;
                int cost = edge.second;
                    
                if(dist[next].first > dist[cur].first+cost)
                {
                    dist[next].first = dist[cur].first+cost;
                    dist[next].second = dist[cur].second;
                    dist[next].second.push_back(next);
                    pq.push({dist[next].first, next});
                }
            }
        }
            
        //print(from, dist);
        for(int i = 1; i <= N; i++)
        {
            if(from == i)
                continue;
            
            result[from][i] = dist[i].second[0];
        }
    }
}

void output()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(result[i][j] == 0) printf("-");
            else printf("%d", result[i][j]);
            
            if(j == N) break;
            printf(" ");
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    input();
    solve();
    output();
    return 0;
}
