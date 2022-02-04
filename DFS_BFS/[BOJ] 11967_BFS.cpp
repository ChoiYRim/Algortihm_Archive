#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int N,M;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
int visit[128][128],Map[128][128];
vector<pair<int,int>> bulb[128][128];

inline bool range(int y,int x) { return ((y > 0 && y <= N) && (x > 0 && x <= N)); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> M;
    for(int i = 0; i < M; i++)
    {
        int x,y,a,b; cin >> y >> x >> a >> b; // [y][x] -> [a][b]
        bulb[y][x].push_back({a,b});
        //m.insert({{y,x},{a,b}});
    }
    
    memset((int*)Map,0,sizeof(Map));
    memset((int*)visit,0,sizeof(visit));
}

int bfs()
{
    struct Node
    {
        int y;
        int x;
    };
    
    int cnt = 1;
    queue<Node> q;
    
    Map[1][1] = 1;
    visit[1][1] = 1;
    q.push({1,1}); // cnt : 현재까지 킨 불 개수
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int num = 0;
        q.pop();
        
        // 현재 있는 방에서 킬 수 있는 불은 모두 킨다. -> 베시가 불을 켤 수 있는 방의 최대 개수를 구하는 것이므로
        for(auto it = bulb[y][x].begin(); it != bulb[y][x].end(); it++)
        {
            int ny = it->first;
            int nx = it->second;
            
            if(!Map[ny][nx])
            {
                Map[ny][nx] = 1;
                num++;
            }
        }
        
        cnt += num;
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
                    
            if(!range(ny,nx)) // 범위 초과
                continue;
            if(!Map[ny][nx]) // 어두워서 안됨
                continue;
            if(visit[ny][nx] >= cnt)
                continue;
            
            //printf("[%d,%d]'s target position : [%d,%d]\n",y,x,ny,nx);
            
            visit[ny][nx] = cnt;
            q.push({ny,nx});
        }
    }
    
    return cnt;
}

int main()
{
    input();
        
    cout << bfs() << endl;
    return 0;
}
