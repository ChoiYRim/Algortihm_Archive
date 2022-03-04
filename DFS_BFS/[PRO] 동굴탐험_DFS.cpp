#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

vector<bool> visit;
vector<vector<int>> v;
unordered_map<int,int> before;
unordered_map<int,int> after;

void dfs(int cur)
{
    // 현재 정점을 방문하기 위해 방문해야할 정점을 아직 방문하지 않았다면
    if(!visit[before[cur]])
    {
        after[before[cur]] = cur; // 예약 걸어두기
        return;
    }
    
    visit[cur] = true;
    if(after[cur] != 0) // cur 다음에 방문해야할 노드가 있었다면
        dfs(after[cur]);
    for(int i = 0; i < v[cur].size(); i++)
    {
        int next = v[cur][i];
        if(!visit[next])
            dfs(next);
    }
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order)
{
    v.resize(n);
    visit.resize(n);
    // 그래프 만들기
    for(const auto& ele : path)
    {
        int from = ele[0];
        int to = ele[1];
        
        v[from].push_back(to);
        v[to].push_back(from);
    }
    
    // to를 가기 위해선 from을 미리 방문해야 한다.
    for(const auto& ele : order)
    {
        int from = ele[0];
        int to = ele[1];
        
        before[to] = from;
    }
    
    if(before[0] != 0) // 0보다 전에 방문해야할 정점이 있으면 안됨
        return false;
    
    visit[0] = true;
    for(int i = 0; i < v[0].size(); i++)
        dfs(v[0][i]);
    
    for(int i = 0; i < n; i++)
    {
        if(!visit[i])
            return false;
    }
    
    return true;
}

int main(int argc,char* argv[])
{
    //cout << solution({{0,0,0},{0,0,0},{0,0,0}}) << endl;
    return 0;
}
