#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll N;
vector<ll> dp;

int main()
{
    ll pisano = 1500000; // 피보나치 수를 나눌 수 K = 10^6이므로 피사노 주기는 15*10^(6-1)
    
    cin >> N;
    dp = vector<ll>(pisano,0);
    dp[0] = 0;
    dp[1] = dp[2] = 1;
    for(int i = 3; i < pisano && i <= N; i++)
        dp[i] = (dp[i-1]+dp[i-2]) % 1000000;
    
    if(N >= pisano)
        N %= pisano;
    
    cout << dp[N] << endl;
    return 0;
}
