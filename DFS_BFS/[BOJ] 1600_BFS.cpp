#include <iostream>
#include <queue>

using namespace std;

struct Pos
{
    int y;
    int x;
    int t;
    int knight;
};

const int kMax = 0x7fffffff;

int K,H,W;

// normal
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

// knight
int kdy[8] = {-1,-2,-2,-1,1,2,2,1};
int kdx[8] = {-2,-1,1,2,2,1,-1,-2};

bool Map[256][256] = {0,};
vector<vector<vector<int>>> visit;
queue<Pos> q;

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline bool range(int y,int x) { return ((0 <= y && y < H) && (0 <= x && x < W)); }

int main()
{
    int result = kMax;
    
    cin >> K;
    cin >> W >> H;
    for(int y = 0; y < H; y++)
    {
        for(int x = 0; x < W; x++)
            cin >> Map[y][x];
    }
    // [나이트를 사용한 횟수][y][x]
    visit = vector<vector<vector<int>>>(32,vector<vector<int>>(H,vector<int>(W,kMax)));
    
    visit[0][0][0] = 0;
    q.push({0,0,0,0});
    while(!q.empty())
    {
        int ny,nx,kn;
        Pos cur = q.front();
        q.pop();
        
        if(cur.y == H-1 && cur.x == W-1)
        {
            result = MIN(result,cur.t);
            continue;
        }
        
        kn = cur.knight;
        
        for(int i = 0; i < 4; i++)
        {
            ny = cur.y+dy[i];
            nx = cur.x+dx[i];
            
            if(range(ny,nx) && !Map[ny][nx] && visit[kn][ny][nx] > cur.t+1)
            {
                visit[kn][ny][nx] = cur.t+1;
                q.push({ny,nx,cur.t+1,cur.knight});
            }
        }
        
        if(kn < K)
        {
            for(int i = 0; i < 8; i++)
            {
                ny = cur.y+kdy[i];
                nx = cur.x+kdx[i];
                
                if(range(ny,nx) && !Map[ny][nx] && visit[kn+1][ny][nx] > cur.t+1)
                {
                    visit[kn+1][ny][nx] = cur.t+1;
                    q.push({ny,nx,cur.t+1,cur.knight+1});
                }
            }
        }
    }
    
    if(result != kMax)
        cout << result << '\n';
    else
        cout << -1 << '\n';
    return 0;
}
