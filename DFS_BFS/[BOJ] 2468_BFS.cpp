#include <queue>
#include <iostream>

using namespace std;

int N,limit = 0;
int Map[128][128] = {0,};
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline int MAX(int a,int b) { return (a > b ? a : b); }

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < N)); }

void input()
{
    cin >> N;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            cin >> Map[y][x];
            limit = MAX(Map[y][x],limit);
        }
    }
}

void solve()
{
    int result = 0,cnt;
    queue<pair<int,int>> q;
    
    for(int h = 0; h <= limit; h++)
    {
        cnt = 0;
        bool flood[128][128] = {0,};
        
        for(int y = 0; y < N; y++)
        {
            for(int x = 0; x < N; x++)
            {
                if(Map[y][x] >= h && !flood[y][x])
                {
                    cnt++;
                    q.push({y,x});
                    flood[y][x] = true;

                    while(!q.empty())
                    {
                        pair<int,int> p = q.front();
                        q.pop();
                        
                        for(int i = 0; i < 4; i++)
                        {
                            int ny = p.first+dy[i];
                            int nx = p.second+dx[i];
                            
                            if(range(ny,nx) && Map[ny][nx] >= h && !flood[ny][nx])
                            {
                                q.push({ny,nx});
                                flood[ny][nx] = true;
                            }
                        }
                    }
                }
            }
        }
        
        result = MAX(result,cnt);
    }
    
    cout << result << '\n';
}

int main()
{
    input();
    solve();
    return 0;
}
