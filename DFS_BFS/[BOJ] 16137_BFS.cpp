#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> map;
vector<pair<int, int>> pos;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0 ,-1};

inline bool range(int y, int x) { return ((y >= 0 && y < N) && (x >= 0 && x < N)); }

void print()
{
    printf("MAP\n");
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            printf("%2d ", map[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void input()
{
    cin >> N >> M;
    map = vector<vector<int>>(N, vector<int>(N, 0));
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            cin >> map[y][x];
        }
    }
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            if(map[y][x] == 0)
            {
                bool h = false, w = false;
                
                for(int i = 0; i < 4; i++)
                {
                    int ny = y+dy[i];
                    int nx = x+dx[i];
                    
                    if(!range(ny, nx)) continue;
                    if(map[ny][nx] == 1) continue;
                    if(i % 2 == 0) h = true;
                    else w = true;
                }
                if(h && w) map[y][x] = -1;
                if(map[y][x] == 0) pos.push_back({y, x});
            }
        }
    }
    
    //print();
}

int solve(int result)
{
    vector<vector<int>> visit(N, vector<int>(N, 0x7fffffff));
    queue<pair<pair<int, int>, pair<int, int>>> q;
    
    q.push({{0, 0}, {0, 0}});
    visit[0][0] = 0;
    while(!q.empty())
    {
        int t = q.front().first.first;
        int d = q.front().first.second;
        int y = q.front().second.first;
        int x = q.front().second.second;
        q.pop();
        
        if(t >= result) break;
        
        if(y == N-1 && x == N-1)
        {
            //print();
            return t;
        }
        
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny, nx)) continue;
            if(map[ny][nx] == -1) continue;
            if(map[ny][nx] == 0) continue;
            if(map[ny][nx] > 1)
            {
                if(d < 1)
                {
                    if(visit[ny][nx] <= t+1) continue;
                        
                    if((t+1)%map[ny][nx] != 0)
                    {
                        visit[y][x]++;
                        q.push({{t+1, 0}, {y, x}});
                        continue;
                    }
                        
                    visit[ny][nx] = t+1;
                    q.push({{t+1, 1}, {ny, nx}});
                    continue;
                }
                else continue;
            }
            
            if(visit[ny][nx] <= t+1) continue;
            
            visit[ny][nx] = t+1;
            q.push({{t+1, 0}, {ny, nx}});
        }
    }
    
    return 0x7fffffff;
}

int main(int argc, char* argv[])
{
    int result = 0x7fffffff;
    
    input();
    if(pos.size() == 0)
        result = solve(result);
    for(int i = 0; i < pos.size(); i++)
    {
        map[pos[i].first][pos[i].second] = M;
        result = min(result, solve(result));
        map[pos[i].first][pos[i].second] = 0;
    }
    
    cout << result << endl;
    return 0;
}
