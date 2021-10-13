#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int N;
ll dp[1024] = {0,};

int main(int argc,char* argv[])
{
    const ll kMod = 10007;

    cin >> N;
    
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 3;
    for(int i = 3; i <= N; i++)
    {
        dp[i] = dp[i-1]+dp[i-2]*2;
        dp[i] %= kMod;
    }
    
    cout << dp[N]%kMod << '\n';
    return 0;
}
