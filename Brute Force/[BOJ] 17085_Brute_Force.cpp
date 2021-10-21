#include <vector>
#include <string>
#include <iostream>

#define MAX(a,b) (a > b ? a : b)

using namespace std;

struct Pos
{
    int y;
    int x;
};

int N,M,ans;
vector<string> v;
vector<Pos> pos;
bool visit[32][32] = {0,};
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

void status(bool flag,int maxSize,int idx)
{
    int y = pos[idx].y,x = pos[idx].x;
    
    for(int size = 0; size <= maxSize; size++)
    {
        for(int i = 0; i < 4; i++)
        {
            int ny = y+size*dy[i];
            int nx = x+size*dx[i];
            
            visit[ny][nx] = flag;
        }
    }
}

int getSize(int y,int x)
{
    int maxSize = 0;
    bool check = true;
    
    for(int size = 1; check; size++)
    {
        for(int i = 0; i < 4; i++)
        {
            int ny = y+size*dy[i];
            int nx = x+size*dx[i];
            
            if(!range(ny,nx) || visit[ny][nx] || v[ny][nx] == '.')
            {
                check = false;
                break;
            }
        }
        if(check)
            maxSize++;
    }
    
    return maxSize;
}

int getArea(int maxSize)
{
    int area = 1;
    
    for(int i = 0; i < maxSize; i++)
        area += 4;
    
    return area;
}

void print(vector<int> sz)
{
    cout << "SIZE : [ ";
    for(int i = 0; i < sz.size(); i++)
        cout << sz[i] << " ";
    cout << "]\n";
}

void DFS(vector<int> sz)
{
    if(sz.size() >= 2)
    {
        int result = sz[0]*sz[1];
        
        //print(sz);
        
        ans = MAX(ans,result);
        return;
    }
    
    for(int i = 0; i < (int)pos.size(); i++)
    {
        int y = pos[i].y,x = pos[i].x;
        
        if(!visit[y][x])
        {
            int maxSize = getSize(y,x);
            
            status(true,maxSize,i);
            sz.push_back(getArea(maxSize));
            DFS(sz);
            sz.pop_back();
            status(false,maxSize,i);
        }
    }
}

int main(int argc,char* argv[])
{
    ans = 1;
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        string str = ""; cin >> str;
        for(int j = 0; j < M; j++)
        {
            if(str[j] == '#')
                pos.push_back({i,j});
        }
        v.push_back(str);
    }
    
    DFS({});
    
    cout << ans << '\n';
    return 0;
}
