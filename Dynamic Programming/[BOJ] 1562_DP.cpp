#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll MOD = 1000000000;

ll N, ans = 0;
ll dp[101][10][1<<10] = {0,};

int main(int argc, char* argv[])
{
    cin >> N;
    if(N >= 1 && N < 10)
    {
        cout << 0 << endl;
        return 0;
    }
//    else if(N == 10)
//    {
//        cout << 1 << endl;
//        return 0;
//    }
    
    int satisfied = (1<<10)-1;
    for(int i = 1; i < 10; i++)
        dp[1][i][1<<i] = 1;
    for(int n = 2; n <= N; n++)
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j <= satisfied; j++)
            {
                ll& ele = dp[n][i][j|(1<<i)];
                
                if(i == 0)
                {
                    ele += dp[n-1][i+1][j];
                    ele %= MOD;
                }
                else if(i == 9)
                {
                    ele += dp[n-1][i-1][j];
                    ele %= MOD;
                }
                else
                {
                    ele += dp[n-1][i-1][j];
                    ele %= MOD;
                    
                    ele += dp[n-1][i+1][j];
                    ele %= MOD;
                }
            }
        }
    }
    
    for(int i = 0; i < 10; i++)
        ans = (ans+dp[N][i][satisfied])%MOD;
    
    cout << ans%MOD << endl;
    return 0;
}
