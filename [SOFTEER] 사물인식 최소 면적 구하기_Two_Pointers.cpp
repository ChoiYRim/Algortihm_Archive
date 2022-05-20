#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int MAX = 0x7fffffff;

int N, K;
vector<vector<pair<int, int>>> points;

void dfs(int depth, int min_y, int max_y, int min_x, int max_x, int& ans)
{
    if(depth > K)
    {
        int extent = (max_y-min_y)*(max_x-min_x);
        ans = min(ans, extent);
        return;
    }
    for(int i = 0; i < points[depth].size(); i++)
    {
        int y = points[depth][i].first;
        int x = points[depth][i].second;
        int max_ny = max_y, min_ny = min_y;
        int max_nx = max_x, min_nx = min_x;
        
        if(min_y > y) min_ny = y;
        if(max_y < y) max_ny = y;
        if(min_x > x) min_nx = x;
        if(max_x < x) max_nx = x;
        
        int extent = (max_ny-min_ny)*(max_nx-min_nx);
        
        if(ans <= extent) continue;
        
        dfs(depth+1, min_ny, max_ny, min_nx, max_nx, ans);

    }
}

int main(int argc, char** argv)
{
    int ans = MAX;

    cin >> N >> K;
    points = vector<vector<pair<int, int>>>(K+1);
    for(int i = 0; i < N; i++)
    {
        int y, x, k; cin >> x >> y >> k;
        points[k].push_back({y, x});
    }

    dfs(1, MAX, -MAX, MAX, -MAX, ans);

    cout << ans << endl;
    return 0;
}
