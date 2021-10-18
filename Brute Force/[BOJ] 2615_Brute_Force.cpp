#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int Map[32][32] = {0,};
vector<pair<int,int>> result;
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int dx[8] = {0,1,1,1,0,-1,-1,-1};

bool range(int y,int x)
{
    return ((1 <= y && y <= 19) && (1 <= x && x <= 19));
}

bool comp(pair<int,int>& p1,pair<int,int>& p2)
{
    if(p1.second == p2.second)
        return p1.first < p2.first;
    return p1.second < p2.second;
}

vector<pair<int,int>> search(int y,int x,int color,int dir)
{
    vector<pair<int,int>> v;
    
    while(Map[y][x] == color)
    {
        v.push_back({y,x});
        y += dy[dir];
        x += dx[dir];
        if(!range(y,x))
            return v;
    }
    
    return v;
}

bool check(int y,int x,int color,int dir)
{
    int d1 = dir,d2 = (dir+4)%8;
    int cnt = -1,ny,nx;
    
    ny = y; nx = x;
    while(Map[ny][nx] == color)
    {
        cnt++;
        ny = ny+dy[d1];
        nx = nx+dx[d1];
        if(!range(ny,nx))
            break;
    }
    ny = y; nx = x;
    while(Map[ny][nx] == color)
    {
        cnt++;
        ny = ny+dy[d2];
        nx = nx+dx[d2];
        if(!range(ny,nx))
            break;
    }
    
    if(cnt > 5 || cnt < 5)
        return false;
    return true;
}

int main(int argc,char* argv[])
{
    for(int y = 1; y <= 19; y++)
    {
        for(int x = 1; x <= 19; x++)
            cin >> Map[y][x];
    }
    
    for(int y = 1; y <= 19; y++)
    {
        for(int x = 1; x <= 19; x++)
        {
            if(!Map[y][x])
                continue;
            
            for(int i = 0; i < 8; i++)
            {
                vector<pair<int,int>> v = search(y,x,Map[y][x],i);
                sort(v.begin(),v.end(),comp);
                
                if(v.size() < 5 || v.size() > 5) // 기준 미달
                    continue;
                if(!check(y,x,Map[y][x],i))
                    continue;
                cout << Map[y][x] << '\n';
                cout << v[0].first << " " << v[0].second << '\n';
                return 0;
            }
        }
    }
    
    cout << 0 << '\n';
    return 0;
}
