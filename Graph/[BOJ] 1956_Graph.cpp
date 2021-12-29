#include <vector>
#include <iostream>

using namespace std;

int V,E;
int dp[512][512]={0,};

inline int MIN(int a,int b) { return (a > b ? b : a); }

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int ans = 987654321;
    
    cin >> V >> E;
    for(int i = 1; i <= V; i++)
        fill(dp[i], dp[i]+512, 987654321);
    for(int i = 0; i < E; i++)
    {
        int u,v,w; cin >> u >> v >> w;
        dp[u][v] = w;
    }
    
    for(int u = 1; u <= V; u++)
    {
        for(int v = 1; v <= V; v++)
        {
            for(int m = 1; m <= V; m++)
            {
                dp[u][v] = MIN(dp[u][v],dp[u][m]+dp[m][v]);
            }
        }
    }
    
    bool check = false;
    for(int u = 1; u <= V; u++)
    {
        for(int v = 1; v <= V; v++)
        {
            if(u != v)
            {
                if(dp[u][v] < 987654321 && dp[v][u] < 987654321)
                {
                    check = true;
                    ans = MIN(ans,dp[u][v]+dp[v][u]);
                }
            }
        }
    }
    
    if(!check)
        cout << -1 << '\n';
    else
        cout << ans << '\n';
    return 0;
}
