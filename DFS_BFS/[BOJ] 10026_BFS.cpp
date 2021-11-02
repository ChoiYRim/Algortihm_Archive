#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<string> v;
int r1 = 0,r2 = 0;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

inline bool range(int y,int x) { return ((0 <= y && y < N) && (0 <= x && x < N)); }

char ifBlind(char color) { return (color != 'B' ? 'R' : 'B'); }

void solve(bool blind)
{
    bool visit[128][128] = {0,};
    
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            if(!visit[y][x])
            {
                char color = v[y][x];
                
                if(!blind)
                    r1++;
                else
                    r2++;
                
                queue<pair<int,int>> q;
                visit[y][x] = true;
                q.push({y,x});
                while(!q.empty())
                {
                    pair<int,int> p = q.front();
                    q.pop();
                    
                    for(int i = 0; i < 4; i++)
                    {
                        int ny = p.first+dy[i];
                        int nx = p.second+dx[i];
                        
                        if(range(ny,nx) && !visit[ny][nx])
                        {
                            if(!blind && color == v[ny][nx])
                            {
                                visit[ny][nx] = true;
                                q.push({ny,nx});
                            }
                            if(blind && ifBlind(color) == ifBlind(v[ny][nx]))
                            {
                                visit[ny][nx] = true;
                                q.push({ny,nx});
                            }
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        string tmp = ""; cin >> tmp;
        v.push_back(tmp);
    }
    
    solve(false);
    solve(true);
    
    cout << r1 << " " << r2 << '\n';
    return 0;
}
