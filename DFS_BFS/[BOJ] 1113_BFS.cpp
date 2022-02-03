#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int N,M;
vector<vector<int>> map,water;
bool visit[64][64];
int max_height = 0;
int min_height = 0x7fffffff;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < M)); }

void input()
{
    cin >> N >> M;
    map = vector<vector<int>>(N,vector<int>(M,0));
    water = vector<vector<int>>(N,vector<int>(M,0));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            scanf("%1d", &map[i][j]);
            
            if(max_height < map[i][j])
                max_height = map[i][j];
            if(min_height > map[i][j])
                min_height = map[i][j];
        }
    }
}

void bfs(int y,int x,int height)
{
    queue<pair<int,int>> q;
    
    q.push({y,x});
    visit[y][x] = true;
    while(!q.empty())
    {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        
        water[cy][cx]--;
        for(int i = 0; i < 4; i++)
        {
            int ny = cy+dy[i];
            int nx = cx+dx[i];
            
            if(!range(ny,nx))
                continue;
            if(visit[ny][nx])
                continue;
            
            if(map[ny][nx]+water[ny][nx] == height && water[ny][nx] > 0)
            {
                q.push({ny,nx});
                visit[ny][nx] = true;
            }
        }
    }
}

int solve()
{
    int ret = 0;
    
    for(int y = 1; y < N-1; y++)
    {
        for(int x = 1; x < M-1; x++)
            water[y][x] = max_height-map[y][x];
    }
    
    for(int height = max_height; height > min_height; height--)
    {
        memset((bool*)visit,0,sizeof(visit));
        
        for(int y = 1; y < N-1; y++)
        {
            for(int x = 1; x < M-1; x++)
            {
                if(water[y][x] > 0 && !visit[y][x])
                {
                    for(int i = 0; i < 4; i++)
                    {
                        int ny = y+dy[i];
                        int nx = x+dx[i];
                        
                        // 옆칸보다 현재 칸에 차 있는 물의 높이가 더 높은 경우 -> 흘러내림
                        if(map[ny][nx]+water[ny][nx] < map[y][x]+water[y][x])
                        {
                            bfs(y,x,height);
                            break;
                        }
                    }
                }
            }
        }
    }
    
    for(int y = 1; y < N-1; y++)
        for(int x = 1; x < M-1; x++)
            ret += water[y][x];
    
    return ret;
}

int main()
{
    input();
    
    printf("%d\n", solve());
    return 0;
}
