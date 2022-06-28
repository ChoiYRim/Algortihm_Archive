#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll INF = 2000000001;

ll N;
vector<ll> liquid;

void input()
{
    cin >> N;
    liquid = vector<ll>(N);
    for(int i = 0; i < N; i++) cin >> liquid[i];
    sort(liquid.begin(), liquid.end());
}

pair<ll, ll> solve()
{
    ll result = INF, add;
    size_t left = 0, right = N-1,l = 0,r = N-1;
    
    while(left < right)
    {
        add = liquid[right]+liquid[left];
        ll abs_add = abs(add);
        ll abs_result = abs(result);
        
        if(add > 0)
        {
            if(abs_result > abs_add)
            {
                result = add;
                l = left;
                r = right;
            }
            if(right-1 != left) right--;
            else break;
        }
        else if(add < 0)
        {
            if(abs_result > abs_add)
            {
                result = add;
                l = left;
                r = right;
            }
            if(left+1 != right) left++;
            else break;
        }
        else
        {
            l = left;
            r = right;
            break;
        }
    }
    
    return {liquid[l], liquid[r]};
}

int main(int argc, char* argv[])
{
    input();
    auto result = solve();
    cout << result.first << " " << result.second << endl;
    return 0;
}
