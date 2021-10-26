#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Status
{
    int y;
    int x;
    int day;
};

int N,M;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
int box[1024][1024] = {0,};
queue<Status> q;

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

int main(void)
{
    int none = 0;
    
    cin >> M >> N;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            cin >> box[y][x];
            if(box[y][x] > 0)
                q.push({y,x,0});
            if(!box[y][x])
                none++;
        }
    }
    
    if(!none)
    {
        cout << 0 << '\n';
        return 0;
    }
    
    while(!q.empty())
    {
        Status cur = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int ny = cur.y+dy[i];
            int nx = cur.x+dx[i];
            
            if(range(ny,nx) && box[ny][nx] == 0)
            {
                box[ny][nx] = 1;
                q.push({ny,nx,cur.day+1});
                none--;
                
                if(!none)
                {
                    cout << cur.day+1 << '\n';
                    return 0;
                }
            }
        }
    }
    
    cout << -1 << '\n';
    return 0;
}
