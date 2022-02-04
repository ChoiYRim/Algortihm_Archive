#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node
{
    int y;
    int x;
    int cnt;
};

int R,C;
int dy[10] = {0,1,1,1,0,0,0,-1,-1,-1};
int dx[10] = {0,-1,0,1,-1,0,1,-1,0,1};
Node jongSu;
map<pair<int,int>,int> crazy;
vector<string> Map;
queue<int> dir;

inline bool range(int y,int x) { return ((y >= 0 && y < R) && (x >= 0 && x < C)); }

void reset()
{
    for(int y = 0; y < R; y++)
    {
        for(int x = 0; x < C; x++)
        {
            Map[y][x] = '.';
        }
    }
    
    Map[jongSu.y][jongSu.x] = 'I';
    for(auto& it : crazy)
        Map[it.first.first][it.first.second] = 'R';
}

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    string tmp;
    
    cin >> R >> C;
    for(int i = 0; i < R; i++)
    {
        cin >> tmp;
        for(int j = 0; j < C; j++)
        {
            if(tmp[j] == 'I')
                jongSu = {i,j,0};
            else if(tmp[j] == 'R')
            {
                crazy.insert({{i,j},1});
            }
        }
        Map.push_back(tmp);
    }
    cin >> tmp;
    for(size_t i = 0; i < tmp.length(); i++)
        dir.push(tmp[i]-'0');
}

inline int dist(const Node& me,const int y,const int x)
{
    return abs(me.y-y)+abs(me.x-x);
}

void print()
{
    for(int y = 0; y < R; y++)
        cout << Map[y] << endl;
}

void solve()
{
    int cnt = 0;
    bool gameOver = false;
    
    while(!dir.empty())
    {
        //cout << "Current Map" << endl;
        //print();
        //cout << endl;
        
        int curDir = dir.front();
        map<pair<int,int>,int> newCrazy;
        dir.pop();
        
        int y = jongSu.y;
        int x = jongSu.x;
        int ny = y+dy[curDir]; // step 1
        int nx = x+dx[curDir];
        int ncnt = jongSu.cnt+1;
        
        Map[y][x] = '.';
        if(Map[ny][nx] == 'R') // step 2
        {
            gameOver = true;
            cnt = ncnt;
            break;
        }
        Map[ny][nx] = 'I';
        jongSu = {ny,nx,ncnt};
        
        for(auto it = crazy.begin(); it != crazy.end(); it++) // step 3
        {
            int cy = it->first.first;
            int cx = it->first.second;
            int cny,cnx;
            int idx = 0,minDist = 0x7fffffff;
            
            for(int i = 1; i < 10; i++)
            {
                cny = cy+dy[i];
                cnx = cx+dx[i];
                int Dist = dist(jongSu,cny,cnx);
                
                if(!range(cny,cnx))
                    continue;
                if(minDist > Dist)
                {
                    minDist = Dist;
                    idx = i;
                }
            }
            cny = cy+dy[idx];
            cnx = cx+dx[idx];
            if(Map[cny][cnx] == 'I')
            {
                gameOver = true;
                cnt = ncnt;
                break;
            }
            if(newCrazy.find({cny,cnx}) != newCrazy.end())
                newCrazy[{cny,cnx}]++;
            else
                newCrazy.insert({{cny,cnx},1});
        }
        if(gameOver)
            break;
        
        vector<pair<int,int>> v;
        for(auto it = newCrazy.begin(); it != newCrazy.end(); it++)
        {
            if(it->second > 1)
                v.push_back(it->first);
        }
        for(auto it = v.begin(); it != v.end(); it++)
            newCrazy.erase({it->first,it->second});
        
        crazy = newCrazy;
        reset();
    }
    
    if(gameOver)
    {
        cout << "kraj " << cnt << endl;
    }
    else
        print();
}

int main(int argc,char* argv[])
{
    input();
    
    solve();
    return 0;
}


