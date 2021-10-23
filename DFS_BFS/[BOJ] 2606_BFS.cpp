#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int N,M;
vector<int> computer[128];
bool visit[128] = {0,};
queue<int> q;

int main(void)
{
    int ans = 0;
    
    cin >> N;
    cin >> M;
    for(int i = 0; i < M; i++)
    {
        int a,b; cin >> a >> b;
        computer[a].push_back(b);
        computer[b].push_back(a);
    }
    
    q.push(1);
    visit[1] = true;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        
        for(int i = 0; i < (int)computer[cur].size(); i++)
        {
            int next = computer[cur][i];
            
            if(!visit[next])
            {
                visit[next] = true;
                ans += 1;
                q.push(next);
            }
        }
    }
    
    cout << ans << '\n';
    return 0;
}
