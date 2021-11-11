#include <queue>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Pos
{
    int y;
    int x;
    int t;
};

const int kMax = 0x7fffffff;

int R,C;
vector<string> Map;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
queue<Pos> fire,q;
vector<vector<int>> visit;

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline bool range(int y,int x) { return ((0 <= y && y < R) && (0 <= x && x < C)); }

int main()
{
    int result = kMax;
    
    cin >> R >> C;
    visit = vector<vector<int>>(R+1,vector<int>(C+1,kMax));
    for(int y = 0; y < R; y++)
    {
        string tmp; cin >> tmp;
        for(int x = 0; x < C; x++)
        {
            if(tmp[x] == 'J')
            {
                q.push({y,x,0});
                visit[y][x] = 0;
                tmp[x] = '.';
            }
            else if(tmp[x] == 'F')
                fire.push({y,x,0});
        }
        Map.push_back(tmp);
    }
    
    while(!q.empty())
    {
        int ny,nx;
        Pos cur = q.front();
        q.pop();
        
        if(cur.t == fire.front().t)
        {
            queue<Pos> new_fire;
            while(!fire.empty())
            {
                Pos f = fire.front();
                fire.pop();
                
                for(int i = 0; i < 4; i++)
                {
                    ny = f.y+dy[i];
                    nx = f.x+dx[i];
                    
                    if(range(ny,nx) && Map[ny][nx] == '.')
                    {
                        new_fire.push({ny,nx,f.t+1});
                        Map[ny][nx] = 'F';
                    }
                }
            }
            
            fire = new_fire;
        }
        
        for(int i = 0; i < 4; i++)
        {
            ny = cur.y+dy[i];
            nx = cur.x+dx[i];
            
            if(!range(ny,nx))
                result = MIN(result,cur.t+1);
            
            if(range(ny,nx) && Map[ny][nx] == '.')
            {
                if(visit[ny][nx] > cur.t+1)
                {
                    visit[ny][nx] = cur.t+1;
                    q.push({ny,nx,cur.t+1});
                }
            }
        }
    }
    
    if(result != kMax)
        cout << result << '\n';
    else
        cout << "IMPOSSIBLE" << '\n';
    return 0;
}
