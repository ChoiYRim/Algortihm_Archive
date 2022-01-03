#include <vector>
#include <iostream>

using namespace std;

vector<int> color;
vector<vector<pair<int,int>>> v; // color paper
bool paper[16][16];

int ans = -1;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline int MIN(int a,int b) { return (a > b ? b : a); }

inline bool range(int y,int x) { return ((y >= 0 && y < 10) && (x >= 0 && x < 10)); }

void input()
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            cin >> paper[y][x];
        }
    }
    
    color = vector<int>(6,5);
    v = vector<vector<pair<int,int>>>(6,vector<pair<int,int>>());
    for(size_t width = 1; width <= 5; width++)
    {
        for(int y = 0; y < width; y++)
        {
            for(int x = 0; x < width; x++)
            {
                v[width].push_back({y,x});
            }
        }
    }
}

void getPos(int y,int x,int width,vector<pair<int,int>>& pos)
{
    for(int i = 0; i < (int)v[width].size(); i++)
    {
        pos.push_back({y+v[width][i].first,x+v[width][i].second});
    }
}

bool isPossible(vector<pair<int,int>>& pos)
{
    for(int i = 0; i < (int)pos.size(); i++)
    {
        int y = pos[i].first;
        int x = pos[i].second;
        
        if(!range(y,x))
            return false;
        if(!paper[y][x])
            return false;
    }
    
    return true;
}

void coverArea(vector<pair<int,int>>& pos,bool check)
{
    for(int i = 0; i < (int)pos.size(); i++)
    {
        int y = pos[i].first;
        int x = pos[i].second;
        
        paper[y][x] = check;
    }
}

void solve(int cnt,int depth)
{
    if(depth >= 100)
    {
        if(ans != -1)
            ans = MIN(ans,cnt);
        else
            ans = cnt;
        return;
    }
    
    int y = depth/10;
    int x = depth%10;
    
    if(paper[y][x])
    {
        for(int i = 5; i > 0; i--)
        {
            if(!color[i])
                continue;
            
            vector<pair<int,int>> pos;
            getPos(y, x, i, pos);
            
            if(isPossible(pos))
            {
                color[i]--;
                coverArea(pos,false);
                solve(cnt+1,depth+1);
                coverArea(pos,true);
                color[i]++;
            }
        }
    }
    else
        solve(cnt,depth+1);
}

int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    input();
    
    solve(0,0);
    
    cout << ans << '\n';
    return 0;
}
