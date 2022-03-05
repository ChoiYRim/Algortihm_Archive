#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

int n,m;
int graph[256][256];
int list[1024];
map<int,int> link;

int find(int node)
{
    if(link[node] == node)
        return node;
    return link[node] = find(link[node]);
}

void input()
{
    scanf("%d", &n);
    scanf("%d", &m);
    for(int i = 1; i <= n; i++)
    {
        link[i] = i;
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
    for(int i = 0; i < m; i++)
        scanf("%d", &list[i]);
}

void make_disjoint_set()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            if(!graph[i][j])
                continue;
            
            int a = find(i);
            int b = find(j);
            
            if(a == b)
                continue;
            link[a] = b;
        }
    }
}

int main(int argc,char* argv[])
{
    input();
    make_disjoint_set();
    
    bool possible = true;
    int root = find(list[0]);
    for(int i = 1; i < m; i++)
    {
        if(root != find(list[i]))
        {
            possible = false;
            break;
        }
    }
    
    if(possible) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
