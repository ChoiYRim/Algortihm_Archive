#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int w,h,sy,sx;
const int dy[4]={-1,1,0,0};
const int dx[4]={0,0,1,-1};
char map[20][20];
bool visit[20][20][1<<10];

struct Node
{
    int y;
    int x;
    int cnt;
};

vector<Node> dusts;
 
int getPos(int y,int x)
{
    for(int i = 0; i < dusts.size(); i++)
    {
        if(dusts[i].y == y && dusts[i].x == x)
            return i;
    }
    
    return 0;
}
int bfs()
{
    memset(visit,0,sizeof(visit));
    
    queue<Node> q;
    visit[sy][sx][0] = 1;
    q.push({sy,sx,0});
    int ret = 0;
    
    while(!q.empty())
    {
        int q_size = static_cast<int>(q.size());
        while(q_size--)
        {
            Node node = q.front();
            q.pop();
            
            if(node.cnt == (1<<dusts.size())-1)
                return ret;
            
            for(int i = 0; i < 4; i++)
            {
                int ny = node.y+dy[i];
                int nx = node.x+dx[i];
                int cnt = node.cnt;
                
                if(ny < 0 || nx < 0 || ny >= h || nx >= w || map[ny][nx] == 'x')
                    continue;
                if(map[ny][nx]=='*')
                    cnt |= (1<<getPos(ny,nx));
                if(!visit[ny][nx][cnt])
                {
                    visit[ny][nx][cnt] = 1;
                    q.push({ny,nx,cnt});
                }
            }
        }
        ret++;
    }
    return -1;
}
 
int main()
{
    while(true)
    {
        scanf("%d%d",&w,&h);
        if(w == 0 && h == 0)
            break;
        
        dusts.clear();
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                scanf(" %c",&map[i][j]);
                if(map[i][j]=='o')
                {
                    sy=i;
                    sx=j;
                }
                else if(map[i][j]=='*')
                {
                    dusts.push_back({i,j,0});
                }
            }
        }
        
        printf("%d\n",bfs());
    }
}
