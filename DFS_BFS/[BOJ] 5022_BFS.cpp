#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

struct Pos
{
    int y;
    int x;
    int cnt;
    vector<pair<int,int>> path;
};

int N,M;
vector<Pos> v1,v2;
const int dy[4] = {-1,0,1,0};
const int dx[4] = {0,1,0,-1};

inline bool range(int y, int x) { return ((y >= 0 && y <= N) && (x >= 0 && x <= M)); }

inline bool comp(const Pos& p1, const Pos& p2) { return (p1.y == p2.y ? p1.x < p2.x : p1.y < p2.y); }

void input()
{
    cin >> N >> M;
    for(int i = 0; i < 2; i++)
    {
        int y,x; cin >> y >> x;
        v1.push_back({y,x,0,{}});
    }
    for(int i = 0; i < 2; i++)
    {
        int y,x; cin >> y >> x;
        v2.push_back({y,x,0,{}});
    }
    
    sort(v1.begin(),v1.end(),comp);
    sort(v2.begin(),v2.end(),comp);
}

int get_path(const Pos& from, const Pos& to, const Pos& p1, const Pos& p2, const vector<pair<int,int>>& danger)
{
    int result = INF;
    queue<Pos> q;
    vector<vector<bool>> visit(N+1,vector<bool>(M+1,0));
    
    visit[from.y][from.x] = 1;
    q.push({from.y, from.x, 0, {{from.y,from.x},{to.y,to.x}}});
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int cnt = q.front().cnt;
        auto path = q.front().path;
        q.pop();
        
        if(y == to.y && x == to.x)
        {
            if(danger.size() > 2)
            {
                result = min(result,cnt);
                continue;
            }
            
            result = min(result,cnt+get_path(p1, p2, from, to, path));
            continue;
        }
        
        for(int i = 0; i < 4; i++)
        {
            bool exists = false;
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny,nx)) continue;
            if(visit[ny][nx]) continue;
            
            for(int j = 0; j < danger.size(); j++)
            {
                if(ny == danger[j].first && nx == danger[j].second)
                {
                    exists = true;
                    break;
                }
            }
            
            if(exists) continue;
            
            visit[ny][nx] = 1;
            path.push_back({ny, nx});
            q.push({ny, nx, cnt+1, path});
            path.pop_back();
        }
    }
    
    return result;
}

string solve()
{
    int result1 = get_path(v1[0], v1[1], v2[0], v2[1], {{v2[0].y, v2[0].x}, {v2[1].y, v2[1].x}});
    int result2 = get_path(v2[0], v2[1], v1[0], v1[1], {{v1[0].y, v1[0].x}, {v1[1].y, v1[1].x}});
    
    return (result1 >= INF && result2 >= INF ? "IMPOSSIBLE" : to_string(min(result1,result2)));
}

int main(int argc,char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
