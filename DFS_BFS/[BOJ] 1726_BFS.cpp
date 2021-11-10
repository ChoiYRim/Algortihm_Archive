#include <queue>
#include <vector>
#include <iostream>

using namespace std;

const int kMax = 0x7fffffff;

struct Status
{
    int y; // row
    int x; // col
    int d; // dir
    int cnt;
};

int M,N;
bool Map[128][128] = {0,};
Status start,dst;
int dy[4] = {-1,0,0,1}; // north , east , west , south
int dx[4] = {0,1,-1,0}; // same with above
queue<Status> q;
vector<vector<int>> visit;

inline bool range(int y,int x) { return ((0 < y && y <= M) && (0 < x && x <= N)); }

inline int MIN(int a,int b) { return (a > b ? b : a); }

int direction(int cur,int next)
{
    if(cur == next)
        return 0;
    
    if(cur == 0)
    {
        if(next == 3)
            return 2;
        else
            return 1;
    }
    else if(cur == 1)
    {
        if(next == 2)
            return 2;
        else
            return 1;
    }
    else if(cur == 2)
    {
        if(next == 1)
            return 2;
        else
            return 1;
    }
    
    if(next == 0)
        return 2;
    else
        return 1;
}

void input()
{
    cin >> M >> N;
    for(int y = 1; y <= M; y++)
    {
        for(int x = 1; x <= N; x++)
        {
            cin >> Map[y][x];
        }
    }
    cin >> start.y >> start.x >> start.d;
    cin >> dst.y >> dst.x >> dst.d;
    
    start.d %= 4;
    dst.d %= 4;
    
    visit = vector<vector<int>>(M+1,vector<int>(N+1,kMax));
}

int main()
{
    int result = kMax;
    
    input();
    
    q.push({start.y,start.x,start.d,0});
    while(!q.empty())
    {
        int turn;
        Status cur = q.front();
        q.pop();
                
        if(cur.y == dst.y && cur.x == dst.x)
        {
            turn = direction(cur.d,dst.d);
            result = MIN(result,cur.cnt+turn);
            continue;
        }
        
        for(int dir = 0; dir < 4; dir++)
        {
            int mdist = 0;
            turn = direction(cur.d,dir);
            for(int dist = 1; dist <= 3; dist++)
            {
                int ny = cur.y+dist*dy[dir];
                int nx = cur.x+dist*dx[dir];
                
                if(!range(ny,nx) || Map[ny][nx] || visit[ny][nx] < cur.cnt+turn+1)
                    break;
                
                mdist = dist;
            }
            for(int dist = 1; dist <= mdist; dist++)
            {
                int ny = cur.y+dist*dy[dir];
                int nx = cur.x+dist*dx[dir];
                
                visit[ny][nx] = cur.cnt+turn+1;
                q.push({ny,nx,dir,cur.cnt+turn+1});
            }
        }
    }
    
    cout << result << '\n';
    return 0;
}
