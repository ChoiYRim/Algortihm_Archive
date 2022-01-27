#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int MAX = 10001;

vector<int> dp;

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int N,M,temp;
    cin >> N >> M;
    dp = vector<int>(MAX,0);
    for (int i = 0; i < N; i++)
    {
        int v, c, k; cin >> v >> c >> k;
        int t = 1;
        while (k > 0)
        {
            temp = min(k,t);
            for (int j = M; j >= v*temp; j--)
            {
                dp[j] = max(dp[j-v*temp]+c*temp,dp[j]);
            }
            t *= 2;
            k -= temp;
        }
    }
    
    cout << *max_element(dp.begin(),dp.end()) << endl;
    return 0;
}
