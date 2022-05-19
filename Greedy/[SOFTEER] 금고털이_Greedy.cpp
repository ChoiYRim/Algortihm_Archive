#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int W, N;
vector<pair<int, int>> v;

void input()
{
    cin >> W >> N;
    v = vector<pair<int, int>>(N);
    for(int i = 0; i < N; i++) { int m, p; cin >> m >> p; v[i] = {p, m}; }
}

int solve()
{
    int ans = 0;

    sort(v.begin(), v.end());
    for(int i = N-1; i >= 0; i--)
    {
        int weight = min(v[i].second, W);
        W -= weight;
        ans += weight*v[i].first;
    }

    return ans;
}

int main(int argc, char** argv)
{
    input();
    cout << solve() << endl;
    return 0;
}
