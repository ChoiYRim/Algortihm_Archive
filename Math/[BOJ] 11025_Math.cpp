#include <iostream>

using namespace std;

int N,K;

int main()
{
    int ans = 0;
    
    cin >> N >> K;
    for(int n = 1; n <= N; n++)
    {
        ans = (ans + K) % n;
    }
    
    cout << ans+1 << '\n';
    return 0;
}
