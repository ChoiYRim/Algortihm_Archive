#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int R, C;
vector<string> v, visit;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

inline bool range(int y, int x) { return ((y >= 0 && y < R) && (x >= 0 && x < C)); }

void input()
{
    cin >> R >> C;
    for(int y = 0; y < R; y++)
    {
        string tmp; cin >> tmp;
        v.push_back(move(tmp));
    }
    
    visit = vector<string>(R, string(C, '0'));
}

bool solve(int depth, int sy, int sx, int cy, int cx)
{
    if(depth >= 4)
    {
        for(int i = 0; i < 4; i++)
        {
            int ny = cy+dy[i];
            int nx = cx+dx[i];
            
            if(!range(ny, nx)) continue;
            if(ny == sy && nx == sx) return true;
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        int ny = cy+dy[i];
        int nx = cx+dx[i];
        
        if(!range(ny, nx)) continue;
        if(v[sy][sx] != v[ny][nx]) continue;
        if(visit[ny][nx] != '0') continue;
        
        visit[ny][nx] = '1';
        if(solve(depth+1, sy, sx, ny, nx)) return true;
        visit[ny][nx] = '0';
    }
    
    return false;
}

int main(int argc, char* argv[])
{
    input();
    for(int y = 0; y < R; y++)
    {
        for(int x = 0; x < C; x++)
        {
            visit[y][x] = '1';
            if(solve(1, y, x, y, x))
            {
                printf("Yes\n");
                return 0;
            }
            visit[y][x] = '0';
        }
    }
    
    printf("No\n");
    return 0;
}
