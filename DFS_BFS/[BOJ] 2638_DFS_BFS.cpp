#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int row,col;
int visit[128][128];
vector<vector<int>> map;
queue<pair<int,int>> cheese;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((y >= 0 && y < row) && (x >= 0 && x < col)); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> row >> col;
    for(int y = 0; y < row; y++)
    {
        vector<int> line;
        for(int x = 0; x < col; x++)
        {
            int tmp; cin >> tmp;
            if(tmp)
                cheese.push({y,x});
            line.push_back(tmp);
        }
        map.push_back(line);
    }
}

void dfs(int y,int x)
{
    map[y][x] = -1;
    visit[y][x] = true;
    for(int i = 0; i < 4; i++)
    {
        int ny = y+dy[i];
        int nx = x+dx[i];
        
        if(!range(ny,nx))
            continue;
        if(visit[ny][nx])
            continue;
        if(map[ny][nx] == 0)
            dfs(ny,nx);
    }
}

int solve()
{
    int hours = 0;
    
    // 외부 공기층 검사 - 모눈종이의 테두리 공간은 치즈가 없는 것으로 가정했으므로
    memset((int *)visit,0,sizeof(visit));
    dfs(0,0); // 외부 공기층은 모두 -1로 변환
    
    while(!cheese.empty())
    {
        // 외부 공기와 2면 이상 접한 치즈 체크
        queue<pair<int,int>> next,melt;
        
        while(!cheese.empty())
        {
            int connected = 0;
            int y = cheese.front().first;
            int x = cheese.front().second;
            cheese.pop();
            
            for(int i = 0; i < 4; i++)
            {
                int ny = y+dy[i];
                int nx = x+dx[i];
                
                if(map[ny][nx] == -1)
                    connected++;
            }
            if(connected >= 2)
                melt.push({y,x});
            else
                next.push({y,x});
        }
        
        // 치즈 녹이기
        while(!melt.empty())
        {
            int y = melt.front().first;
            int x = melt.front().second;
            melt.pop();
            
            dfs(y,x);
        }
        
        cheese = next;
        hours++;
    }
    
    return hours;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
