#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int N,M;
vector<int> num;
map<vector<int>,bool> m;

void DFS(int depth,vector<int> v)
{
    if(depth >= M)
    {
        if(m.find(v) != m.end())
            return;
        
        m.insert({v,true});
        for(int i = 0; i < M; i++)
            cout << v[i] << ' ';
        cout << '\n';
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
    
    DFS(0,{});
    return 0;
}
