#include <set>
#include <queue>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Pos
{
    int y;
    int x;
};

int N,M;
vector<string> v;
vector<Pos> land;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline int MAX(int a,int b) { return (a > b ? a : b); }

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

int main()
{
    int dist = 0;
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        v.push_back(tmp);
    }
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            if(v[y][x] != 'L')
                continue;
            
            queue<Pos> q;
            vector<vector<int>> vd(N,vector<int>(M,-1));
            
            vd[y][x] = 0;
            q.push({y,x});
            while(!q.empty())
            {
                Pos cur = q.front();
                q.pop();
                
                for(int i = 0; i < 4; i++)
                {
                    int ny = cur.y+dy[i];
                    int nx = cur.x+dx[i];
                    
                    if(range(ny,nx) && v[ny][nx] != 'W' && vd[ny][nx] < 0)
                    {
                        vd[ny][nx] = vd[cur.y][cur.x]+1;
                        dist = MAX(dist,vd[ny][nx]);
                        q.push({ny,nx});
                    }
                }
            }
        }
    }
    
    cout << dist << '\n';
    return 0;
}
