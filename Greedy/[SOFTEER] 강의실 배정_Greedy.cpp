#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll MAX = 1000000000;

int N;
vector<pair<ll, ll>> v;

inline bool comp(const pair<ll, ll>& p1, const pair<ll, ll>& p2)
{
    return p1.second == p2.second ? p1.first < p2.first : p1.second < p2.second;
}

void print()
{
    printf("[TEST PRINT]\n");
    for(const auto& c : v)
    {
        printf("\t[%lld ~ %lld] : %lld\n", c.first, c.second, c.second-c.first);
    }
}

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        ll from, to, diff;
        cin >> from >> to;
        v.push_back({from, to});
    }

    sort(v.begin(), v.end(), comp);
    //print();
}

int solve()
{
    int cnt = 0;

    for(int i = 0; i < v.size(); i++)
    {
        int end_time = v[i].second, idx = i;

        cnt++;
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[j].first >= end_time)
            {
                idx = j;
                break;
            }
        }
        if(idx == i) break;

        i = idx-1;
    }

    return cnt;
}

int main(int argc, char** argv)
{
    input();
    cout << solve() << endl;
    return 0;
}
