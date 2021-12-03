#include <queue>
#include <iostream>

using namespace std;

typedef long long ll;

ll A,B;
ll (*fp[2])(ll);
queue<pair<ll,int>> q;

ll f1(ll n) { return n*2; }

ll f2(ll n) { return n*10+1; }

int main()
{
    fp[0] = f1;
    fp[1] = f2;
    
    cin >> A >> B;
    q.push({A,1});
    while(!q.empty())
    {
        ll cur = q.front().first;
        int t = q.front().second;
        q.pop();
        
        if(cur == B)
        {
            cout << t << '\n';
            return 0;
        }
        
        for(int i = 0; i < 2; i++)
        {
            ll next = fp[i](cur);
            
            if(next > B)
                continue;
            
            q.push({next,t+1});
        }
    }
    
    cout << -1 << '\n';
    return 0;
}
