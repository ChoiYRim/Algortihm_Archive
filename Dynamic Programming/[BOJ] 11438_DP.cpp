#include <cmath>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, M, height;
vector<int> answer, heights;
vector<vector<int>> edges, parent;

void make_tree()
{
    queue<int> q;
    vector<bool> visit(N+1,0);

    q.push(1);
    visit[1] = true;
    parent[1][0] = 0;
    heights[1] = 1;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(const auto& edge : edges[cur])
        {
            int next = edge;

            if(visit[next]) continue;

            q.push(next);
            visit[next] = true;
            parent[next][0] = cur;
            heights[next] = heights[cur]+1;
        }
    }

    for(int i = 1; i <= height; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(parent[j][i-1] == 0) continue;

            parent[j][i] = parent[parent[j][i-1]][i-1];
        }
    }
}

int Find(int u, int v)
{
    int ret;
    int u_height = heights[u];
    int v_height = heights[v];

    if(u_height > v_height)
    {
        swap(u, v);
        //swap(u_height, v_height);
    }

    // 높이 맞춰주기
    for(int i = height; i >= 0; i--)
    {
        if(heights[u] <= heights[parent[v][i]])
            v = parent[v][i];
    }

    ret = u;
    if(u != v)
    {
        for(int i = height; i >= 0; i--) // 가까운 조상부터
        {
            if(parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
            }
            ret = parent[u][i];
        }
    }

    return ret;
}

void input()
{
    scanf("%d", &N);
    height = static_cast<int>(floor(log2(N+1)));
    heights = vector<int>(N+1);
    edges = vector<vector<int>>(N+1);
    parent = vector<vector<int>>(N+1, vector<int>(height+1, 0));
    for(int i = 0; i < N-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    make_tree();
    
    scanf("%d", &M);
    for(int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        answer.push_back(Find(u, v));
    }
}

void output()
{
    for(const auto& ele : answer) printf("%d\n", ele);
}

int main(int argc, char* argv[])
{
    input();
    
    output();
    return 0;
}
