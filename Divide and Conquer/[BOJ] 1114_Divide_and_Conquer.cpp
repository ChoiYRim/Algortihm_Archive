#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int L, K, C;
vector<int> v;

void input()
{
    cin >> L >> K >> C;
    v = vector<int>(K);
    for(int i = 0; i < K; i++) cin >> v[i];
    sort(v.begin(), v.end());
}

int get_cutting_point(int cutting_length)
{
    int last_point = L, cnt = 0;
    int minimum_cutting_point = 0;
    
    for(int i = K-1; i >= 0; i--)
    {
        if(last_point-v[i] > cutting_length)
        {
            if(i == K-1)
                return 0;
            
            last_point = v[i+1];
            if(last_point-v[i] > cutting_length)
                return 0;
            cnt++;
            minimum_cutting_point = v[i+1];
        }
        if(cnt >= C)
            break;
    }
    if(cnt < C)
        minimum_cutting_point = v[0];
    if(minimum_cutting_point > cutting_length)
        return 0;
    return minimum_cutting_point;
}

pair<int, int> solve()
{
    int left = 1, right = L;
    int mid, len, minimum_cutting_point = L;
    
    while(left <= right)
    {
        mid = (left+right)/2;
        int cutting_point = get_cutting_point(mid);
        
        if(cutting_point != 0)
        {
            len = mid;
            minimum_cutting_point = cutting_point;
            right = mid-1;
        }
        else
        {
            left = mid+1;
        }
    }
    
    return make_pair(len, minimum_cutting_point);
}

int main(int argc, char* argv[])
{
    input();
    
    auto answer = solve();
    cout << answer.first << " " << answer.second << endl;
    return 0;
}
