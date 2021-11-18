#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N,M;
vector<vector<int>> result;

void DFS(int depth,vector<int> v)
{
    if(depth == M)
    {
        result.push_back(v);
        return;
    }
    
    for(int i = 1; i <= N; i++)
    {
        v.push_back(i);
        DFS(depth+1,v);
        v.pop_back();
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        vector<int> v = {i};
        DFS(1,v);
    }
    
    for(int i = 0; i < (int)result.size(); i++)
    {
        for(int j = 0; j < (int)result[i].size(); j++)
            cout << result[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
