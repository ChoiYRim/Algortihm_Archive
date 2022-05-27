#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, int>> v;
priority_queue<int, vector<int>, greater<int>> pq;

int main(int argc, char* argv[])
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int from, to; cin >> from >> to;
        v.push_back({from, to});
    }
    
    sort(v.begin(), v.end());
    pq.push(v[0].second);
    
    for(int i = 1; i < N; i++)
    {
        if(pq.top() <= v[i].first)
        {
            pq.pop();
            pq.push(v[i].second);
            continue;
        }
        
        pq.push(v[i].second);
    }
    
    cout << pq.size() << endl;
    return 0;
}
