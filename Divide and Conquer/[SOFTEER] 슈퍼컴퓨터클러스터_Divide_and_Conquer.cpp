#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

ll N, B, mini, maxi, result;
vector<ll> computers;

void input()
{
    cin >> N >> B;
    computers = vector<ll>(N, 0);
    for(int i = 0; i < N; i++)
    {
        cin >> computers[i];
    }
    sort(computers.begin(), computers.end());
    mini = computers[0];
    maxi = computers[N-1];
    result = mini;
}

ll solve(ll left, ll right)
{
    if(left > right) return 0;
    if(left == right)
    {
        ll budget = B;
        for(int i = 0; i < N; i++)
        {
            ll diff = (left-computers[i] > 0 ? left-computers[i] : 0);
            budget -= (diff*diff);
            if(budget < 0) break;
        }
        
        return (budget >= 0 ? left : 0);
    }

    ll mid = (left+right)/2;
    ll budget = B;
    for(int i = 0; i < N; i++)
    {
        ll diff = (mid-computers[i] > 0 ? mid-computers[i] : 0);
        budget -= (diff*diff);
        if(budget < 0) break;
    }
    
    if(budget < 0)
        return solve(left, mid);
    return max(mid, solve(mid+1, right));
}

int main(int argc, char** argv)
{
    input();
    cout << solve(1, 2000000000) << endl;
    return 0;
}
