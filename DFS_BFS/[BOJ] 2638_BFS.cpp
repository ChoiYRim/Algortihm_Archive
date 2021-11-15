#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 128;

struct Node
{
    int y;
    int x;
};

int n,m,ans;
int map[MAX][MAX];
int air[MAX][MAX];
bool visited[MAX][MAX];
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

queue<Node> q;
vector<Node> melted;

inline bool range(int y,int x) { return ((0 <= y && y < n) && (0 <= x && x < m)); }

void printMap()
{
    cout << "\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void bfs()
{
    q.push({0,0});
    visited[0][0] = true;
    
    while(!q.empty())
    {
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if(!range(ny,nx))
                continue;
            
            // 공기라면
            if(map[ny][nx] == 0 && !visited[ny][nx])
            {
                q.push({ny,nx});
                visited[ny][nx] = true;
            }
            // 치즈라면
            else if(map[ny][nx] == 1)
            {
                air[ny][nx] += 1;
                
                // 치즈가 녹을 예정이면?
                if(air[ny][nx] >= 2 && !visited[ny][nx])
                {
                    melted.push_back({ny,nx});
                    visited[ny][nx] = true;
                }
            }
        }
        
        if(q.empty())
        {
            if(!melted.empty())
                ans++;
            else
                break;
            
            for(int i = 0; i < melted.size(); i++)
            {
                q.push(melted[i]);
                map[melted[i].y][melted[i].x] = 0;
            }
            melted.clear();
        }
    }
}

int main(int argc, const char * argv[])
{
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }
    
    memset(visited, false, sizeof(visited));
    ans = 0;
    bfs();
    
    cout << ans << "\n";
    return 0;
}
