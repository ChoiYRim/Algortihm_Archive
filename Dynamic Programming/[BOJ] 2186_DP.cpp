#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

string ans;
int N,M,K,res = 0;
vector<string> v;
int visit[81][101][101];

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

int dfs(int y,int x,int cnt)
{
    if(visit[cnt][y][x] != -1)
        return visit[cnt][y][x];
    
    if(cnt == (int)ans.length())
        return 1;
    
    visit[cnt][y][x] = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int k = 1; k <= K; k++)
        {
            int ny = y+dy[i]*k;
            int nx = x+dx[i]*k;
            
            if(!range(ny,nx))
                continue;
            
            if(ans[cnt] == v[ny][nx])
            {
                visit[cnt][y][x] += dfs(ny,nx,cnt+1);
            }
        }
    }
    
    return visit[cnt][y][x];
}

void input()
{
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++)
    {
        string tmp = ""; cin >> tmp;
        v.push_back(tmp);
    }
    cin >> ans;
    memset((int*)visit,-1,sizeof(visit));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    input();
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(v[i][j] == ans[0])
            {
                res += dfs(i,j,1);
            }
        }
    }
    
    cout << res << '\n';
    return 0;
}
