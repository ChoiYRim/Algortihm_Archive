#include <iostream>

using namespace std;
using ll = long long;

const int MAX = 1000001;

int T;
ll dp[MAX];
ll s[MAX];

int main()
{
    fill_n(dp, MAX, 1);
    
    for (int i = 2; i < MAX; i++)
    {
        for (int j = 1; i*j < MAX; j++)
        {
                dp[i*j] += i;
        }
    }
    
    for (int i = 1; i < MAX; i++)
        s[i] = s[i - 1] + dp[i];
    
    scanf("%d", &T);
    while (T--)
    {
        int n;
        
        scanf("%d", &n);
        printf("%lld\n", s[n]);
    }
    
    return 0;
}
