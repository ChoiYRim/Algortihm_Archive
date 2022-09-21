#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 10001;
int N, mday = 0;
vector<vector<int>> v(MAX);

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int p, d; cin >> p >> d;
        v[d].push_back(p);
        mday = max(mday, d);
    }
}

int solve()
{
    int result = 0;
    priority_queue<int> pq;
    
    for(int i = mday; i > 0; i--)
    {
        for(auto& ele : v[i]) pq.push(ele);
        if(!pq.empty())
        {
            result += pq.top();
            pq.pop();
        }
    }
    
    return result;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
