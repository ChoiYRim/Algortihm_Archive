#include <iostream>
#include <vector>

using namespace std;

const int kMax = 100001;

int N,R,Q;
vector<int> graph[kMax];
vector<int> query;
vector<int> tree;

int DFS(int cur)
{
    tree[cur]++;
    for(int i = 0; i < (int)graph[cur].size(); i++)
    {
        int node = graph[cur][i];
        
        if(!tree[node])
            tree[cur] += DFS(node);
    }
    
    return tree[cur];
}

int main()
{
    cin >> N >> R >> Q;
    tree = vector<int>(N+1,0);
    for(int i = 0; i < N-1; i++)
    {
        int v1,v2; cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    for(int i = 0; i < Q; i++)
    {
        int q; cin >> q;
        query.push_back(q);
    }
    
    DFS(R);
    for(int i = 0; i < (int)query.size(); i++)
    {
        int node = query[i];
        cout << tree[node] << '\n';
    }
    return 0;
}
