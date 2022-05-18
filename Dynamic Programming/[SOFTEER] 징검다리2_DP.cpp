#include <vector>
#include <iostream>

using namespace std;
using ll = long long;
const ll MAX = 100000001;

int N;
vector<ll> dp, rdp, Data;
vector<int> v;

void input()
{
    cin >> N;
    v = vector<int>(N, 0);
    Data = vector<ll>(N, 0);
    for(int i = 0; i < N; i++) cin >> Data[i];
}

int solve()
{
    int ans = 0;

    dp.push_back(0);
    for(int i = 0; i < N; i++)
    {
        if(Data[i] > dp.back())
        {
            dp.push_back(Data[i]);
            v[i] = static_cast<int>(dp.size()-1);
            continue;
        }

        auto it = lower_bound(dp.begin(), dp.end(), Data[i]);
        v[i] = static_cast<int>(it-dp.begin());
        *it = Data[i];
    }

    rdp.push_back(0);
    for(int i = N-1; i >= 0; i--)
    {
        if(Data[i] > rdp.back())
        {
            rdp.push_back(Data[i]);
            v[i] += static_cast<int>(rdp.size()-1);
            ans = max(ans, v[i]-1);
            continue;
        }

        auto it = lower_bound(rdp.begin(), rdp.end(), Data[i]);
        v[i] += static_cast<int>(it-rdp.begin());
        ans = max(ans, v[i]-1);
        *it = Data[i];
    }
    
    return ans;
}

int main(int argc, char** argv)
{
    input();
    cout << solve() << endl;
    return 0;
}
