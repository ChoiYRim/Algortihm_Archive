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
    int bit;
    int dep;
};

int N, M, cnt, sy, sx;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

vector<string> map;

inline bool range(int y, int x) { return ((y >= 0 && y < N) && (x >= 0 && x < M)); }

void input()
{
    cnt = 0;
    cin >> M >> N;
    for(int y = 0; y < N; y++)
    {
        string tmp; cin >> tmp;
        for(int x = 0; x < M; x++)
        {
            if(tmp[x] == 'S')
            {
                sy = y;
                sx = x;
            }
            else if(tmp[x] == 'X')
            {
                tmp[x] = (cnt++)+'0';
            }
        }
        map.push_back(tmp);
    }
    
    cnt = (1 << cnt) - 1;
}

void solve()
{
    queue<Node> q;
    vector<vector<vector<int>>> visit(cnt+1, vector<vector<int>>(N, vector<int>(M, 0)));
    
    visit[0][sy][sx] = 1;
    q.push({sy, sx, 0, 0});
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int bit = q.front().bit;
        int dep = q.front().dep;
        q.pop();
        
        if(map[y][x] == 'E' && bit == cnt)
        {
            cout << dep << endl;
            return;
        }
        
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            int nb = bit;
            
            if(!range(ny, nx)) continue;
            if(map[ny][nx] == '#') continue;
            if(map[ny][nx] != '.' && map[ny][nx] != 'E' && map[ny][nx] != 'S')
            {
                nb = bit | (1 << (map[ny][nx]-'0'));
                
                if(visit[nb][ny][nx]) continue;
                
                visit[nb][ny][nx] = 1;
                q.push({ny, nx, nb, dep+1});
            }
            else
            {
                if(visit[nb][ny][nx]) continue;
                
                visit[nb][ny][nx] = 1;
                q.push({ny, nx, nb, dep+1});
            }
        }
    }
}

int main(int argc, char* argv[])
{
    input();
    solve();
    return 0;
}
