#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string_view>

using namespace std;

int TC,V,E;
int types[20001];
vector<int> edges[20001];
vector<string> result;

void debug()
{
    cout << "Vertex : " << V << endl << endl;
    
    cout << "Edges  : " << E << endl;
    for(int i = 1; i <= V; i++)
    {
        cout << i << " : ";
        for(auto& j : edges[i])
            cout << j << " ";
        cout << endl;
    }
    
    cout << "Types" << endl;
    for(int i = 1; i <= V; i++)
    {
        cout << i << " : " << types[i] << endl;
    }
}

void print_result()
{
    for(auto& str : result)
        cout << str.data() << endl;
}

void dfs(int cur,int type)
{
    types[cur] = type;
    for(auto i = 0; i < edges[cur].size(); i++)
    {
        int next = edges[cur][i];
        
        if(types[next] != -1)
            continue;
        
        dfs(next,!type);
    }
}

bool check()
{
    for(int i = 1; i <= V; i++)
    {
        int cur = types[i];
        for(auto& j : edges[i])
        {
            int next = types[j];
            
            if(cur == next)
                return false;
        }
    }
    
    return true;
}

int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> TC;
    while(TC--)
    {
        memset(edges,{},sizeof(edges));
        memset(types,-1,sizeof(types));
        
        cin >> V >> E;
        for(int i = 0; i < E; i++)
        {
            int u,v; cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        
        for(int i = 1; i <= V; i++)
        {
            if(types[i] != -1)
                continue;
            
            dfs(i,0);
        }
        
        if(check())
            result.push_back("YES");
        else
            result.push_back("NO");
        //debug();
    }
    
    print_result();
    return 0;
}
