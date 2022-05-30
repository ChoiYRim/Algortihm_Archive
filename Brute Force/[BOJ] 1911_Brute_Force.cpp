#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, L;
vector<pair<int, int>> v;

void input()
{
    scanf("%d%d", &N, &L);
    for(int i = 0; i < N; i++)
    {
        int from, to;
        scanf("%d%d", &from, &to);
        v.push_back({from, to});
    }
    sort(v.begin(), v.end());
}

int solve()
{
    if(v.size() <= 0) return 0;
    
    int cnt = 0, cur, diff;
    
    diff = v[0].second-v[0].first;
    cnt = (diff%L ? diff/L+1 : diff/L);
    cur = v[0].first+cnt*L;
    for(int i = 1; i < N; i++)
    {
        int from = v[i].first;
        int to   = v[i].second;
        int tmp;
        
        if(cur >= to) continue;
        
        if(cur < from)
        {
            diff = to-from;
            tmp = (diff%L ? diff/L+1 : diff/L);
            cnt += tmp;
            cur = from+tmp*L;
            continue;
        }
        
        diff = to-cur;
        tmp = (diff%L ? diff/L+1 : diff/L);
        cnt += tmp;
        cur = cur+tmp*L;
    }
    
    return cnt;
}

int main(int argc, char* argv[])
{
    input();
    printf("%d\n", solve());
    return 0;
}
