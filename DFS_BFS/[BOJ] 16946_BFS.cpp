#include <set>
#include <queue>
#include <string>
#include <iostream>

using namespace std;
using P = pair<int,int>;

int N,M;
int sect[1024][1024];
int area[1024][1024];
vector<int> zeroSize;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < M)); }

void print()
{
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
            cout << area[y][x]%10;
        }
        cout << '\n';
    }
}

void input()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        string tmp = ""; cin >> tmp;
        for(int j = 0; j < (int)tmp.length(); j++)
        {
            sect[i][j] = 0;
            
            if(tmp[j] != '0') // 1
                area[i][j] = 1;
            else
                area[i][j] = 0;
        }
    }
    zeroSize.push_back(0);
}

void makeGroup()
{
    int section = 1;
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(!area[i][j] && !sect[i][j])
            {
                int cnt = 0;
                queue<P> q;
                
                q.push({i,j});
                sect[i][j] = section;
                while(!q.empty())
                {
                    int y = q.front().first;
                    int x = q.front().second;
                    q.pop();
                    
                    cnt++;
                    for(int k = 0; k < 4; k++)
                    {
                        int ny = y+dy[k];
                        int nx = x+dx[k];
                        
                        if(!range(ny,nx))
                            continue;
                        if(area[ny][nx] != 0)
                            continue;
                        if(sect[ny][nx] != 0)
                            continue;
                        
                        q.push({ny,nx});
                        sect[ny][nx] = section;
                    }
                }
                
                zeroSize.push_back(cnt);
                section++;
            }
        }
    }
}

void solve()
{
    makeGroup();
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(area[i][j])
            {
                set<int> s;
                for(int k = 0; k < 4; k++)
                {
                    int ny = i+dy[k];
                    int nx = j+dx[k];
                    
                    if(!range(ny,nx))
                        continue;
                    if(!sect[ny][nx])
                        continue;
                    if(s.find(sect[ny][nx]) != s.end())
                        continue;
                    
                    s.insert(sect[ny][nx]);
                    area[i][j] += zeroSize[sect[ny][nx]];
                }
            }
            cout << area[i][j]%10;
        }
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
        
    input();
    
    solve();
    
    //print();
    return 0;
}
