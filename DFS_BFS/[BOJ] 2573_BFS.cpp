#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N,M;
int map[512][512];
int visit[512][512];
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
vector<vector<pair<int,int>>> ices;
vector<vector<pair<int,int>>> newIces;

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < M)); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    vector<pair<int,int>> ice;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            cin >> map[y][x];
            if(map[y][x])
                ice.push_back({y,x});
        }
    }
    ices.push_back(ice);
}

void melt(vector<pair<int,int>>& ice) // 녹이기
{
    for(auto& i : ice)
    {
        int y = i.first;
        int x = i.second;
        int cnt = 0;
        
        for(int j = 0; j < 4; j++)
        {
            int ny = y+dy[j];
            int nx = x+dx[j];
            
            if(!range(ny,nx))
                continue;
            if(map[ny][nx])
                continue;
            
            cnt++;
        }
        visit[y][x] -= cnt;
        if(visit[y][x] < 0) visit[y][x] = 0;
    }
}

bool check() // 나뉘었는가
{
    memset((int*)visit,0,sizeof(visit));
    for(auto i = 0; i < ices.size(); i++)
    {
        for(auto j = 0; j < ices[i].size(); j++)
        {
            int y = ices[i][j].first;
            int x = ices[i][j].second;
            
            if(visit[y][x])
                continue;
            if(!map[y][x])
                continue;
            
            queue<pair<int,int>> q;
            vector<pair<int,int>> v;
            
            q.push({y,x});
            visit[y][x] = 1;
            v.push_back({y,x});
            while(!q.empty())
            {
                int cy = q.front().first;
                int cx = q.front().second;
                q.pop();
                
                for(int k = 0; k < 4; k++)
                {
                    int ny = cy+dy[k];
                    int nx = cx+dx[k];
                    
                    if(!range(ny,nx))
                        continue;
                    if(visit[ny][nx])
                        continue;
                    if(!map[ny][nx])
                        continue;
                    
                    visit[ny][nx] = 1;
                    v.push_back({ny,nx});
                    q.push({ny,nx});
                }
            }
            
            newIces.push_back(v);
        }
    }
    
    if(!newIces.size()) // 다 녹음
        return false;
    if(ices.size() != newIces.size()) // 분리됨
        return true;
    return false;
}

int solve()
{
    if(check())
        return 0;
    
    for(int year = 1; ices.size(); year++)
    {
        newIces.clear();
        
        memcpy(visit,map,sizeof(map));
        for(auto i = 0; i < ices.size(); i++)
            melt(ices[i]);
        memcpy(map,visit,sizeof(map));
        
        if(check())
            return year;
        ices = newIces;
    }
    return 0;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
