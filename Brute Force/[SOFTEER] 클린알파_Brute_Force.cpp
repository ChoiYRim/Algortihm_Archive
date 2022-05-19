#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll MOD = 1000000007;

int P, N;
vector<int> v;

void input()
{
    cin >> P >> N;
    v = vector<int>(N+1, 0);
    for(int i = 1; i <= N; i++) cin >> v[i];
}

ll solve()
{
    ll ans = 0, cur = 1;

    for(int i = N; i > 0; i--)
    {
        ans += (cur*v[i])%MOD;
        ans %= MOD;
        cur *= P;
        cur %= MOD;
    }

    return ans%MOD;
}

int main(int argc, char** argv)
{
    input();
    cout << solve() << endl;
    return 0;
}
