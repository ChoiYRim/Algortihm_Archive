#include <vector>
#include <iostream>

using namespace std;
using ll = long long;

int N;
vector<ll> dp;

void input()
{
    cin >> N;
    //for(int i = 0; i < N; i++) cin >> v[i];
}

int solve()
{
    dp.push_back(0);
    for(int i = 0; i < N; i++)
    {
        ll num; cin >> num;

        if(num > dp.back())
        {
            dp.push_back(num);
            continue;
        }

        auto it = lower_bound(dp.begin(), dp.end(), num);
        *it = num;
    }

    return static_cast<int>(dp.size()-1);
}

int main(int argc, char** argv)
{
    input();
    cout << solve() << endl;
    return 0;
}
