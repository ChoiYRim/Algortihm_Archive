#include <map>
#include <string>
#include <iostream>

using namespace std;

int result = 0;
int board[8][8] = {0,};
int dy[5] = {-1,0,1,0};
int dx[5] = {0,1,0,-1};
map<string,bool> m;

inline bool range(int y,int x) { return ((0 <= y && y < 5) && (0 <= x && x < 5)); }

void DFS(int y,int x,int depth,string cur)
{
    if(depth >= 5)
    {
        auto it = m.find(cur);
        
        if(it != m.end())
            return;
        
        result++;
        m.insert({cur,true});
        return;
    }
    
    for(int i = 0; i < 4; i++)
    {
        int ny = y+dy[i];
        int nx = x+dx[i];
        
        if(range(ny,nx))
        {
            cur += to_string(board[ny][nx]);
            DFS(ny,nx,depth+1,cur);
            cur.pop_back();
        }
    }
}

int main()
{
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 5; x++)
            cin >> board[y][x];
    }
    
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 5; x++)
        {
            string cur = to_string(board[y][x]);
            DFS(y,x,0,cur);
        }
    }
    
    cout << result << '\n';
    return 0;
}
