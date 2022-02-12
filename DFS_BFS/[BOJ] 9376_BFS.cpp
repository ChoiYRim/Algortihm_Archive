#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <string>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;

const int kMax = INT_MAX;

struct Node
{
    int y;
    int x;
    int cnt;
    
    inline bool operator<(const Node& n) const { return cnt < n.cnt; }
    inline bool operator>(const Node& n) const { return cnt > n.cnt; }
};

int TC,R,C;
int result;
vector<int> results;
vector<string> map;
vector<pair<int,int>> prisoners;
int door[3][128][128];
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((y >= 0 && y <= R+1) && (x >= 0 && x <= C+1)); }

void print_map()
{
    cout << "MAP PRINTED" << endl;
    for(auto y = 0; y < map.size(); y++)
    {
        cout << map[y] << endl;
    }
}

void input()
{
    result = kMax;
    map.clear();
    prisoners.clear();
    
    cin >> R >> C;
    prisoners.push_back({0,0});
    map.push_back(string(C+2,'.'));
    for(int y = 1; y <= R; y++)
    {
        string tmp; cin >> tmp;
        
        tmp = "."+tmp;
        for(int x = 1; x <= C; x++)
        {
            if(tmp[x] == '$')
                prisoners.push_back({y,x});
        }
        tmp.push_back('.');
        map.push_back(tmp);
    }
    map.push_back(string(C+2,'.'));
    
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 128; j++)
            fill(door[i][j],door[i][j]+128,kMax);
    }
}

void output()
{
    for(auto& result : results)
        cout << result << endl;
}

void solve()
{
    for(int i = 0; i < 3; i++)
    {
        int y = prisoners[i].first;
        int x = prisoners[i].second;
        bool visit[128][128] = {0,};
        
        priority_queue<Node,vector<Node>,greater<Node>> pq;
        pq.push({y,x,0});
        visit[y][x] = 1;
        door[i][y][x] = 0;
        
        while(!pq.empty())
        {
            int cy = pq.top().y;
            int cx = pq.top().x;
            int cnt = pq.top().cnt;
            pq.pop();
            
            for(int j = 0; j < 4; j++)
            {
                int ny = cy+dy[j];
                int nx = cx+dx[j];
                int ncnt = cnt;
                
                if(!range(ny,nx))
                    continue;
                if(visit[ny][nx] || map[ny][nx] == '*')
                    continue;
                if(map[ny][nx] == '#')
                    ncnt++;
                
                if(door[i][ny][nx] > ncnt)
                {
                    door[i][ny][nx] = ncnt;
                    visit[ny][nx] = 1;
                    pq.push({ny,nx,ncnt});
                }
            }
        }
    }
    
    for(int y = 1; y <= R; y++)
    {
        for(int x = 1; x <= C; x++)
        {
            if(map[y][x] == '*')
                continue;
            int sum = 0;
            for(int i = 0; i < 3; i++)
            {
                sum += door[i][y][x];
            }
            if(map[y][x] == '#')
                sum -= 2;
            
            result = min(result,sum);
        }
    }
}

int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> TC;
    while(TC--)
    {
        input();
        
        //print_map();
        
        solve();
        
        results.push_back(result);
    }
    
    output();
    return 0;
}
