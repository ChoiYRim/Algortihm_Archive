#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

struct Node
{
    int y;
    int x;
};

const int kMax = 0x7fffffff;

int N;
vector<string> Map;
vector<vector<int>> visit;
queue<Node> q;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < N)); }

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        Map.push_back(tmp);
    }
    visit = vector<vector<int>>(N,vector<int>(N,kMax));
}

int main()
{
    int ans = kMax;
    
    input();
    
    q.push({0,0});
    visit[0][0] = 0;
    while(!q.empty())
    {
        Node cur = q.front();
        q.pop();
        
        int value = visit[cur.y][cur.x];
        
        if(cur.y == N-1 && cur.x == N-1)
        {
            ans = MIN(ans,value);
            continue;
        }
        
        for(int i = 0; i < 4; i++)
        {
            int ny = cur.y+dy[i];
            int nx = cur.x+dx[i];
            
            if(range(ny,nx))
            {
                if(Map[ny][nx] == '0')
                {
                    if(visit[ny][nx] > value+1)
                    {
                        visit[ny][nx] = value+1;
                        q.push({ny,nx});
                    }
                }
                else
                {
                    if(visit[ny][nx] > value)
                    {
                        visit[ny][nx] = value;
                        q.push({ny,nx});
                    }
                }
            }
        }
    }
    
    cout << ans << '\n';
    return 0;
}
