#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N, K;
vector<ll> bags;
vector<pair<ll, ll>> v;

bool comp(const pair<ll, ll>& p1, const pair<ll, ll>& p2)
{
    if(p1.first == p2.first)
        return p1.second > p2.second;
    return p1.first < p2.first;
}

int main(int argc, char* argv[])
{
    int idx = 0;
    ll result = 0;
    priority_queue<ll> pq;

    cin >> N >> K;
    v = vector<pair<ll, ll>>(N);
    bags = vector<ll>(K);

    for(int i = 0; i < N; i++)
    {
        ll weight, value; cin >> weight >> value;
        v[i] = {weight, value};
    }
    for(int i = 0; i < K; i++)
    {
        ll max_weight; cin >> max_weight;
        bags[i] = max_weight;
    }

    // 무게순으로 보석 배치, 무게가 같으면 가치가 비싼 순으로 배치
    sort(v.begin(), v.end(), comp);
    sort(bags.begin(), bags.end());

    for(int i = 0; i < K; i++)
    {
        while(idx < N && v[idx].first <= bags[i])
            pq.push(v[idx++].second);

        if(pq.empty()) continue;

        result += pq.top();
        pq.pop();
    }

    cout << result << endl;
    return 0;
}
