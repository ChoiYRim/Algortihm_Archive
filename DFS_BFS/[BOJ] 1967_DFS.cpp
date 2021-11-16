#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
 
int n;
int visited[10002] = {0};
vector<pair<int,int>> node[10002];
 
int ans = 0; //지름 길이
int last_node = 0; //지름에 해당하는 끝점

void DFS(int point,int weight)
{
    if(visited[point])
        return;
    
    visited[point] = 1;
    
    if(ans < weight)
    {
        ans = weight;
        last_node = point;
    }
    
    for(int i = 0; i < (int)node[point].size(); i++)
        DFS(node[point][i].first,weight+node[point][i].second);
}
 
int main()
{
    cin >> n;
    
    int parent,child,weight;
    for(int i=0;i<n-1;i++)
    {
        cin >> parent >> child >> weight;
        node[parent].push_back(make_pair(child,weight));
        node[child].push_back(make_pair(parent,weight));
    }
    
    DFS(1,0);
    ans = 0;
    memset(visited,0,sizeof(visited));
    
    DFS(last_node,0);
    cout << ans << '\n';
    return 0;
}
