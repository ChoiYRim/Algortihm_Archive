#include <queue>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Pos
{
    int y;
    int x;
    int cnt;
};

int N,M;
queue<Pos> q;
vector<string> v;
bool visit[128][128] = {0,};
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

int main(void)
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        v.push_back(tmp);
    }
    
    visit[0][0] = true;
    q.push({0,0,1});
    while(!q.empty())
    {
        Pos cur = q.front();
        q.pop();
        
        if(cur.y == N-1 && cur.x == M-1)
        {
            cout << cur.cnt << '\n';
            break;
        }
        
        for(int i = 0; i < 4; i++)
        {
            int ny = cur.y+dy[i];
            int nx = cur.x+dx[i];
            
            if(range(ny,nx) && !visit[ny][nx] && v[ny][nx] != '0')
            {
                visit[ny][nx] = true;
                q.push({ny,nx,cur.cnt+1});
            }
        }
    }
    
    return 0;
}
