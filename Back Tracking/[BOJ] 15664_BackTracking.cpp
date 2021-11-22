#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int N,M;
vector<int> num;
vector<bool> visit;
map<vector<int>,bool> m;

void DFS(int idx,int depth,vector<int> v)
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
    
    for(int i = idx; i < (int)num.size(); i++)
    {
        if(!visit[i])
        {
            visit[i] = true;
            v.push_back(num[i]);
            DFS(i+1,depth+1,v);
            v.pop_back();
            visit[i] = false;
        }
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
    
    visit = vector<bool>(N+1,false);
    sort(num.begin(),num.end());
    
    DFS(0,0,{});
    return 0;
}
