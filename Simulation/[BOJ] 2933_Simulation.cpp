#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

int R,C,N;
vector<int> stick;
vector<string> map;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((y >= 0 && y < R) && (x >= 0 && x < C)); }

bool comp(const pair<int,int>& p1,const pair<int,int>& p2)
{
    if(p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first < p2.first;
}

void input()
{
    cin >> R >> C;
    for(int y = 0; y < R; y++)
    {
        string tmp; cin >> tmp;
        map.push_back(tmp);
    }
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        stick.push_back(tmp);
    }
}

auto Throw(bool turn,int height)
{
    if(!turn)
    {
        for(int col = 0; col < C; col++)
        {
            if(map[height][col] == 'x')
            {
                map[height][col] = '.';
                break;
            }
        }
    }
    else
    {
        for(int col = C-1; col >= 0; col--)
        {
            if(map[height][col] == 'x')
            {
                map[height][col] = '.';
                break;
            }
        }
    }
}

void dfs(int y,int x,vector<vector<bool>>& visit)
{
    for(int i = 0; i < 4; i++)
    {
        int ny = y+dy[i];
        int nx = x+dx[i];
        
        if(!range(ny,nx))
            continue;
        
        if(map[ny][nx] == 'x' && !visit[ny][nx])
        {
            visit[ny][nx] = 1;
            dfs(ny,nx,visit);
        }
    }
}

void down_spaces(vector<set<pair<int,int>>>& spaces)
{
    for(auto i = 0; i < spaces.size(); i++)
    {
        int diff = 0x7fffffff;
        set<pair<int,int>> space = spaces[i];
        
        for(auto& s : space)
        {
            for(int j = 1; ; j++)
            {
                int y = s.first+j;
                int x = s.second;
                
                if(space.find({y,x}) != space.end())
                    break;
                if(!range(y,x))
                {
                    diff = min(diff,j-1);
                    break;
                }
                if(map[y][x] == 'x')
                {
                    diff = min(diff,j-1);
                    break;
                }
            }
        }
        
        for(auto& s : space)
            map[s.first][s.second] = '.';
        for(auto& s : space)
            map[s.first+diff][s.second] = 'x';
    }
}

void down()
{
    vector<vector<bool>> visit(R,vector<bool>(C,0));
    vector<set<pair<int,int>>> spaces;
    
    // 땅에 붙어있는 클러스터들 찾기
    for(int x = 0; x < C; x++)
    {
        if(map[R-1][x] == 'x' && !visit[R-1][x])
        {
            visit[R-1][x] = 1;
            dfs(R-1,x,visit);
        }
    }
    
    // 공중에 떠 있는 클러스터들 찾기
    for(int y = R-1; y >= 0; y--)
    {
        for(int x = 0; x < C; x++)
        {
            if(!visit[y][x] && map[y][x] == 'x')
            {
                set<pair<int,int>> space;
                queue<pair<int,int>> q;
                
                q.push({y,x});
                visit[y][x] = 1;
                space.insert({y,x});
                while(!q.empty())
                {
                    pair<int,int> cur = q.front();
                    q.pop();
                    
                    for(int i = 0; i < 4; i++)
                    {
                        int ny = cur.first+dy[i];
                        int nx = cur.second+dx[i];
                        
                        if(!range(ny,nx))
                            continue;
                        if(!visit[ny][nx] && map[ny][nx] == 'x')
                        {
                            space.insert({ny,nx});
                            q.push({ny,nx});
                            visit[ny][nx] = 1;
                        }
                    }
                }
                
                spaces.push_back(space);
            }
        }
    }
    
    // 클러스터 내리기
    down_spaces(spaces);
}

void solve()
{
    for(int turn = 0; turn < N; turn++)
    {
        int height = R-stick[turn];
        
        Throw(turn%2,height); // throw a stick
        down();
    }
}

void output()
{
    for(int y = 0; y < R; y++)
        cout << map[y] << endl;
}

int main(int argc,char* argv[])
{
    input();
    
    solve();
    
    output();
    return 0;
}
