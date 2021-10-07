#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define IN(y,x,R,C) ((0 <= y && y < R) && (0 <= x && x < C))

struct Pos
{
    int y;
    int x;
    int t; // time
};

int R,C;
int dy[] = {-1,0,1,0};
int dx[] = {0,1,0,-1};
std::queue<Pos> q;
std::vector<Pos> water;
std::vector<std::string> v;
bool visit[51][51] = {0,};

int main(int argc,char* argv[])
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
        
    std::cin >> R >> C;
    for(int i = 0; i < R; i++)
    {
        std::string str; std::cin >> str;
        for(int j = 0; j < C; j++)
        {
            if(str[j] == '*')
                water.push_back({i,j,0});
            else if(str[j] == 'S')
                q.push({i,j,0});
        }
        v.push_back(str);
    }
    
    visit[q.front().y][q.front().x] = true;
    while(!q.empty())
    {
        Pos hedgeHog = q.front();
        q.pop();
        
        std::vector<Pos> nextW;
        
        if(water.size() > 0 && water[water.size()-1].t == hedgeHog.t)
        {
            for(int i = 0; i < (int)water.size(); i++)
            {
                if(water[i].t < hedgeHog.t || water[i].t > hedgeHog.t)
                    continue;
                
                int y = water[i].y,x = water[i].x,t = water[i].t;
                
                for(int j = 0; j < 4; j++)
                {
                    int ny = y+dy[j];
                    int nx = x+dx[j];
                    
                    if(IN(ny,nx,R,C))
                    {
                        if(v[ny][nx] == '.' || v[ny][nx] == 'S')
                        {
                            v[ny][nx] = '*';
                            nextW.push_back({ny,nx,t+1});
                        }
                    }
                }
            }
            water.insert(water.end(),nextW.begin(),nextW.end());
        }
        
        int hy = hedgeHog.y,hx = hedgeHog.x,ht = hedgeHog.t;
        
        for(int i = 0; i < 4; i++)
        {
            int ny = hy+dy[i];
            int nx = hx+dx[i];
            
            if(IN(ny,nx,R,C) && !visit[ny][nx])
            {
                if(v[ny][nx] == 'D')
                {
                    std::cout << ht+1 << '\n';
                    return 0;
                }
                
                if(v[ny][nx] == '.' || v[ny][nx] == 'S')
                {
                    visit[ny][nx] = true;
                    q.push({ny,nx,ht+1});
                }
            }
        }
    }
    
    std::cout << "KAKTUS" << '\n';
    return 0;
}
