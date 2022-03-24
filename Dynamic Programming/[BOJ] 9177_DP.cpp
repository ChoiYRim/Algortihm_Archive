#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int n;
vector<vector<string>> Data;
string str1,str2,result;
vector<vector<int>> dp;

void input()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        string a,b,c; cin >> a >> b >> c;
        Data.push_back({a,b,c});
    }
}

int dfs(int i,int j,int k)
{
    if(k == result.length())
        return 1;
    if(dp[i][j] != -1)
        return dp[i][j];
    
    dp[i][j] = 0;
    if(i < str1.length() && str1[i] == result[k])
        dp[i][j] = dfs(i+1,j,k+1);
    if(j < str2.length() && str2[j] == result[k])
        dp[i][j] = max(dp[i][j],dfs(i,j+1,k+1));
    
    return dp[i][j];
}

void solve()
{
    for(int i = 0; i < Data.size(); i++)
    {
        str1 = Data[i][0];
        str2 = Data[i][1];
        result = Data[i][2];
        dp = vector<vector<int>>(str1.length()+1,vector<int>(str2.length()+1,-1));
        
        cout << "Data set " << i+1 << ": ";
        if(dfs(0,0,0)) cout << "yes\n";
        else cout << "no\n";
    }
}

int main(int argc,char* argv[])
{
    input();
    solve();
    return 0;
}
