#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int kMax = 100001;

int V,W = 0,node;
bool visit[kMax] = {0,};
vector<pair<int,int>> graph[kMax];

void DFS(int cur,int weight)
{
    if(visit[cur])
        return;
    
    visit[cur] = true;
    if(weight > W)
    {
        W = weight;
        node = cur;
    }
    
    for(int i = 0; i < (int)graph[cur].size(); i++)
    {
        int v = graph[cur][i].first;
        int e = graph[cur][i].second;
        
        DFS(v,weight+e);
    }
}

int main()
{
    cin >> V;
    for(int i = 1; i <= V; i++)
    {
        int input,cnt = 0,cur = 0,v = 0,sum = 0;
        while(1)
        {
            cin >> input;
            if(input == -1)
                break;
            
            if(cnt == 0)
                cur = input;
            else if(cnt%2 != 0) // vertex
                v = input;
            else
            {
                graph[cur].push_back({v,input});
                sum += input;
            }
            cnt++;
        }
    }
    
    DFS(1,0);
    memset((bool *)visit,0,sizeof(visit));
    DFS(node,0);
    
    cout << W << '\n';
    return 0;
}
