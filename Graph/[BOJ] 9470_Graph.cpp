#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int T, K, M, P;
vector<int> nodes;
vector<vector<int>> rivers;
vector<pair<int, int>> depth;

void input()
{
    cin >> K >> M >> P;
    rivers = vector<vector<int>>(M+1);
    nodes = vector<int>(M+1, 0);
    depth = vector<pair<int, int>>(M+1,{0, 0});
    for(int i = 0; i < P; i++)
    {
        int from, to; cin >> from >> to;
        rivers[from].push_back(to);
        nodes[to]++; // to점으로 들어오는 간선의 수
    }
}

int solve()
{
    queue<int> q;
    
    // 시작부분 모두 체크
    for(int i = 1; i <= M; i++)
    {
        if(nodes[i] != 0) continue;
        
        q.push(i);
        depth[i] = {1, 1};
    }
    
    // BFS
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        
        for(const int next : rivers[cur])
        {
            if(depth[next].first < depth[cur].first)
                depth[next] = make_pair(depth[cur].first, 1);
            else if(depth[next].first == depth[cur].first)
                depth[next].second++;

            nodes[next]--;
            if(nodes[next] == 0)
            {
                if(depth[next].second > 1) depth[next] = make_pair(depth[next].first+1, 1);
                q.push(next);
            }
        }
    }
    
    return depth[M].first;
}

void output(const vector<pair<int, int>>& results)
{
    for(const auto& result : results)
        cout << result.first << " " << result.second << endl;
}

int main(int argc, char* argv[])
{
    vector<pair<int, int>> results;
    
    cin >> T;
    while(T--)
    {
        input();
        int result = solve();
        results.push_back({K, result});
    }
    output(results);
    return 0;
}
