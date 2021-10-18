#include <vector>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

struct Cross
{
    int row;
    int column;
    int size;
};

int N,M;
vector<string> v;
vector<Cross> result;
bool visit[128][128] = {0,};
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

inline bool range(int x,int y) { return ((0 <= x && x < N) && (0 <= y && y < M)); }

bool check()
{
    for(int x = 0; x < N; x++)
    {
        for(int y = 0; y < M; y++)
        {
            if(v[x][y] != '*')
                continue;
            if(!visit[x][y])
                return false;
        }
    }
    
    return true;
}

int maxSize(int x,int y)
{
    for(int size = 1; ;size++)
    {
        for(int i = 0; i < 4; i++)
        {
            int nx = x+size*dx[i];
            int ny = y+size*dy[i];
            
            if(!range(nx,ny) || v[nx][ny] != '*')
                return size-1;
        }
    }
    
    return 0;
}

void solve()
{
    for(int x = 0; x < N; x++)
    {
        for(int y = 0; y < M; y++)
        {
            if(v[x][y] != '*')
                continue;
            
            int size = maxSize(x,y);
            
            if(!size)
                continue;
            
            visit[x][y] = true;
            for(int s = 1; s <= size; s++)
            {
                for(int i = 0; i < 4; i++)
                {
                    int nx = x+s*dx[i];
                    int ny = y+s*dy[i];
                    
                    visit[nx][ny] = true;
                }
            }
            result.push_back({x,y,size});
        }
    }
}

void input()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        string str = ""; cin >> str;
        v.push_back(str);
    }
}

void output()
{
    if(!check())
        cout << -1 << '\n';
    else
    {
        cout << result.size() << '\n';
        for(int i = 0; i < result.size(); i++)
            cout << result[i].row+1 << " " << result[i].column+1 << " " << result[i].size << '\n';
    }
}

int main(int argc,char* argv[])
{
    input();
    solve();
    output();
    return 0;
}
