#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int y;
    int x;
    int t; // time
};

vector<vector<string>> maps;
vector<pair<int,int>> walls;
const int dy[9] = {-1,-1,-1,0,0,0,1,1,1};
const int dx[9] = {-1,0,1,-1,0,1,-1,0,1};

inline bool range(int y,int x) { return ((y >= 0 && y < 8) && (x >= 0 && x < 8)); }

void print_map()
{
    for(int i = 0; i < 9; i++)
    {
        printf("Time : %d\n", i);
        for(int j = 0; j < 8; j++)
            printf("%s\n", maps[i][j].c_str());
        printf("-------------\n");
    }
}

void input()
{
    maps = vector<vector<string>>(9);
    for(int i = 0; i < 8; i++)
    {
        string tmp; cin >> tmp;
        for(int j = 0; j < 8; j++)
        {
            if(tmp[j] == '#')
                walls.push_back({i,j});
        }
        maps[0].push_back(tmp);
    }
}

void init()
{
    for(int i = 1; i <= 8; i++)
    {
        auto tmp = maps[i-1];
        
        tmp.pop_back();
        tmp.insert(tmp.begin(), string(8,'.'));
        
        maps[i] = tmp;
    }
}

bool solve()
{
    queue<Node> q;
    bool visit[8][8][9] = {0,};
    
    q.push({7,0,0});
    visit[7][0][0] = 1;
    
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int t = q.front().t;
        vector<string> cur,next;
        q.pop();
        
        if(y == 0 && x == 7)
            return true;
                
        if(t >= 8)
        {
            cur = maps[8];
            next = maps[8];
        }
        else
        {
            cur = maps[t];
            next = maps[t+1];
        }
        
        for(int i = 0; i < 9; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny,nx))
                continue;
            if(next[ny][nx] == '#')
                continue;
            if(cur[ny][nx] == '#')
                continue;
            if(visit[ny][nx][t+1])
                continue;
            
            q.push({ny,nx,t+1});
            visit[ny][nx][t+1] = 1;
        }
    }
    
    return false;
}

int main(int argc,char* argv[])
{
    input();
    init();
    //print_map();
    cout << solve() << endl;
    return 0;
}
