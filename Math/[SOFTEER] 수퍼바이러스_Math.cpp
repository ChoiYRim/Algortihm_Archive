#include <iostream>

using namespace std;
using ull = unsigned long long;
const long long MOD = 1000000007;

ull K, P, N;

int main(int argc, char** argv)
{
    ull ans = 1, cur = 1;

    cin >> K >> P >> N;
    
    for(int i = 0; i < 10; i++)
    {
        cur *= P;
        cur %= MOD;
    }

    while(N > 0)
    {
        if(N%2) ans = (ans*cur)%MOD;
        
        N /= 2;
        cur = (cur*cur)%MOD;
    }

    ans %= MOD;
    cout << (K*ans)%MOD << endl;
    return 0;
}
