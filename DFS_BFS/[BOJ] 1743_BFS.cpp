#include <queue>
#include <iostream>

using namespace std;

int N,M,K,result = 0;
bool Map[128][128] = {0,};
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
queue<pair<int,int>> q;

inline int MAX(int a,int b) { return (a > b ? a : b); }

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

int main()
{
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++)
    {
        int r,c; cin >> r >> c;
        Map[r-1][c-1] = 1;
    }
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            if(Map[y][x])
            {
                int cnt = 0;
                Map[y][x] = 0;
                q.push({y,x});
                while(!q.empty())
                {
                    pair<int,int> cur = q.front();
                    q.pop();
                    
                    cnt++;
                    
                    for(int i = 0; i < 4; i++)
                    {
                        int ny = cur.first+dy[i];
                        int nx = cur.second+dx[i];
                        
                        if(range(ny,nx) && Map[ny][nx])
                        {
                            Map[ny][nx] = 0;
                            q.push({ny,nx});
                        }
                    }
                }
                
                result = MAX(result,cnt);
            }
        }
    }
    
    cout << result << '\n';
    return 0;
}
