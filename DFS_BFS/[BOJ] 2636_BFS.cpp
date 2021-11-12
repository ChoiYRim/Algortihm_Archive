#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct Pos
{
    int y;
    int x;
};

int R,C;
int Map[128][128] = {0,};
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
queue<Pos> cheese;

inline bool range(int y,int x) { return ((0 <= y && y < R) && (0 <= x && x < C)); }

void input()
{
    cin >> R >> C;
    for(int y = 0; y < R; y++)
    {
        for(int x = 0; x < C; x++)
        {
            cin >> Map[y][x];
            if(Map[y][x])
                cheese.push({y,x});
        }
    }
}

bool check(int y,int x,bool (*visit)[128])
{
    // true : 치즈 안 녹음 , false : 치즈 녹음
    queue<Pos> q;
    vector<Pos> tmp = {{y,x}};
    
    q.push({y,x});
    visit[y][x] = true;
    while(!q.empty())
    {
        Pos cur = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int ny = cur.y+dy[i];
            int nx = cur.x+dx[i];
            
            if(!range(ny,nx))
            {
                for(int j = 0; j < (int)tmp.size(); j++)
                    visit[tmp[j].y][tmp[j].x] = false;
                return false;
            }
            if(range(ny,nx) && !Map[ny][nx] && !visit[ny][nx])
            {
                visit[ny][nx] = true;
                q.push({ny,nx});
                tmp.push_back({ny,nx});
            }
        }
    }
    
    return true;
}

int main()
{
    int t,num = 0;
    
    input();
    
    for(t = 0; cheese.size() > 0; t++)
    {
        bool visit[128][128] = {0,};
        queue<Pos> new_cheese;
        vector<Pos> air;
        
        num = (int)cheese.size();
        while(!cheese.empty())
        {
            Pos cz = cheese.front();
            cheese.pop();
            
            bool can_remove = false;
            for(int i = 0; i < 4; i++)
            {
                int ny = cz.y+dy[i];
                int nx = cz.x+dx[i];
                
                if(range(ny,nx))
                {
                    if(!Map[ny][nx] && !visit[ny][nx])
                    {
                        if(!check(ny,nx,visit))
                        {
                            can_remove = true;
                            break;
                        }
                    }
                }
            }
            if(!can_remove)
                new_cheese.push(cz);
            else
                air.push_back(cz);
        }
        
        for(int i = 0; i < (int)air.size(); i++)
            Map[air[i].y][air[i].x] = 0;
        cheese = new_cheese;
    }
    
    cout << t << "\n";
    cout << num << "\n";
    return 0;
}
