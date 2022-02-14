#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

struct Node
{
    int y;
    int x;
    int d;
};

int dy[8] = {-1,-1,0,1,1,1,0,-1}; // 북 -> 북서 -> 서 -> ... -> 북동
int dx[8] = {0,-1,-1,-1,0,1,1,1};
Node fishes[17];
bool hunted[17];
int visit[17][4][4];

inline bool range(int y,int x) { return ((y >= 0 && y < 4) && (x >= 0 && x < 4)); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            int num,dir; cin >> num >> dir;
            fishes[num] = {y,x,dir-1};
        }
    }
    
    hunted[0] = 1;
}

pair<int,int> get_fish(int y,int x)
{
    for(int i = 1; i <= 16; i++)
    {
        int fy = fishes[i].y;
        int fx = fishes[i].x;
        
        if(hunted[i])
            continue;
        if(fy == y && fx == x)
            return {i,fishes[i].d};
    }
    
    return {-1,-1};
}

void move_fishes(int shark_y,int shark_x)
{
    // 1번 물고기부터 마지막 번호 물고기까지 차례대로 이동
    for(int i = 1; i <= 16; i++)
    {
        if(not hunted[i])
        {
            int y = fishes[i].y;
            int x = fishes[i].x;
            int d = fishes[i].d;
            
            for(int j = 0; j < 8; j++)
            {
                int nd = (d+j)%8;
                int ny = y+dy[nd];
                int nx = x+dx[nd];
                
                if(!range(ny,nx)) // 범위 이탈
                    continue;
                if(ny == shark_y && nx == shark_x) // 상어가 있는 칸
                    continue;
                
                auto fish = get_fish(ny,nx);
                int idx = fish.first;
                int dir = fish.second;
                
                fishes[i] = {ny,nx,nd};
                if(idx != -1)
                    fishes[idx] = {y,x,dir};
                break;
            }
        }
    }
}

void print(int score)
{
    printf("CURRENT EAT LIST : ");
    for(int i = 1; i <= 16; i++)
        if(hunted[i])
            printf("%2d ", i);
    printf("\n");
}

void dfs(int cnt,int y,int x,int d,int score,int& answer)
{
    answer = max(answer,score);
    if(cnt > 16)
        return;
    //print(score);
    
    Node tmp_fishes[17];
    memcpy(tmp_fishes,fishes,sizeof(fishes));
    
    move_fishes(y,x); // 물고기 이동
    
    // 상어가 이동
    int ny = y+dy[d];
    int nx = x+dx[d];
    for( ; range(ny,nx); ny += dy[d], nx += dx[d])
    {
        auto fish = get_fish(ny,nx); // 상어가 움직일 위치에 있을 물고기 탐색
        int idx = fish.first;
        int dir = fish.second;
        
        if(idx == -1) // 물고기가 없는 칸이면 pass
            continue;
        
        int fy = fishes[idx].y;
        int fx = fishes[idx].x;
        
        if(visit[cnt+1][fy][fx] > score+idx) // already visited
            continue;
        
        int save = visit[cnt+1][fy][fx];
        
        visit[cnt+1][fy][fx] = score+idx;
        hunted[idx] = 1;
        dfs(cnt+1,ny,nx,dir,score+idx,answer);
        visit[cnt+1][fy][fx] = save;
        hunted[idx] = 0;
    }
    
    memcpy(fishes,tmp_fishes,sizeof(tmp_fishes));
}

int solve()
{
    auto fish = get_fish(0,0);
    int idx = fish.first;
    int dir   = fish.second;
    int answer = 0;
    
    hunted[idx] = 1;
    visit[1][0][0] = idx;
    
    dfs(1,0,0,dir,idx,answer);
    
    return answer;
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
