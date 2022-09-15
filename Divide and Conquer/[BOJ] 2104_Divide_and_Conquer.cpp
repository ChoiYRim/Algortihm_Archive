#include <vector>
#include <climits>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N;
int h, s; // height, size
vector<ll> sum;
vector<ll> v, m_idx;

ll init(int idx, int left, int right)
{
    if(left == right) return sum[idx] = v[left];

    int mid = (left+right)/2;
    ll lr = init(idx*2, left, mid);
    ll rr = init(idx*2+1, mid+1, right);

    return sum[idx] = lr+rr;
}

ll init_idx(int idx, int left, int right)
{
    if(left == right) return m_idx[idx] = left;

    int mid = (left+right)/2;
    ll lr = init_idx(idx*2, left, mid);
    ll rr = init_idx(idx*2+1, mid+1, right);

    if(v[lr] < v[rr]) m_idx[idx] = lr;
    else m_idx[idx] = rr;

    return m_idx[idx];
}

ll find(int idx, ll left, ll right, ll from, ll to)
{
    if(left > to || right < from) return 0;
    else if(left >= from && right <= to) return sum[idx];

    ll mid = (left+right)/2;
    ll lr = find(idx*2, left, mid, from, to);
    ll rr = find(idx*2+1, mid+1, right, from, to);

    return lr+rr;
}

ll find_idx(int idx, ll left, ll right, ll from, ll to)
{
    if(left > to || right < from) return -1;
    else if(left >= from && right <= to) return m_idx[idx];

    ll mid = (left+right)/2;
    ll lr = find_idx(idx*2, left, mid, from, to);
    ll rr = find_idx(idx*2+1, mid+1, right, from, to);

    if(lr == -1 && rr != -1) return rr;
    else if(lr != -1 && rr == -1) return lr;
    return (v[lr] < v[rr] ? lr : rr);
}

void input()
{
    cin >> N;
    v.push_back(0);
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        v.push_back(tmp);
    }

    h = ceil(log2(N));
    s = (1<<(h+1))+1;
    sum = vector<ll>(s, 0);
    m_idx = vector<ll>(s, 0);

    init(1, 1, N);
    init_idx(1, 1, N);
}

ll solve(ll left, ll right)
{
    if(left == right) return v[left]*v[left];

    ll idx = find_idx(1, 1, N, left, right);
    ll result = v[idx]*find(1, 1, N, left, right);

    if(left < idx) result = max(result, solve(left, idx-1));
    if(right > idx) result = max(result, solve(idx+1, right));

    return result;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve(1, N) << endl;
    return 0;
}
