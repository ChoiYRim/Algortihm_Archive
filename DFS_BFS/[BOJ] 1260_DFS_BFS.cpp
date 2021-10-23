#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MAX 1010

using namespace std;

int n,m,v;
queue<int> q;
vector<int> vec;
bool visited[MAX];
bool node[MAX][MAX];

void dfs(int start)
{
    for(int i = 1; i <= n; i++)
    {
        if(node[start][i] && !visited[i])
        {
            visited[i] = true;
            vec.push_back(i);
            dfs(i);
        }
    }
}

int main(void)
{
    memset((bool *)node,0,sizeof(node));
    memset((bool *)visited,0,sizeof(visited));

    scanf("%d %d %d", &n, &m, &v);

    for(int i = 0; i < m; i++)
    {
        int tmp1,tmp2;
        scanf("%d %d", &tmp1, &tmp2);
        node[tmp1][tmp2] = true;
        node[tmp2][tmp1] = true;
    }

    // DFS
    visited[v] = true;
    vec.push_back(v);
    dfs(v);
    for(int i = 0; i < vec.size(); i++)
        printf("%d ", vec[i]);
    printf("\n");

    vec.clear();
    memset((bool *)visited,0,sizeof(visited));

    // BFS
    q.push(v);
    visited[v] = true;
    while(!q.empty())
    {
        int vertex = q.front();
        vec.push_back(vertex);
        q.pop();
        for(int i = 1; i <= n; i++)
        {
            if(node[vertex][i] && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    for(int i = 0; i < vec.size(); i++)
        printf("%d ", vec[i]);
    printf("\n");

    return 0;
}
