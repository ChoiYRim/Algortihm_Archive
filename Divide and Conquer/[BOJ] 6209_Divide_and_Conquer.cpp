#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int d, n, m;
vector<int> rocks;

void input()
{
    cin >> d >> n >> m;
    for(int i = 0; i < n; i++)
    {
        int tmp; cin >> tmp;
        rocks.push_back(tmp);
    }
    
    rocks.push_back(0);
    rocks.push_back(d);
    sort(rocks.begin(), rocks.end());
}

int solve()
{
    int answer = 0;
    int left = 0, right = d, mid; // mid값이 최소거리
    
    while(left <= right)
    {
        int cnt = 0, idx = 0;
        
        mid = (left+right)/2;
        for(int i = 1; i < rocks.size(); i++)
        {
            if(rocks[i]-rocks[idx] < mid) { cnt++; continue; }
            idx = i;
        }
        
        if(cnt > m) { right = mid-1; continue; } // 최소거리로 건너 뛸 수 있는 개수가 m보다 크면 right 갱신
        
        left = mid+1;
        answer = mid;
    }
    
    return answer;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
