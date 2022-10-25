#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, C;
vector<int> x;

void input()
{
    cin >> N >> C;
    x = vector<int>(N);
    for(int i = 0; i < N; i++) cin >> x[i];
    sort(x.begin(), x.end());
}

bool check(int term)
{
    int cnt = 1;
    int from = x[0];
    
    for(int i = 1; i < N; i++)
    {
        if(x[i]-from >= term)
        {
            from = x[i];
            cnt++;
        }
    }
    
    if(cnt >= C)
        return true;
    return false;
}

int solve()
{
    int result = 0;
    int left = 0, right = x[N-1]-1, mid;
    
    while(left <= right)
    {
        mid = (left+right)/2;
        if(check(mid))
        {
            left = mid+1;
            if(result < mid) result = mid;
        }
        else
            right = mid-1;
    }
    
    return result;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
