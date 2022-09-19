#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int INF = 987654321;

int N;
int dp[61][61][61];
int scv[3]={ 0, };

int dfs(int x, int y, int z)
{
    // 파괴된 SCV가 있을 경우
    if(x < 0)return dfs(0, y, z);
    if(y < 0)return dfs(x, 0, z);
    if(z < 0)return dfs(x, y, 0);
    
    // 모든 SCV가 파괴된 경우
    if(x == 0 && y == 0 && z == 0) return 0;
    
    int& ref = dp[x][y][z];

    //이미 구해둔 값이면
    if(ref != -1) return ref;

    ref = INF;
    ref = min(ref, dfs(x-9, y-3, z-1) + 1);
    ref = min(ref, dfs(x-9, y-1, z-3) + 1);
    ref = min(ref, dfs(x-3, y-9, z-1) + 1);
    ref = min(ref, dfs(x-1, y-9, z-3) + 1);
    ref = min(ref, dfs(x-3, y-1, z-9) + 1);
    ref = min(ref, dfs(x-1, y-3, z-9) + 1);

    return ref;
}

int main()
{
    cin >> N;
    
    memset(dp, -1, sizeof(dp));
    
    for(int i = 0; i < N; i++)
    {
        cin >> scv[i];
    }
    
    cout << dfs(scv[0], scv[1], scv[2]) << endl;
    return 0;
}
