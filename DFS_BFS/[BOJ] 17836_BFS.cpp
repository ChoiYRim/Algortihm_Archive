#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int y;
    int x;
    int t;
    int g;
};

int T, N, M;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
vector<vector<int>> map;
vector<vector<vector<int>>> visit;

inline bool range(int y, int x) { return ((y >= 1 && y <= N) && (x >= 1 && x <= M)); }

void input()
{
    cin >> N >> M >> T;
    
    map = vector<vector<int>>(N+1, vector<int>(M+1, 0));
    visit = vector<vector<vector<int>>>(2, vector<vector<int>>(N+1, vector<int>(M+1, 0x7fffffff)));
    
    for(int y = 1; y <= N; y++)
    {
        for(int x = 1; x <= M; x++)
        {
            cin >> map[y][x];
        }
    }
}

string solve()
{
    queue<Node> q;

    visit[0][1][1] = 0;
    q.push({1, 1, 0, 0});
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int t = q.front().t;
        int g = q.front().g;
        q.pop();
        
        if(t > T) continue;
        if(y == N && x == M) return to_string(t);
        
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny, nx)) continue;
            if(map[ny][nx] == 1 && !g) continue;
            
            if(map[ny][nx] == 2)
            {
                if(visit[1][ny][nx] <= t+1) continue;
                
                visit[1][ny][nx] = t+1;
                q.push({ny, nx, t+1, 1});
            }
            else
            {
                if(visit[g][ny][nx] <= t+1) continue;
                
                visit[g][ny][nx] = t+1;
                q.push({ny, nx, t+1, g});
            }
        }
    }
    
    return "Fail";
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
