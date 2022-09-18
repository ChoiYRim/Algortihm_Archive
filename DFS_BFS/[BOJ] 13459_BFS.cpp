#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int cnt;
    int ry, rx;
    int by, bx;
};

int N, M;
int _ry, _rx;
int _by, _bx;
vector<string> map;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

void input()
{
    cin >> N >> M;
    for(int y = 0; y < N; y++)
    {
        string tmp; cin >> tmp;
        for(int x = 0; x < M; x++)
        {
            if(tmp[x] == 'R')
            {
                _ry = y;
                _rx = x;
                tmp[x] = '.';
            }
            else if(tmp[x] == 'B')
            {
                _by = y;
                _bx = x;
                tmp[x] = '.';
            }
        }
        map.push_back(tmp);
    }
}

bool solve()
{
    queue<Node> q;
    
    q.push({0, _ry, _rx, _by, _bx});
    while(!q.empty())
    {
        int cnt = q.front().cnt;
        int ry = q.front().ry;
        int rx = q.front().rx;
        int by = q.front().by;
        int bx = q.front().bx;
        q.pop();
        
        if(cnt > 10) continue;
        
        for(int i = 0; i < 4; i++)
        {
            bool flag = false;
            int nry = ry, nrx = rx;
            int nby = by, nbx = bx;
                        
            // 일단 빨간색 공 먼저 움직이기
            while(map[nry][nrx] != '#' && map[nry][nrx] != 'O')
            {
                nry += dy[i];
                nrx += dx[i];
            }
            // 사후 조사
            if(map[nry][nrx] == '#')
            {
                nry -= dy[i];
                nrx -= dx[i];
            }
            else if(map[nry][nrx] == 'O')
            {
                flag = true;
            }
            
            // 파란공도 움직이기
            while(map[nby][nbx] != '#' && map[nby][nbx] != 'O')
            {
                nby += dy[i];
                nbx += dx[i];
            }
            // 사후 조사
            if(map[nby][nbx] == '#')
            {
                nby -= dy[i];
                nbx -= dx[i];
            }
            else if(map[nby][nbx] == 'O')
            {
                continue;
            }
            
            if(flag && cnt+1 <= 10)
                return 1;
            if(nry == nby && nrx == nbx) // 겹침
            {
                switch(i)
                {
                    case 0:
                    {
                        if(ry < by) nby -= dy[i];
                        else nry -= dy[i];
                        break;
                    }
                    case 1:
                    {
                        if(rx < bx) nrx -= dx[i];
                        else nbx -= dx[i];
                        break;
                    }
                    case 2:
                    {
                        if(ry < by) nry -= dy[i];
                        else nby -= dy[i];
                        break;
                    }
                    case 3:
                    {
                        if(rx < bx) nbx -= dx[i];
                        else nrx -= dx[i];
                        break;
                    }
                    default:
                        break;
                }
            }
            
            if(cnt+1 > 10) continue;
            
            q.push({cnt+1, nry, nrx, nby, nbx});
        }
    }
    
    return 0;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
