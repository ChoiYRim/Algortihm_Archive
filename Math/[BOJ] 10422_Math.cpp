#include <iostream>

using namespace std;

typedef long long ll;

int T,L;
const int kMod = 1000000007;

/*
 Catalan Number : C(n+1) = for(i : 0~n) C(i) * C(n-i)
*/

ll dp[5001] = {0,};

void make_dp()
{
    dp[0] = 1;
    for(int i = 2; i <= 5000; i += 2)
    {
        for(int j = 0; j <= i-2; j += 2)
        {
            dp[i] += (dp[j]*dp[i-2-j]);
            dp[i] %= kMod;
        }
    }
}

int main()
{
    cin >> T;
    make_dp();
    while(T--)
    {
        cin >> L;
        cout << dp[L] << '\n';
    }
    
    return 0;
}
