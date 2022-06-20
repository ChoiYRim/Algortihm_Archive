#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

ll N;
vector<ll> v;

void input()
{
    cin >> N;
    v = vector<ll>(N+1);
    for(int i = 1; i <= N; i++) cin >> v[i];
}

ll solve()
{
    ll ans = 0;
    
    sort(v.begin(), v.end());
    for(int i = 1; i <= N; i++)
    {
        ans += abs(i-v[i]);
    }
    
    return ans;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
