#include <iostream>

using namespace std;

int N,ans = 0;
bool Map[16][16] = {0,};
int dy[8] = {-1,-2,-2,-1,1,2,2,1};
int dx[8] = {-2,-1,1,2,2,1,-1,-2};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < N)); }

void check(int y,int x,bool b)
{
    for(int i = 0; i < 8; i++)
    {
        int ny = y+dy[i];
        int nx = x+dx[i];
        
        if(range(ny,nx))
            Map[ny][nx] = b;
    }
}

void DFS(int depth,int cnt)
{
    if(depth >= N*N)
    {
        if(cnt == N)
            ans++;
        return;
    }
    
    int y = depth/N;
    int x = depth%N;
    
    if(Map[y][x])
    {
        DFS(depth+1,cnt);
        return;
    }
    
    Map[y][x] = true;
    check(y,x,true);
    DFS(depth+1,cnt+1);
    check(y,x,false);
    Map[y][x] = false;
}

int main()
{
    cin >> N;
    DFS(0,0);
    cout << ans << '\n';
    return 0;
}
