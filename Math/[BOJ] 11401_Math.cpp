#include <iostream>

using namespace std;
using ll = long long;

ll N,K,X,Y;
ll mod = 1000000007;

ll divide_conquer(ll p)
{
    if(p == 0)
        return 1;
    if(p % 2)
        return Y*divide_conquer(p-1)%mod;
    
    ll half = divide_conquer(p/2);
    return half*half%mod;
}

int main()
{
    cin >> N >> K;
    X = Y = 1;
    for(ll i = N-K+1; i <= N; i++) // (n! / (n-k)!)
        X = (X * i) % mod;
    for(ll i = 1; i <= K; i++) // k!
        Y = (Y * i) % mod;
    Y = divide_conquer(mod-2);
    
    cout << X * Y % mod << endl;
    return 0;
}
