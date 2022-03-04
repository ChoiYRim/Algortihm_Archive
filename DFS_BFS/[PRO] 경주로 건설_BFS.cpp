#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;
const int MAX = 25*25*500;

struct Node
{
    int y;
    int x;
    int cost;
    int dir;
};

int N;
int dy[4] = {-1,0,1,0}; // north, east, south, west
int dx[4] = {0,1,0,-1}; // ""
vector<vector<vector<int>>> road;

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < N)); }

void init(const vector<vector<int>>& board,queue<Node>& q)
{
    N = static_cast<int>(board.size());
    road = vector<vector<vector<int>>>(4);
    for(int i = 0; i < 4; i++)
    {
        road[i] = vector<vector<int>>(N,vector<int>(N,MAX));
        road[i][0][0] = 0;
        q.push({0,0,0,i});
    }
}

int solve(const vector<vector<int>>& board,queue<Node>& q)
{
    int result = MAX;
    
    while(!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int cost = q.front().cost;
        int dir = q.front().dir;
        q.pop();
        
        if(y == N-1 && x == N-1)
        {
            result = min(result,cost);
            continue;
        }
        
        int ny = y+dy[dir];
        int nx = x+dx[dir];
        
        if(range(ny,nx) && !board[ny][nx])
        {
            if(road[dir][ny][nx] > cost+100)
            {
                road[dir][ny][nx] = cost+100;
                q.push({ny,nx,cost+100,dir});
            }
        }
        
        for(int i = 0; i < 4; i++)
        {
            if(dir == i)
                continue;
            if(i == (dir+2)%4) // 왔던 방향으로 거슬러 올라감 -> 낭비
                continue;
            
            ny = y+dy[i];
            nx = x+dx[i];
            
            if(!range(ny,nx))
                continue;
            if(board[ny][nx]) // wall
                continue;
            if(road[i][ny][nx] > cost+600)
            {
                road[i][ny][nx] = cost+600;
                q.push({ny,nx,cost+600,i});
            }
        }
    }
    
    return result;
}

int solution(vector<vector<int>> board)
{
    queue<Node> q;
    
    init(board,q);
    
    return solve(board,q);
}

int main(int argc,char* argv[])
{
    cout << solution({{0,0,0},{0,0,0},{0,0,0}}) << endl;
    return 0;
}
