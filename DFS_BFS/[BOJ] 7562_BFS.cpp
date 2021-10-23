#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos
{
    int y;
    int x;
    int cnt;
};

int T,L;
int dy[8] = {-1,-2,-2,-1,1,2,2,1};
int dx[8] = {-2,-1,1,2,2,1,-1,-2};
vector<int> result;

inline bool range(int y,int x) { return ((0 <= y && y < L) && (0 <= x && x < L)); }

int main(void)
{
    cin >> T;
    while(T--)
    {
        queue<Pos> q;
        Pos start = {0,0,0},end = {0,0,0};
        bool visit[512][512] = {0,};
        
        cin >> L;
        cin >> start.y >> start.x;
        cin >> end.y >> end.x;
        
        if(start.y == end.y && start.x == end.x)
        {
            result.push_back(0);
            continue;
        }
        
        visit[start.y][start.x] = true;
        q.push({start.y,start.x,0});
        while(!q.empty())
        {
            Pos cur = q.front();
            q.pop();
            
            if(cur.y == end.y && cur.x == end.x)
            {
                result.push_back(cur.cnt);
                break;
            }
            
            for(int i = 0; i < 8; i++)
            {
                int ny = cur.y+dy[i];
                int nx = cur.x+dx[i];
                
                if(!range(ny,nx) || visit[ny][nx])
                    continue;
                
                visit[ny][nx] = true;
                q.push({ny,nx,cur.cnt+1});
            }
        }
    }
    
    for(int i = 0; i < (int)result.size(); i++)
        cout << result[i] << '\n';
    return 0;
}
