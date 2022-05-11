#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

typedef long long ll;

int N;
std::vector<ll> A,B,C,D;
ll AB[16000001];
ll CD[16000001];

void save_sum(const std::vector<ll>& v1,const std::vector<ll>& v2,ll* arr)
{
    int idx = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            ll sum = v1[i]+v2[j];
            arr[idx++] = sum;
        }
    }
}

int main(int argc,char* argv[])
{
    ll ans = 0;
    
    std::cin >> N;
    for(int i = 0; i < N; i++)
    {
        ll a,b,c,d;
        
        std::cin >> a >> b >> c >> d;
        
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
    }
    
    save_sum(A, B, AB);
    save_sum(C, D, CD);
    
    std::sort(AB, AB+N*N);
    std::sort(CD, CD+N*N);
    
    for(int i = 0; i < N*N; i++)
    {
        ll ab = AB[i];
        ll low = std::lower_bound(CD, CD+N*N, -ab)-CD; // -ab 값이 존재하는 가장 빠른 인덱스, 없으면 -ab보다 큰 가장 빠른 인덱스
        ll upp = std::upper_bound(CD, CD+N*N, -ab)-CD; // -ab 값을 초과하는 값들 중에서 가장 빠른 인덱스
        
        if(CD[low] == -ab)
            ans += (upp-low);
    }
    
    std::cout << ans << '\n';
    return 0;
}
