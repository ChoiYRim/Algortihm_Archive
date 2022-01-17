#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int kMax = 0x7fffffff;

int N;
int dp[501][501]; // [x][y] : x~y구간 행렬곱의 연산 최소값
vector<pair<int,int>> mat;

void input()
{
    cin >> N;
    mat = vector<pair<int,int>>(N+1);
    for(int i = 0; i < N; i++)
    {
        int r,c; cin >> r >> c;
        mat[i+1] = {r,c};
    }
}

int solve()
{
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; i + j <= N; j++)
        {
            dp[j][i+j] = kMax;
            for (int k = j; k <= i + j; k++)
            {
                dp[j][i+j] = min(dp[j][i+j],dp[j][k]+dp[k+1][i+j]+mat[j].first*mat[k].second*mat[i+j].second);
            }
        }
    }
    
    return dp[1][N];
}

int main()
{
    input();
    
    cout << solve() << '\n';
    return 0;
}
