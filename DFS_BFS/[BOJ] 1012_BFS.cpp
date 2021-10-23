#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct Pos
{
    int y;
    int x;
};

int T;
int N,M,K;
int Map[64][64] = {0,};
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

int check(vector<Pos> v)
{
    for(int i = 0; i < (int)v.size(); i++)
    {
        int y = v[i].y,x = v[i].x;
        
        if(Map[y][x] == 1)
            return i;
    }
    
    return -1;
}

int main(void)
{
    cin >> T;
    while(T--)
    {
        memset((int *)Map,0,sizeof(Map));
        queue<Pos> q;
        int idx,ans = 0;
        vector<Pos> v;
        
        cin >> M >> N >> K;
        for(int i = 0; i < K; i++)
        {
            int x,y; cin >> x >> y;
            Map[y][x] = 1;
            v.push_back({y,x});
        }
        
        while((idx = check(v)) != -1)
        {
            ans++;
            Map[v[idx].y][v[idx].x] = 2;
            q.push({v[idx].y,v[idx].x});
            while(!q.empty())
            {
                Pos cur = q.front();
                q.pop();
                
                int y = cur.y,x = cur.x;
                
                for(int i = 0; i < 4; i++)
                {
                    int ny = y+dy[i];
                    int nx = x+dx[i];
                    
                    if(range(ny,nx) && Map[ny][nx] == 1)
                    {
                        Map[ny][nx] = 2;
                        q.push({ny,nx});
                    }
                }
            }
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
