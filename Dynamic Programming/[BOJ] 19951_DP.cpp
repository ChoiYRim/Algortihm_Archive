#include <iostream>
#include <vector>

using namespace std;

int N,M;
vector<int> place,dp;
vector<pair<pair<int,int>,int>> orders;

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int idx = 1;
    
    cin >> N >> M;
    place = vector<int>(N+2,0);
    dp = vector<int>(N+2,0);
    for(int i = 0; i < N; i++)
    {
        int height; cin >> height;
        place[idx++] = height;
    }
    for(int i = 0; i < M; i++)
    {
        int a,b,k; cin >> a >> b >> k;
        orders.push_back({{a,b},k});
    }
}

void solve()
{
    for(const auto& order : orders)
    {
        int from = order.first.first;
        int to = order.first.second;
        int height = order.second;
        
        dp[from] += height;
        dp[to+1] -= height;
    }
    
    int height = dp[1];
    for(int i = 2; i < dp.size(); i++)
    {
        dp[i] += height;
        height = dp[i];
    }
    
    for(int i = 1; i < place.size()-1; i++)
    {
        place[i] += dp[i];
    }
}

void output()
{
    for(int i = 1; i < place.size()-1; i++)
        cout << place[i] << ' ';
    cout << endl;
}

int main(int argc,char* argv[])
{
    input();
    
    solve();
    
    output();
    return 0;
}
