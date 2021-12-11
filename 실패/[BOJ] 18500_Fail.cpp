#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Pos
{
    int y;
    int x;
    
    bool operator==(const Pos& p)
    {
        if(y != p.y)
            return false;
        if(x != p.x)
            return false;
        return true;
    }
};

struct Cluster
{
    int ny,sy; // north y , south y
    int lx,rx; // west  x , east  x
    vector<Pos> mineral;
    
    Cluster() { }
    
    Cluster(const Cluster& c)
    {
        *this = c;
    }
    
    Cluster(int ny_,int sy_,int lx_,int rx_,vector<Pos> mineral_) : ny(ny_), sy(sy_), lx(lx_), rx(rx_)
    {
        mineral.insert(mineral.end(), mineral_.begin(), mineral_.end());
    }
    
    bool operator=(const Cluster& c)
    {
        ny = c.ny; sy = c.sy; lx = c.lx; rx = c.rx;
        for(int i = 0; i < c.mineral.size(); i++)
            mineral.push_back(c.mineral[i]);
        return true;
    }
    
    bool operator==(const Cluster& c)
    {
        if(ny != c.ny || sy != c.sy || lx != c.lx || rx != c.rx)
            return false;
        if(mineral.size() != c.mineral.size())
            return false;
        
        for(int i = 0; i < (int)mineral.size(); i++)
        {
            if(mineral[i] == c.mineral[i])
                continue;
            return false;
        }
        
        return true;
    }
};

int R,C;
int cave[128][128] = {0,};
bool visit[128][128] = {0,};
int N;
vector<int> height;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
vector<Cluster> v;

inline bool range(int y,int x) { return ((0 <= y && y < R) && (0 <= x && x < C)); }

inline bool comp_pos(const Pos& p1,const Pos& p2) { return (p1.y == p2.y ? p1.x < p2.x : p1.y < p2.y); }

inline bool comp_cluster(const Cluster& c1,const Cluster& c2) { return (c1.sy == c2.sy ? c1.lx < c2.lx : c1.sy < c2.sy); }

void print()
{
    for(int y = 0; y < R; y++)
    {
        for(int x = 0; x < C; x++)
            cout << cave[y][x];
        cout << '\n';
    }
}

void input()
{
    cin >> R >> C;
    for(int i = R-1; i >= 0; i--)
    {
        string tmp = ""; cin >> tmp;
        for(int j = 0; j < (int)tmp.length(); j++)
        {
            if(tmp[j] != '.')
                cave[i][j] = 1;
            else
                cave[i][j] = 0;
        }
    }
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int h; cin >> h;
        height.push_back(h-1);
    }
    
    for(int y = 0; y < R; y++)
    {
        for(int x = 0; x < C; x++)
        {
            if(cave[y][x] != 0 && !visit[y][x])
            {
                int nY = y,sY = y,lX = x,rX = x;
                queue<Pos> q;
                q.push({y,x});
                visit[y][x] = true;
                vector<Pos> mineral = {{y,x}};
                
                while(!q.empty())
                {
                    Pos cur = q.front();
                    q.pop();
                    
                    for(int i = 0; i < 4; i++)
                    {
                        int ny = cur.y+dy[i];
                        int nx = cur.x+dx[i];
                        
                        if(range(ny,nx) && cave[ny][nx] != 0 && !visit[ny][nx])
                        {
                            nY = max(nY,ny);
                            sY = min(sY,ny);
                            lX = min(lX,nx);
                            rX = max(rX,nx);
                            
                            q.push({ny,nx});
                            visit[ny][nx] = true;
                            mineral.push_back({ny,nx});
                        }
                    }
                }
                
                sort(mineral.begin(),mineral.end(),comp_pos);
                
                Cluster c = {nY,sY,lX,rX,mineral};
                v.push_back(c);
            }
        }
    }
}

void solve(int turn)
{
    if(turn >= (int)height.size())
        return;
    
    int idx = -1,x = -1,idx_min = -1;
    int h = height[turn];
    
    if(turn % 2 != 0) // 오른쪽
    {
        // 박살날 클러스터 찾기
        for(int i = 0; i < (int)v.size(); i++)
        {
            Cluster cluster = v[i];
            
            if(h >= cluster.sy && h <= cluster.ny)
            {
                for(int j = 0; j < (int)cluster.mineral.size(); j++)
                {
                    Pos pos = cluster.mineral[j];
                    
                    if(pos.y == h && x <= pos.x)
                    {
                        x = pos.x;
                        idx = i;
                        idx_min = j;
                    }
                }
            }
        }
        
        if(idx == -1) // 파괴할 미네랄이 없음
        {
            solve(turn+1);
            return;
        }
        
        // idx번째 클러스터의 idx_min번째 미네랄 파괴
        Cluster& cluster = v[idx];
        
        cluster.mineral.erase(cluster.mineral.begin()+idx_min);
        
        
        // 둘로 쪼개졌는가? -> 클러스터 분리
    }
    else // 왼쪽
    {
    }
}

int main(int argc,char* argv[])
{
    input();
    
    solve(0);
    
    print();
    return 0;
}
