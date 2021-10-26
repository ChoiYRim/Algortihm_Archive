#include <queue>
#include <iostream>

using namespace std;

struct Status
{
    int z;
    int y;
    int x;
    int day;
};

int dz[3] = {-1,0,1};
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
int box[128][128][128] = {0,};
int H,N,M;
queue<Status> q;

inline bool range(int z,int y,int x) { return ((0 <= z && z < H) && (0 <= y && y < N) && (0 <= x && x < M)); }

int main(void)
{
    int none = 0;
    
    cin >> M >> N >> H;
    for(int z = 0; z < H; z++)
    {
        for(int y = 0; y < N; y++)
        {
            for(int x = 0; x < M; x++)
            {
                cin >> box[z][y][x];
                if(box[z][y][x] == 1)
                    q.push({z,y,x,0});
                else if(box[z][y][x] == 0)
                    none++;
            }
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
                
        for(int i = 0; i < 3; i++)
        {
            int nz = cur.z+dz[i];
            for(int j = 0; j < 4; j++)
            {
                int ny = cur.y,nx = cur.x;
                
                if(dz[i] == 0)
                {
                    ny += dy[j];
                    nx += dx[j];
                }
                
                if(range(nz,ny,nx) && box[nz][ny][nx] == 0)
                {
                    box[nz][ny][nx] = 1;
                    q.push({nz,ny,nx,cur.day+1});
                    none--;
                    
                    if(!none)
                    {
                        cout << cur.day+1 << '\n';
                        return 0;
                    }
                }
            }
        }
    }
    
    cout << -1 << '\n';
    return 0;
}
