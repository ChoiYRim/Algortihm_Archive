#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

int n,m;
map<int,int> link;

int find(int node)
{
    if(link[node] == -1)
        return node;
    return link[node] = find(link[node]);
}

int main(int argc,char* argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; i++)
        link[i] = -1;
    
    for(int i = 0; i < m; i++)
    {
        int s,a,b;
        scanf("%d%d%d", &s, &a, &b);
        
        if(s == 0)
        {
            a = find(a);
            b = find(b);
            
            if(a == b)
                continue;
            link[a] = b;
            continue;
        }
        
        printf("%s\n", (find(a) == find(b) ? "YES" : "NO"));
    }
    
    return 0;
}
