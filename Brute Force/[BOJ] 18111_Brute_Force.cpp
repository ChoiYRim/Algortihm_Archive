#include <vector>
#include <iostream>
#include <algorithm>

#define INF 64000000
#define HLIMIT 256
#define LLIMIT 0

using namespace std;

struct Pos
{
    int y;
    int x;
};

long long N,M,B;
long long T = INF;
int height = 0;
vector<Pos> pos[257];

inline int MAX(int a,int b) { return (a > b ? a : b); }

int getLow(int h)
{
    int cnt = 0;
    
    for(int i = h-1; i >= LLIMIT; i--) // low
    {
        if(pos[i].size() > 0)
            cnt += ((h-i)*(int)pos[i].size()); // (높이 차) x (개수)
    }
    
    return cnt;
}

int getHigh(int h)
{
    int cnt = 0;
    
    for(int i = h+1; i <= HLIMIT; i++) // high
    {
        if(pos[i].size() > 0)
            cnt += ((i-h)*(int)pos[i].size()); // (높이 차) x (개수)
    }
    
    return cnt;
}

void solve()
{
    long long b,t;
    
    for(int h = HLIMIT; h >= LLIMIT; h--)
    {
        b = B;
        int low_cnt = getLow(h),high_cnt = getHigh(h);
        
        if(b+high_cnt > INF || b+high_cnt < low_cnt)
            continue;
        
        t = high_cnt * 2 + low_cnt;
        
        if(T > t)
        {
            T = t;
            height = h;
        }
    }
}

int main(int argc,char* argv[])
{
    cin >> N >> M >> B;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            int h; cin >> h;
            pos[h].push_back({i,j});
        }
    }
    
    solve();
    cout << T << " " << height << '\n';
    return 0;
}
