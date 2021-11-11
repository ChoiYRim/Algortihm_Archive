#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int kMax = 0x7fffffff;

struct Pos
{
    int y;
    int x;
    int t; // time
};

int H,W,T;
vector<vector<int>> visit;
vector<string> Map,result;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline bool range(int y,int x) { return ((0 <= y && y < H) && (0 <= x && x < W)); }

int main()
{
    cin >> T;
    while(T--)
    {
        Map.clear();
        visit.clear();
        
        Pos start;
        queue<Pos> q,fire;
        int output = kMax;
        
        cin >> W >> H;
        for(int y = 0; y < H; y++)
        {
            string tmp; cin >> tmp;
            for(int x = 0; x < W; x++)
            {
                if(tmp[x] == '@')
                    start = {y,x,0};
                else if(tmp[x] == '*')
                    fire.push({y,x,0});
            }
            Map.push_back(tmp);
        }
        visit = vector<vector<int>>(H+1,vector<int>(W+1,0));
        
        visit[start.y][start.x] = 1;
        q.push({start.y,start.x,0});
        while(!q.empty())
        {
            Pos cur = q.front();
            q.pop();
            
            int ny,nx;
            
            if(fire.size() > 0 && cur.t == fire.front().t)
            {
                queue<Pos> new_fire;
                while(!fire.empty())
                {
                    Pos f = fire.front();
                    fire.pop();
                    
                    for(int i = 0; i < 4; i++)
                    {
                        ny = f.y+dy[i];
                        nx = f.x+dx[i];
                        
                        if(range(ny,nx) && (Map[ny][nx] == '.' || Map[ny][nx] == '@'))
                        {
                            Map[ny][nx] = '*';
                            new_fire.push({ny,nx,f.t+1});
                        }
                    }
                }
                
                fire = new_fire;
            }
            
            for(int i = 0; i < 4; i++)
            {
                ny = cur.y+dy[i];
                nx = cur.x+dx[i];
                
                if(!range(ny,nx))
                {
                    output = MIN(output,cur.t+1);
                    continue;
                }
                
                if(range(ny,nx) && Map[ny][nx] == '.' && !visit[ny][nx])
                {
                    visit[ny][nx] = 1;
                    q.push({ny,nx,cur.t+1});
                }
            }
        }
        if(output != kMax)
            result.push_back(to_string(output));
        else
            result.push_back("IMPOSSIBLE");
    }
    
    for(int i = 0; i < (int)result.size(); i++)
        cout << result[i] << '\n';
    return 0;
}
