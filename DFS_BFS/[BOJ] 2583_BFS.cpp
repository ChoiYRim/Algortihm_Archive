#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int M,N,K; // x , y , 좌표 개수
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
bool Map[128][128] = {0,};
vector<int> result;

inline bool range(int x,int y) { return ((0 <= x && x < M) && (0 <= y && y < N)); }

void print()
{
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            cout << Map[y][x] << ' ';
        }
        cout << '\n';
    }
}

void init(pair<int,int> left,pair<int,int> right)
{
    for(int y = left.second; y < right.second; y++)
    {
        for(int x = left.first; x < right.first; x++)
            Map[y][x] = true;
    }
}

int solve(int y,int x)
{
    int cnt = 0;
    queue<pair<int,int>> q;
    Map[y][x] = true;
    q.push({y,x});
    
    while(!q.empty())
    {
        pair<int,int> pos = q.front();
        q.pop();
        
        cnt++;
        
        for(int i = 0; i < 4; i++)
        {
            int ny = pos.first+dy[i];
            int nx = pos.second+dx[i];
            
            if(range(nx,ny) && !Map[ny][nx])
            {
                Map[ny][nx] = true;
                q.push({ny,nx});
            }
        }
    }
    
    return cnt;
}

int main(void)
{
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++)
    {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        init({x1,y1},{x2,y2});
    }
    
//    print();
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            if(!Map[y][x])
            {
                int cnt = solve(y,x);
                result.push_back(cnt);
            }
        }
    }
    
    sort(result.begin(),result.end());
    
    cout << result.size() << '\n';
    for(int i = 0; i < (int)result.size(); i++)
        cout << result[i] << ' ';
    cout << '\n';
    return 0;
}
