#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<int> v;
vector<pair<int, int>> set;

bool comp(const pair<int, int>& p1, const pair<int, int>& p2)
{
    if(p1.second == p2.second) return p1.first < p2.first;
    return p1.second > p2.second;
}

int main(int argc, char* argv[])
{
    int idx;
    double sum = 0;
    
    cin >> N;
    v = vector<int>(N);
    set = vector<pair<int, int>>(8002);
    for(int i = 0; i < N; i++)
    {
        cin >> v[i];
        sum += v[i];
        
        set[v[i]+4000].first = v[i]+4000;
        set[v[i]+4000].second++;
    }
    
    sort(v.begin(), v.end());
    sort(set.begin(), set.end(), comp);
    
    if(set.size() == 1) idx = set.front().first;
    else
    {
        if(set[0].second == set[1].second) idx = set[1].first;
        else idx = set[0].first;
    }
    
    cout << static_cast<int>(floor((sum/N)+0.5)) << endl;
    cout << v[N/2] << endl;
    cout << idx-4000 << endl;
    cout << abs(v.back()-v.front()) << endl;
    return 0;
}
