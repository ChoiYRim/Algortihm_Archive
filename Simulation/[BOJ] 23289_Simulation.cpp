#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
//#include <map>

using namespace std;

int R,C,K,W;
int visit[32][32];
int check[32][32];
vector<vector<int>> room;
vector<pair<pair<int,int>,int>> heaters;
vector<pair<pair<int,int>,int>> heatPos[32][32];
bool walls[5][32][32];
int dy[5] = {0,0,0,-1,1}; // [x,right,left,up,down]
int dx[5] = {0,1,-1,0,0}; // [x,right,left,up,down]

void print_room()
{
    for(int y = 1; y <= R; y++)
    {
        for(int x = 1; x <= C; x++)
        {
            printf("%3d ", room[y][x]);
        }
        printf("\n");
    }
}

void print(const char* str)
{
    cout << str << endl;
    print_room();
    cout << endl;
}


inline bool range(int y,int x) { return ((y >= 1 && y <= R) && (x >= 1 && x <= C)); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> R >> C >> K;
    room = vector<vector<int>>(R+1,vector<int>(C+1,0));
    for(int i = 1; i <= R; i++)
    {
        vector<int> tmp;
        for(int j = 1; j <= C; j++)
        {
            cin >> room[i][j];
            if(room[i][j] == 5)
                check[i][j] = 1;
            else if(room[i][j] != 0)
                heaters.push_back({{i,j},room[i][j]});
            room[i][j] = 0;
        }
    }
    cin >> W;
    for(int i = 0; i < W; i++)
    {
        int x,y,t; cin >> y >> x >> t;
        int ny = y,nx = x;
        
        if(!t) ny--;
        else nx++;
        
        if(!t) // north
        {
            walls[3][y][x] = true;
            walls[4][ny][nx] = true;
        }
        else // east
        {
            walls[1][y][x] = true;
            walls[2][ny][nx] = true;
        }
    }
}

bool isThereWall(int y,int x,int ty,int tx,int dir) // 시작 y,x / 도착 y,x / 방향 dir
{
    if(dir == 1 || dir == 2) // 오른쪽 왼쪽 - x값은 동일
    {
        if(y-1 == ty)
        {
            //mid = {y-1,x};
            if(walls[3][y][x])
                return true;
            if(walls[dir][y-1][x])
                return true;
        }
        else if(y+1 == ty)
        {
            //mid = {y+1,x};
            if(walls[4][y][x])
                return true;
            if(walls[dir][y+1][x])
                return true;
        }
        else
            return walls[dir][y][x];
    }
    else // 위 아래 - y값은 동일
    {
        if(x-1 == tx)
        {
            //mid = {y,x-1};
            if(walls[2][y][x])
                return true;
            if(walls[dir][y][x-1])
                return true;
        }
        else if(x+1 == tx)
        {
            //mid = {y,x+1};
            if(walls[1][y][x])
                return true;
            if(walls[dir][y][x+1])
                return true;
        }
        else
            return walls[dir][y][x];
    }
    
    return false;
}

void bfs(int y,int x,int dir)
{
    queue<pair<pair<int,int>,int>> q;
    memset((int*)visit,0,sizeof(visit));
    
    q.push({{y+dy[dir],x+dx[dir]},5});
    visit[y][x] = 1;
    heatPos[y][x].push_back({{y+dy[dir],x+dx[dir]},5});
    while(!q.empty())
    {
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int ct = q.front().second; // 현재 위치 온도
        q.pop();
        
        room[cy][cx] += ct;
        if(ct-1 <= 0)
            continue;
        for(int i = -1; i <= 1; i++)
        {
            int ny,nx;
            
            if(!dy[dir])
            {
                ny = cy+i;
                nx = cx+dx[dir];
            }
            else
            {
                ny = cy+dy[dir];
                nx = cx+i;
            }
            
            if(!range(ny,nx))
                continue;
            if(visit[ny][nx])
                continue;
            if(isThereWall(cy,cx,ny,nx,dir))
                continue;
            
            visit[ny][nx] = 1;
            heatPos[y][x].push_back({{ny,nx},ct-1});
            q.push({{ny,nx},ct-1});
        }
    }
}

void heat()
{
    // 모든 히터에 대해서
    for(auto it = heaters.begin(); it != heaters.end(); it++)
    {
        int y = it->first.first; // 히터의 위치
        int x = it->first.second;
        int dir = it->second; // 바람 방향
        auto heat = heatPos[y][x];
        
        if(heat.size() <= 0)
        {
            //heatPos.insert({{y,x},{}});
            bfs(y,x,dir);
            continue;
        }
        
        for(const auto& pos : heat)
        {
            int py = pos.first.first;
            int px = pos.first.second;
            int pt = pos.second;
            
            room[py][px] += pt;
        }
    }
}

bool control()
{
    int dir;
    int temp_dy[2] = {0,1};
    int temp_dx[2] = {1,0};
    bool finish = true;
    vector<vector<int>> newRoom = room;
    
    for(int y = 1; y <= R; y++)
    {
        for(int x = 1; x <= C; x++)
        {
            for(int i = 0; i < 2; i++)
            {
                if(i == 0) dir = 1;
                else dir = 4;
                
                int ny = y+temp_dy[i];
                int nx = x+temp_dx[i];
                
                if(!range(ny,nx))
                    continue;
                if(walls[dir][y][x])
                    continue;
                
                int diff = abs(newRoom[y][x]-newRoom[ny][nx]);
                if(newRoom[y][x] < newRoom[ny][nx])
                {
                    room[y][x] += diff / 4;
                    room[ny][nx] -= diff / 4;
                    //if(room[ny][nx] < 0) room[ny][nx] = 0;
                }
                else if(newRoom[y][x] > newRoom[ny][nx])
                {
                    room[y][x] -= diff / 4;
                    room[ny][nx] += diff / 4;
                    //if(room[y][x] < 0) room[y][x] = 0;
                }
            }
            
            if(y == 1 || y == R)
            {
                if(room[y][x] > 0) room[y][x]--;
            }
            else
            {
                if(x == 1 || x == C)
                    if(room[y][x] > 0) room[y][x]--;
            }
            
            if(check[y][x] && room[y][x] < K)
                finish = false;
        }
    }
    
    return finish;
}

int solve()
{
    int choco = 0;
    
    while(true)
    {
        //print("CURRENT RESULT");
        
        // 집에 있는 모든 온풍기에서 바람이 한 번 나옴 - 1
        heat();
        
        // 온도가 조절됨 - 2
        // 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소 - 3
        bool check = control();
        
        // 초콜릿을 하나 먹는다. - 4
        choco++;
        
        // 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다. - 5
        if(check || choco > 100)
            break;
    }
    
    //print("FINAL RESULT");
    return choco;
}

int main()
{
    input();
    
    int result = solve();
    
    cout << (result > 100 ? 101 : result) << endl;
    return 0;
}

