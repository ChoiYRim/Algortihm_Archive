#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, A, B;
vector<int> distA, distB, needs;
priority_queue<pair<int, int>> pq;

void input()
{
    distA = vector<int>(N);
    distB = vector<int>(N);
    needs = vector<int>(N);
    for(int i = 0; i < N; i++)
    {
        cin >> needs[i] >> distA[i] >> distB[i];
        pq.push({abs(distA[i]-distB[i]), i});
    }
}

int solve()
{
    int ans = 0;
    
    while(!pq.empty())
    {
        int idx = pq.top().second;
        pq.pop();
        
        int& from = (distA[idx] > distB[idx] ? B : A);
        
        if(from)
        {
            int cnt = min(from, needs[idx]);
            from -= cnt;
            needs[idx] -= cnt;
            ans += cnt*min(distA[idx], distB[idx]);
        }
        ans += needs[idx]*max(distA[idx], distB[idx]);
    }
    
    return ans;
}

int main(int argc, char* argv[])
{
    while(1)
    {
        cin >> N >> A >> B;
        
        if(N == 0 && A == 0 && B == 0) return 0;
        
        input();
        cout << solve() << endl;
    }
    
    return 0;
}
