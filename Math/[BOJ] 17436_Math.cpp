#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using ll = long long;

ll N, M, ans;
vector<int> primes;

void input()
{
    cin >> N >> M;
    primes.resize(N);
    for(int i = 0; i < N; i++)
        cin >> primes[i];
}

void solve(int idx, int h1, int h2 = 0, ll mul = 1)
{
    if(h2 >= h1)
    {
        ll sign = h1%2 ? 1 : -1;
        ans += sign*(M/mul);
        return;
    }
    for(int i = idx; i < N; i++)
    {
        solve(i+1, h1, h2+1, mul*primes[i]);
    }
}

int main(int argc, char* argv[])
{
    ans = 0;
    
    input();
    for(int i = 0; i < N; i++) solve(0, i+1);
    
    cout << ans << endl;
    return 0;
}
