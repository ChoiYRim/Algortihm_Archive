#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N,M;
vector<int> num;
vector<vector<int>> result;

void DFS(int depth,vector<int> v)
{
    if(depth >= M)
    {
        result.push_back(v);
        return;
    }
    
    for(int i = 0; i < (int)num.size(); i++)
    {
        v.push_back(num[i]);
        DFS(depth+1,v);
        v.pop_back();
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        num.push_back(tmp);
    }
    
    sort(num.begin(),num.end());
    
    vector<int> v;
    DFS(0,v);
    
    for(int i = 0; i < (int)result.size(); i++)
    {
        for(int j = 0; j < (int)result[i].size(); j++)
            cout << result[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
