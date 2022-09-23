#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N, K;
vector<ll> v, sum;

int main(int argc, char* argv[])
{
    ll cnt = 0, tmp;
    
    cin >> N;
    v = vector<ll>(N);
    sum = vector<ll>(N);
    cin >> sum[0];
    v[0] = sum[0];
    for(int i = 1; i < N; i++)
    {
        cin >> v[i];
        sum[i] = sum[i-1]+v[i];
    }
    cin >> K;
    
    for(int i = 0; i < N; i++)
    {
        for(int j = N-1; j >= i; j--)
        {
            if(i == j) tmp = v[i];
            else
            {
                if(i > 0) tmp = sum[j]-sum[i-1];
                else tmp = sum[j];
            }
            
            if(tmp > K) cnt++;
            else break;
        }
    }
    
    cout << cnt << endl;
    return 0;
}
