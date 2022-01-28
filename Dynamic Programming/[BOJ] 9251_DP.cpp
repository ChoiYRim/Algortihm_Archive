#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string s1 = "";
string s2 = "";
int dp[1024][1024];

int tabulation()
{
    int ans = 0;
    
    for(size_t i = 1; i <= s1.length(); i++)
    {
        for(size_t j = 1; j <= s2.length(); j++)
        {
            if(s1[i-1] != s2[j-1]) // 다르다면
            {
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
            else // 같다면
            {
                dp[i][j] = dp[i-1][j-1]+1;
            }
            
            ans = max(ans,dp[i][j]);
        }
    }
    
    return ans;
}

int main(void)
{
    cin >> s1;
    cin >> s2;
    
    if(!s1.length() || !s2.length())
    {
        cout << 0 << endl;
        return 0;
    }
    
    cout << tabulation() << endl;
    return 0;
}
