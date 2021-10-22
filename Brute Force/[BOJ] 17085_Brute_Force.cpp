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
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

inline int getArea(int maxSize) { return (1 + 4*maxSize); }

void print(vector<int> sz)
{
    cout << "SIZE : [ ";
    for(int i = 0; i < sz.size(); i++)
        cout << sz[i] << " ";
    cout << "]\n";
}

void status(char flag,int maxSize,int idx)
{
    int y = pos[idx].y,x = pos[idx].x;
    
    for(int size = 0; size <= maxSize; size++)
    {
        for(int i = 0; i < 4; i++)
        {
            int ny = y+size*dy[i];
            int nx = x+size*dx[i];
            
            v[ny][nx] = flag;
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
            
            if(!range(ny,nx) || v[ny][nx] != '#')
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

int main(int argc,char* argv[])
{
    ans = 0;
    
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
        
    for(int i = 0; i < (int)pos.size()-1; i++)
    {
        int iy = pos[i].y,ix = pos[i].x;
        int imax = getSize(iy,ix);
        
        for(int j = 0; j <= imax; j++)
        {
            status('*',j,i);
            for(int k = i+1; k < (int)pos.size(); k++)
            {
                int ky = pos[k].y,kx = pos[k].x;
                int kmax = getSize(ky,kx);
                
                ans = MAX(ans,(getArea(j)*(getArea(kmax))));
            }
            status('#',j,i);
        }
    }
    
    cout << ans << '\n';
    return 0;
}
