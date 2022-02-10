#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
int map[128][128];
bool visit[128][128];
vector<pair<int,int>> coasts;

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < N)); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> map[i][j];
        }
    }
    
    int land = 2;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(map[i][j] == 1)
            {
                // 대륙들 구분해주기
                queue<pair<int,int>> q;
                
                q.push({i,j});
                map[i][j] = land;
                while(!q.empty())
                {
                    int y = q.front().first;
                    int x = q.front().second;
                    q.pop();
                    
                    for(int k = 0; k < 4; k++)
                    {
                        int ny = y+dy[k];
                        int nx = x+dx[k];
                        
                        if(!range(ny,nx))
                            continue;
                        if(!map[ny][nx] || map[ny][nx] == land)
                            continue;
                        
                        map[ny][nx] = land;
                        q.push({ny,nx});
                    }
                }
                
                land++;
                continue;
            }
            
            // 대륙에 접해있는 해안선들 위치 저장
            bool check = false;
            for(int k = 0; k < 4; k++)
            {
                int ny = i+dy[k];
                int nx = j+dx[k];
                
                if(!range(ny,nx))
                    continue;
                if(map[ny][nx])
                {
                    check = true;
                    break;
                }
            }
            if(check)
                coasts.push_back({i,j});
        }
    }
}

void debug()
{
    cout << "MAP" << endl;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            cout << map[y][x] << " ";
        }
        cout << endl;
    }
}

int solve()
{
    int result = 0x7fffffff;
    
    //debug();
    
    for(auto& coast : coasts)
    {
        memset((bool *)visit,0,sizeof(visit));
        
        int y = coast.first;
        int x = coast.second;
        int land = 0;
        queue<pair<pair<int,int>,int>> q;
        
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny,nx))
                continue;
            if(map[ny][nx] > 0)
            {
                land = map[ny][nx];
                break;
            }
        }

        q.push({{y,x},1});
        visit[y][x] = 1;
        while(!q.empty())
        {
            int cy = q.front().first.first;
            int cx = q.front().first.second;
            int cnt = q.front().second;
            q.pop();
            
            if(cnt > result)
                break;
            
            bool complete = false;
            for(int i = 0; i < 4; i++)
            {
                int ny = cy+dy[i];
                int nx = cx+dx[i];
                
                if(!range(ny,nx))
                    continue;
                if(visit[ny][nx])
                    continue;
                if(map[ny][nx] > 0)
                {
                    if(map[ny][nx] == land)
                        continue;
                    else
                    {
                        result = min(result,cnt);
                        complete = true;
                        break;
                    }
                }
                
                visit[ny][nx] = 1;
                q.push({{ny,nx},cnt+1});
            }
            if(complete)
                break;
        }
        
    }
    
    return result;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
