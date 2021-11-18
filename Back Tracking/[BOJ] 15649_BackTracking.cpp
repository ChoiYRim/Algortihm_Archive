#include <iostream>
#include <vector>

using namespace std;

int N,M;
vector<vector<int>> result;
vector<int> visit;

void DFS(int depth,vector<int> v)
{
    if(depth >= M)
    {
        result.push_back(v);
        return;
    }
    
    for(int i = 1; i <= N; i++)
    {
        if(!visit[i])
        {
            v.push_back(i);
            visit[i] = 1;
            DFS(depth+1,v);
            v.pop_back();
            visit[i] = 0;
        }
    }
}

int main()
{
    cin >> N >> M;
    
    vector<int> v;
    visit = vector<int>(N+1,0);
    DFS(0,v);
    
    for(int i = 0; i < (int)result.size(); i++)
    {
        for(int j = 0; j < (int)result[i].size(); j++)
            cout << result[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
