#include <cstdio>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N,M,K;
vector<vector<int>> map;
vector<vector<vector<int>>> visit;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < M)); }

void input()
{
    cin >> N >> M >> K;
    map = vector<vector<int>>(N,vector<int>(M,0));
    visit = vector<vector<vector<int>>>(16,vector<vector<int>>(N,vector<int>(M,0)));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            scanf("%1d", &map[i][j]);
        }
    }
}

int solve()
{
    struct Node
    {
        int y; // row
        int x; // col
        int k; // K
        int d; // distance
    };
    
    queue<Node> q;
    
    q.push({0,0,0,1});
    visit[0][0][0] = 1;
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int k = q.front().k;
        int d = q.front().d;
        q.pop();
        
        if(y == N-1 && x == M-1)
            return d;
        
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny,nx))
                continue;
            if(!map[ny][nx] && !visit[k][ny][nx]) // 0
            {
                q.push({ny,nx,k,d+1});
                visit[k][ny][nx] = 1;
            }
            else if(map[ny][nx] == 1 && k < K && !visit[k+1][ny][nx])
            {
                q.push({ny,nx,k+1,d+1});
                visit[k+1][ny][nx] = 1;
            }
        }
    }
    
    return -1;
}

int main()
{
    input();
    
    printf("%d\n", solve());
    return 0;
}
