#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int cnt;
    int y1;
    int x1;
    int y2;
    int x2;
};

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
int N, M;
vector<string> map;
int ya = -1, xa = -1;
int yb = -1, xb = -1;

inline bool range(int y, int x) { return ((y >= 0 && y < N) && (x >= 0 && x < M)); }

void input()
{
    cin >> N >> M;
    map = vector<string>(N);
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        map[i] = tmp;
        
        for(int j = 0; j < M; j++)
        {
            if(tmp[j] == 'o')
            {
                if(ya != -1)
                {
                    yb = i;
                    xb = j;
                }
                else
                {
                    ya = i;
                    xa = j;
                }
            }
        }
    }
}

int solve()
{
    int ans = 11;
    queue<Node> q;
    
    q.push({0, ya, xa, yb, xb});
    while(!q.empty())
    {
        int cur = q.front().cnt;
        int y1 = q.front().y1;
        int x1 = q.front().x1;
        int y2 = q.front().y2;
        int x2 = q.front().x2;
        
        q.pop();
        
        if(cur > 10 || cur >= ans)
            continue;
        
        for(int dir = 0; dir < 4; dir++)
        {
            int cnt = 0, ny1 = -1, nx1 = -1, ny2 = -1, nx2 = -1;

            for(int i = 0; i < 2; i++)
            {
                int y, x;
                
                if(i == 0)
                {
                    y = y1;
                    x = x1;
                }
                else
                {
                    y = y2;
                    x = x2;
                }
                                
                int ny = y+dy[dir];
                int nx = x+dx[dir];
                
                if(!range(ny, nx))
                {
                    cnt++;
                    continue;
                }
                if(map[ny][nx] == '#')
                {
                    if(ny1 != -1)
                    {
                        ny2 = y;
                        nx2 = x;
                    }
                    else
                    {
                        ny1 = y;
                        nx1 = x;
                    }
                    continue;
                }
                
                if(ny1 != -1)
                {
                    ny2 = ny;
                    nx2 = nx;
                }
                else
                {
                    ny1 = ny;
                    nx1 = nx;
                }
            }
            if(cnt == 0)
            {
                q.push({cur+1, ny1, nx1, ny2, nx2});
            }
            else if(cnt == 1)
            {
                ans = cur+1;
                break;
            }
        }
    }
    
    return (ans > 10 ? -1 : ans);
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
