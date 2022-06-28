#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll INF = 1000000000;

ll N, M;
vector<ll> trees, sum;

void input()
{
    cin >> N >> M;
    sum = vector<ll>(N+1);
    trees = vector<ll>(N);
    for(int i = 0; i < N; i++) cin >> trees[i];
    sort(trees.begin(), trees.end());
    for(int i = 1; i <= N; i++)
        sum[i] = sum[i-1]+trees[i-1];
}

ll solve()
{
    ll height = 0, ans = 0;
    ll left = 0, right = INF;
    
    while(left <= right)
    {
        height = (left+right)/2;
        auto it = lower_bound(trees.begin(), trees.end(), height);
        int idx = static_cast<int>(it-trees.begin());
        ll total = sum[N]-sum[idx]-((N-idx)*height);
        
        if(total < M)
            right = height-1;
        else if(total >= M)
        {
            left = height+1;
            ans = max(ans, height);
        }
    }
    
    return ans;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
