#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

map<ll,ll> m;
int N,K,ans = 0;
vector<pair<ll,ll>> v;

ll gcd(ll a,ll b)
{
    if(b != 0)
        return gcd(b,a%b);
    return a;
}

int main()
{
    cin >> N >> K;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        ll GCD = gcd(K,tmp);
        
        if(m.find(GCD) != m.end())
            m[GCD]++;
        else
            m[GCD] = 1;
    }
    
    for(map<ll,ll>::iterator it = m.begin(); it != m.end(); it++)
        v.push_back(*it);
    
    for(int i = 0; i < (int)v.size(); i++)
    {
        ll fi = v[i].first;
        ll si = v[i].second;
        
        if(si >= 3 && fi*fi*fi % K == 0)
        {
            ans += (si * (si-1) * (si-2) / 6);
        }
    }
    
    for(int i = 0; i < (int)v.size(); i++)
    {
        ll fi = v[i].first;
        ll si = v[i].second;
        
        for(int j = i+1; j < (int)v.size(); j++)
        {
            ll fj = v[j].first;
            ll sj = v[j].second;
                        
            if(sj >= 2 && fj*fj*fi % K == 0)
            {
                ans += (sj * (sj-1) * si / 2);
            }
            if(si >= 2 && fj*fi*fi % K == 0)
            {
                ans += (si * (si-1) * sj / 2);
            }
        }
    }
    
    for(int i = 0; i < (int)v.size(); i++)
    {
        ll fi = v[i].first;
        ll si = v[i].second;
        
        for(int j = i+1; j < (int)v.size(); j++)
        {
            ll fj = v[j].first;
            ll sj = v[j].second;
            
            for(int k = j+1; k < (int)v.size(); k++)
            {
                ll fk = v[k].first;
                ll sk = v[k].second;
                
                if(fi*fj*fk % K == 0)
                {
                    ans += (si*sj*sk);
                }
            }
        }
    }
    
    cout << ans << '\n';
    return 0;
}
