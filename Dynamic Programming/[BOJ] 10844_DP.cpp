#include <iostream>

using namespace std;
using ll = long long;
const ll MOD = 1000000000;

int N;
ll dp[101][10] = {0,}; // dp[자리수][맨뒤]

inline int ABS(int x) { return (x > 0 ? x : -x); }

int main()
{
    ll ans = 0;
    
    cin >> N;
    for(int i = 1; i < 10; i++)
        dp[1][i] = 1;
    for(int i = 2; i <= N; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(j == 0)
            {
                dp[i][j] = dp[i-1][j+1]%MOD;
            }
            else if(j == 9)
            {
                dp[i][j] = dp[i-1][j-1]%MOD;
            }
            else
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j+1])%MOD;
        }
    }
    
    for(int i = 0; i < 10; i++)
        ans += dp[N][i]%MOD;
    cout << ans%MOD << endl;
    return 0;
}

