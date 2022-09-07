#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int T, R, C;
int sy, sx;
int ey, ex;
vector<string> map;
vector<pair<int, vector<int>>> signals;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0 ,-1};

inline bool range(int y, int x) { return ((y >= 0 && y < R) && (x >= 0 && x < C)); }

void input()
{
    map.clear();
    signals.clear();
    
    int cnt = 0;
    
    cin >> R >> C;
    if(R == 0 && C == 0) exit(0);
    for(int y = 0; y < R; y++)
    {
        string tmp; cin >> tmp;
        for(int x = 0; x < C; x++)
        {
            if(tmp[x] == 'A')
            {
                sy = y;
                sx = x;
            }
            else if(tmp[x] == 'B')
            {
                ey = y;
                ex = x;
            }
            else if(tmp[x] >= '0' && tmp[x] <= '9')
            {
                cnt++;
            }
        }
        map.push_back(tmp);
    }
    for(int i = 0; i < cnt; i++)
    {
        char num, dir;
        int a, b;
        
        cin >> num >> dir >> a >> b;
        
        if(dir == '-')
            signals.push_back({1, {b, a}});
        else
            signals.push_back({0, {b, a}});
    }
    getchar();
}

string solve()
{
    queue<pair<int, pair<int, int>>> q;
    vector<vector<int>> visit(R, vector<int>(C, 0x7fffffff));
    
    visit[sy][sx] = 0;
    q.push({0, {sy, sx}});
    while(!q.empty())
    {
        int t = q.front().first; // 현재 시간
        int y = q.front().second.first;
        int x = q.front().second.second;
        q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];
            
            if(!range(ny, nx)) continue;
            if(map[ny][nx] == '.') continue;
            if(map[ny][nx] == 'A') continue;
            if(map[ny][nx] == 'B') return to_string(t+1);
            if(map[ny][nx] == '#')
            {
                if(visit[ny][nx] <= t+1) continue;
                
                visit[ny][nx] = t+1;
                q.push({t+1, {ny, nx}});
                continue;
            }
            
            int idx = map[ny][nx]-'0';
            int pri = signals[idx].first;
            int sn = signals[idx].second[0];
            int ew = signals[idx].second[1];
            int cur = t%(sn+ew);
            
            if(i % 2 == 0) // 남 북
            {
                if(pri == 0 && cur < sn)
                {
                    if(visit[ny][nx] <= t+1) continue;
                    
                    visit[ny][nx] = t+1;
                    q.push({t+1, {ny, nx}});
                }
                else if(pri == 1 && cur >= ew)
                {
                    if(visit[ny][nx] <= t+1) continue;
                    
                    visit[ny][nx] = t+1;
                    q.push({t+1, {ny, nx}});
                }
                else
                {
                    if(visit[ny][nx] <= t+1) continue;

                    visit[y][x]++;
                    q.push({t+1, {y, x}});
                }
            }
            else // 동 서
            {
                if(pri == 0 && cur >= sn)
                {
                    if(visit[ny][nx] <= t+1) continue;
                    
                    visit[ny][nx] = t+1;
                    q.push({t+1, {ny, nx}});
                }
                else if(pri == 1 && cur < ew)
                {
                    if(visit[ny][nx] <= t+1) continue;
                    
                    visit[ny][nx] = t+1;
                    q.push({t+1, {ny, nx}});
                }
                else
                {
                    if(visit[ny][nx] <= t+1) continue;

                    visit[y][x]++;
                    q.push({t+1, {y, x}});
                }
            }
        }
    }
    
    return "impossible";
}

int main(int argc, char* argv[])
{
    while(true)
    {
        input();
        cout << solve() << endl;
    }
    
    return 0;
}
