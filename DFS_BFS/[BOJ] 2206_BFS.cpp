#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int kMax = 0x7fffffff;

struct Pos
{
    int y;
    int x;
    bool w; // wall
};

int N,M;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
bool Map[1024][1024] = {0,};
vector<vector<vector<int>>> visit;
queue<Pos> q;

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline bool range(int y,int x) { return ((1 <= y && y <= N) && (1 <= x && x <= M)); }

void input()
{
    cin >> N >> M;
    for(int y = 1; y <= N; y++)
    {
        string tmp; cin >> tmp;
        for(int x = 0; x < M; x++)
        {
            if(tmp[x] != '0')
                Map[y][x+1] = 1;
            else
                Map[y][x+1] = 0;
        }
    }
    
    // [벽을 부순 적 있는가?][높이][너비]
    visit = vector<vector<vector<int>>>(2,vector<vector<int>>(N+1,vector<int>(M+1,kMax)));
    visit[0][1][1] = 1;
    q.push({1,1,false});
}

int solve()
{
    while(!q.empty())
    {
        Pos cur = q.front();
        q.pop();
        
        if(cur.y == N && cur.x == M)
            continue;
        
        for(int i = 0; i < 4; i++)
        {
            int ny = cur.y+dy[i];
            int nx = cur.x+dx[i];
            
            if(range(ny,nx))
            {
                int value = visit[cur.w][cur.y][cur.x];
                
                if(!Map[ny][nx])
                {
                    if(visit[cur.w][ny][nx] > value+1)
                    {
                        visit[cur.w][ny][nx] = value+1;
                        q.push({ny,nx,cur.w});
                    }
                }
                else
                {
                    if(!cur.w && visit[cur.w][ny][nx] > value+1)
                    {
                        visit[1][ny][nx] = value+1;
                        q.push({ny,nx,true});
                    }
                }
            }
        }
    }
    
    if(visit[0][N][M] != kMax || visit[1][N][M] != kMax)
        return MIN(visit[0][N][M],visit[1][N][M]);
    return -1;
}

int main()
{
    input();
    cout << solve() << '\n';
    return 0;
}
