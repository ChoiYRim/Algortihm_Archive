#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int y;
    int x;
    int dir;
    int cnt;
};

vector<vector<int>> map;
int visit[4][128][128];
int dy[4] = {-1,0,1,0}; // 북 동 남 서
int dx[4] = {0,1,0,-1}; // "
int N;

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < N)); }

void print_robot(int y1,int x1,int y2,int x2,int cnt)
{
    printf("[%2d,%-2d] ", y1,x1);
    printf("[%2d,%-2d] ", y2,x2);
    printf("cnt = %2d\n", cnt);
}

void print_map()
{
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            printf("%2d ", map[y][x]);
        }
        printf("\n");
    }
}

int get_dir(int y1,int x1,int y2,int x2)
{
    if(y1 != y2)
    {
        if(y1 < y2)
            return 0;
        return 2;
    }
    
    if(x1 < x2)
        return 1;
    return 3;
}

int counter_dir(int dir)
{
    if(dir == 0)
        return 2;
    if(dir == 1)
        return 3;
    if(dir == 2)
        return 0;
    return 1;
}

inline int clock_wise(int dir)
{
    return (dir+1)%4;
}

inline int counter_clock_wise(int dir)
{
    return (dir-1 < 0 ? 3 : dir-1);
}

void init()
{
    for(int i = 0; i < 4; i++)
    {
        for(int y = 0; y < N; y++)
        {
            for(int x = 0; x < N; x++)
                visit[i][y][x] = 0x7fffffff;
        }
    }
}

int solve(const vector<vector<int>>& board)
{
    int result = 0x7fffffff;
    queue<Node> q;
    
    map = board;
    N = static_cast<int>(map.size());
    
    init();
    visit[1][0][0] = 0;
    q.push({0,0,1,0});
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int dir = q.front().dir;
        int cnt = q.front().cnt;
        q.pop();

        int ny = y+dy[dir];
        int nx = x+dx[dir];
        int ndir = counter_dir(dir);
        
        if(visit[ndir][ny][nx] > cnt)
        {
            visit[ndir][ny][nx] = cnt;
            q.push({ny,nx,ndir,cnt});
        }
        
        if(y == N-1 && x == N-1)
        {
            result = min(result,cnt);
            continue;
        }
        
        int clock = clock_wise(dir); // 시계
        int counter_clock = counter_clock_wise(dir); // 반시계
        
        if(dir == 0) // north
        {
            // 시계
            if(x+1 < N && !map[y-1][x+1] && !map[y][x+1])
            {
                if(visit[clock][y][x] > cnt+1)
                {
                    visit[clock][y][x] = cnt+1;
                    q.push({y,x,clock,cnt+1});
                }
            }
            
            // 반시계
            if(x-1 >= 0 && !map[y-1][x-1] && !map[y][x-1])
            {
                if(visit[counter_clock][y][x] > cnt+1)
                {
                    visit[counter_clock][y][x] = cnt+1;
                    q.push({y,x,counter_clock,cnt+1});
                }
            }
            
        } else if(dir == 1) // east
        {
            // 시계
            if(y+1 < N && !map[y+1][x+1] && !map[y+1][x])
            {
                if(visit[clock][y][x] > cnt+1)
                {
                    visit[clock][y][x] = cnt+1;
                    q.push({y,x,clock,cnt+1});
                }
            }
            
            // 반시계
            if(y-1 >= 0 && !map[y-1][x+1] && !map[y-1][x])
            {
                if(visit[counter_clock][y][x] > cnt+1)
                {
                    visit[counter_clock][y][x] = cnt+1;
                    q.push({y,x,counter_clock,cnt+1});
                }
            }
            
        } else if(dir == 2) // south
        {
            // 시계
            if(x-1 >= 0 && !map[y+1][x-1] && !map[y][x-1])
            {
                if(visit[clock][y][x] > cnt+1)
                {
                    visit[clock][y][x] = cnt+1;
                    q.push({y,x,clock,cnt+1});
                }
            }
            
            // 반시계
            if(x+1 < N && !map[y+1][x+1] && !map[y][x+1])
            {
                if(visit[counter_clock][y][x] > cnt+1)
                {
                    visit[counter_clock][y][x] = cnt+1;
                    q.push({y,x,counter_clock,cnt+1});
                }
            }
            
        } else // west
        {
            // 시계
            if(y-1 >= 0 && !map[y-1][x-1] && !map[y-1][x])
            {
                if(visit[clock][y][x] > cnt+1)
                {
                    visit[clock][y][x] = cnt+1;
                    q.push({y,x,clock,cnt+1});
                }
            }
            
            // 반시계
            if(y+1 < N && !map[y+1][x-1] && !map[y+1][x])
            {
                if(visit[counter_clock][y][x] > cnt+1)
                {
                    visit[counter_clock][y][x] = cnt+1;
                    q.push({y,x,counter_clock,cnt+1});
                }
            }
        }
        
        for(int i = 0; i < 4; i++)
        {
            int my = y+dy[i];
            int mx = x+dx[i];
            int mny = ny+dy[i];
            int mnx = nx+dx[i];
            
            if(!range(my,mx) || !range(mny,mnx))
                continue;
            if(map[my][mx] || map[mny][mnx])
                continue;
            if(visit[dir][my][mx] <= cnt+1)
                continue;
            
            visit[dir][my][mx] = cnt+1;
            q.push({my,mx,dir,cnt+1});
        }
    }
    
    return result;
}

int solution(vector<vector<int>> board)
{
    return solve(board);
}
