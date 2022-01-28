#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string s1 = "";
string s2 = "";
vector<vector<int>> dp;

int tabulation()
{
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
        }
    }
    
    return dp[s1.length()][s2.length()];
}

int memoization(size_t i,size_t j)
{
    if(dp[i][j] != 0)
        return dp[i][j];
    if(i >= s1.length() || j >= s2.length())
        return 0;
    
    if(s1[i] != s2[j])
        dp[i][j] = max(memoization(i+1,j),memoization(i,j+1));
    else
        dp[i][j] = memoization(i+1,j+1)+1;
    
    return dp[i][j];
}

void print()
{
    for(auto i = 0; i < s1.length()+1; i++)
    {
        for(auto j = 0; j < s2.length()+1; j++)
            cout << dp[i][j] << ' ';
        cout << endl;
    }
}

int main(void)
{
    int ans = 0;
    
    cin >> s1;
    cin >> s2;
    if(!s1.length() || !s2.length())
    {
        cout << 0 << endl;
        return 0;
    }
    
    dp = vector<vector<int>>(s1.length()+1,vector<int>(s2.length()+1,0));
    //cout << memoization(0,0) << endl;
    
    ans = tabulation();
    cout << ans << endl;
    if(!ans)
        return 0;
    
    size_t i = s1.length();
    size_t j = s2.length();
    string result = "";
    while(dp[i][j] != 0)
    {
        if(dp[i][j] == dp[i-1][j])
            i--;
        else if(dp[i][j] == dp[i][j-1])
            j--;
        else
        {
            result = s1[i-1]+result;
            i--; j--;
        }
    }
    
    cout << result << endl;
    return 0;
}
