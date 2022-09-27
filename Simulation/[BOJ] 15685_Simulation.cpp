#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<vector<pair<int, int>>> v;
const int dy[4] = {0, -1, 0, 1};
const int dx[4] = {1, 0, -1, 0};
int map[128][128] = {0,};

void make_curve(int idx, int dep, int x, int y, int dir, int gen)
{
    if(dep > gen) return;
    
    if(dep == 0)
    {
        v[idx].push_back({x, y});
        v[idx].push_back({x+dx[dir], y+dy[dir]});
        
        map[x][y]++;
        map[x+dx[dir]][y+dy[dir]]++;
        
        make_curve(idx, dep+1, v[idx].back().first, v[idx].back().second, dir, gen);
        return;
    }
    
    int sz = static_cast<int>(v[idx].size())-1;
    for(int i = sz-1; i >= 0; i--)
    {
        int a = v[idx][i].first-x;
        int b = v[idx][i].second-y;
        
        int na = x-b;
        int nb = y+a;
        
        map[na][nb]++;
        
        v[idx].push_back({na, nb});
    }
    
    make_curve(idx, dep+1, v[idx].back().first, v[idx].back().second, dir, gen);
}

void input()
{
    cin >> N;
    v = vector<vector<pair<int, int>>>(N);
    for(int i = 0; i < N; i++)
    {
        int x, y, dir, gen; cin >> x >> y >> dir >> gen;
        make_curve(i, 0, x, y, dir, gen);
    }
}

int solve()
{
    int cnt = 0;
    
    for(int y = 0; y < 100; y++)
    {
        for(int x = 0; x < 100; x++)
        {
            if(map[x][y] && map[x+1][y] && map[x][y+1] && map[x+1][y+1]) cnt++;
        }
    }
    
    return cnt;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
