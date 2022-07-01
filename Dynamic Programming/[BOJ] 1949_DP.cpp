#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int MAX = 10001;

int N;
int dp[2][MAX];
int towns[MAX];
bool visit[MAX];
vector<vector<int>> edges;

void input()
{
    cin >> N;
    edges = vector<vector<int>>(N);
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        towns[i] = tmp;
    }
    for(int i = 0; i < N-1; i++)
    {
        int u, v; cin >> u >> v;
        edges[u-1].push_back(v-1);
        edges[v-1].push_back(u-1);
    }
}

void solve(int cur)
{
    visit[cur] = 1;
    dp[0][cur] = 0; // 현재 마을(cur)이 일반마을
    dp[1][cur] = towns[cur]; // 현재 마을(cur)이 우수마을
    
    for(const auto& next : edges[cur])
    {
        if(visit[next]) continue;
        
        solve(next);
        
        dp[0][cur] += max(dp[0][next], dp[1][next]);
        dp[1][cur] += dp[0][next];
    }
}

int main(int argc, char* argv[])
{
    input();
    solve(0);
    cout << max(dp[0][0], dp[1][0]) << endl;
    return 0;
}
