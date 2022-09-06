#include <set>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int M, N;
vector<vector<int>> map;
vector<vector<bool>> visit;
const int dy[4] = {0, -1, 0, 1};
const int dx[4] = {-1, 0, 1, 0};

inline bool range(int y, int x) { return ((y >= 0 && y < N) && (x >= 0 && x < M)); }

bool movable(int room, int dir)
{
    if(!(room & (1 << dir)))
        return true;
    return false;
}

void input()
{
    cin >> M >> N;
    map = vector<vector<int>>(N, vector<int>(M, 0));
    visit = vector<vector<bool>>(N, vector<bool>(M, 0));
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
            cin >> map[y][x];
    }
}

void solve(vector<vector<int>>& rooms, int& rm, int& mcnt, int& result)
{
    vector<int> sizes;

    rm = 0;
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            if(visit[y][x]) continue;
            
            visit[y][x] = true;
            
            int cnt = 0;
            queue<pair<int, int>> q;
            q.push({y, x});
            
            while(!q.empty())
            {

                int cy = q.front().first;
                int cx = q.front().second;
                rooms[cy][cx] = rm;
                cnt++;
                q.pop();
                
                for(int i = 0; i < 4; i++)
                {
                    int ny = cy+dy[i];
                    int nx = cx+dx[i];
                    
                    if(!range(ny, nx)) continue;
                    if(visit[ny][nx]) continue;
                    if(!movable(map[cy][cx], i)) continue;
                    
                    q.push({ny, nx});
                    visit[ny][nx] = true;
                }
            }
            
            rm++;
            sizes.push_back(cnt);
            mcnt = max(mcnt, cnt);
        }
    }
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            int idx = rooms[y][x];
            int cs = sizes[idx];
            
            for(int i = 0; i < 4; i++)
            {
                int ny = y+dy[i];
                int nx = x+dx[i];
                
                if(!range(ny, nx)) continue;
                if(rooms[ny][nx] == idx) continue;
                if(result >= cs+sizes[rooms[ny][nx]]) continue;
                
                result = cs+sizes[rooms[ny][nx]];
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int rm, max_size = 0, result = 0;
    
    input();
    
    vector<vector<int>> rooms(N, vector<int>(M, 0));
    
    solve(rooms, rm, max_size, result);
    
    std::cout << rm << std::endl;
    std::cout << max_size << std::endl;
    std::cout << result << std::endl;
    return 0;
}
