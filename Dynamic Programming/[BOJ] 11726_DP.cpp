#include <iostream>

using namespace std;

int N;
int dp[1024];

int main(int argc,char* argv[])
{
    cin >> N;
    dp[0] = 0; dp[1] = 1; dp[2] = 2;
    for(int i = 3; i <= N; i++)
    {
        dp[i] = dp[i-1]+dp[i-2];
        dp[i] %= 10007;
    }
    
    cout << dp[N] << '\n';
    return 0;
}
