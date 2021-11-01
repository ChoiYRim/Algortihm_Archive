#include <vector>
#include <string>
#include <iostream>

using namespace std;

int R,C;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
vector<string> Map;
vector<vector<bool>> visit;
int wolf,sheep;

inline bool range(int y,int x) { return ((0 <= y && y < R) && (0 <= x && x < C)); }

void DFS(int& w,int& s,int y,int x)
{
    for(int i = 0; i < 4; i++)
    {
        int ny = y+dy[i];
        int nx = x+dx[i];
        
        if(range(ny,nx) && Map[ny][nx] != '#' && !visit[ny][nx])
        {
            visit[ny][nx] = true;
            
            if(Map[ny][nx] == 'v')
                DFS(++w,s,ny,nx);
            else if(Map[ny][nx] == 'o')
                DFS(w,++s,ny,nx);
            else
                DFS(w,s,ny,nx);
        }
    }
}

int main()
{
    wolf = sheep = 0;
    
    cin >> R >> C;
    for(int i = 0; i < R; i++)
    {
        string tmp = ""; cin >> tmp;
        Map.push_back(tmp);
    }
    visit = vector<vector<bool>>(R,vector<bool>(C,false));
    
    for(int y = 0; y < R; y++)
    {
        for(int x = 0; x < C; x++)
        {
            if(visit[y][x] || Map[y][x] == '#')
                continue;
                
            int w = 0,s = 0;
            visit[y][x] = true;
            
            if(Map[y][x] == '.')
                DFS(w,s,y,x);
            else if(Map[y][x] == 'o')
                DFS(w,++s,y,x);
            else if(Map[y][x] == 'v')
                DFS(++w,s,y,x);
            
            if(w >= s)
                wolf += w;
            else
                sheep += s;
        }
    }
    
    cout << sheep << " " << wolf << '\n';
    return 0;
}
