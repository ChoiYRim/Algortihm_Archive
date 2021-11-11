#include <queue>
#include <vector>
#include <iostream>

using namespace std;

const int kMax = 0x7fffffff;

struct Pos
{
    int y;
    int x;
    int d;
    int cnt;
};

int M,N;
int dy[5] = {0,0,0,1,-1};
int dx[5] = {0,1,-1,0,0};
bool Map[128][128] = {0,};
vector<vector<vector<int>>> visit;
Pos start,dst;
queue<Pos> q;

inline bool range(int y,int x) { return ((0 < y && y <= M) && (0 < x && x <= N)); }

inline int MIN(int a,int b) { return (a > b ? b : a); }

int direction(int cur,int next)
{
    if(cur == next)
        return 0;
    if(cur == 1)
    {
        if(next == 2)
            return 2;
        return 1;
    }
    else if(cur == 2)
    {
        if(next == 1)
            return 2;
        return 1;
    }
    else if(cur == 3)
    {
        if(next == 4)
            return 2;
        return 1;
    }
    
    if(next == 3)
        return 2;
    return 1;
}

int main()
{
    int result = kMax;
    
    cin >> M >> N;
    for(int y = 1; y <= M; y++)
    {
        for(int x = 1; x <= N; x++)
            cin >> Map[y][x];
    }
    cin >> start.y >> start.x >> start.d;
    cin >> dst.y >> dst.x >> dst.d;
    visit = vector<vector<vector<int>>>(5,vector<vector<int>>(M+1,vector<int>(N+1,kMax)));
    
    visit[start.d][start.y][start.x] = 0;
    q.push({start.y,start.x,start.d,0});
    while(!q.empty())
    {
        int turn;
        Pos cur = q.front();
        q.pop();
        
        if(cur.y == dst.y && cur.x == dst.x)
        {
            turn = direction(cur.d,dst.d);
            result = MIN(result,cur.cnt+turn);
            continue;
        }
        
        for(int dir = 1; dir <= 4; dir++)
        {
            turn = direction(cur.d,dir);
            
            for(int dist = 1; dist <= 3; dist++)
            {
                int ny = cur.y+dist*dy[dir];
                int nx = cur.x+dist*dx[dir];
                
                if(!range(ny,nx) || Map[ny][nx])
                    break;
                if(cur.cnt+turn+1 > visit[dir][ny][nx])
                    break;
                
                visit[dir][ny][nx] = cur.cnt+1+turn;
                q.push({ny,nx,dir,cur.cnt+1+turn});
            }
        }
    }
    
    cout << result << '\n';
    return 0;
}
