#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <set>

using namespace std;
 
int N;
int lo,hi;
int a[51][51],visit[51][51];
int dy[] = {0,0,1,-1,1,1,-1,-1};
int dx[] = {1,-1,0,0,1,-1,1,-1};

pair<int,int> P;
vector<pair<int,int>> K;

inline bool range(int y,int x) { return ((y >= 0 && y < N) && (x >= 0 && x < N)); }
 
void dfs(int y,int x)
{
    if(!range(y,x))
        return;
    if(visit[y][x] || a[y][x] < lo || a[y][x] > hi)
        return;
    
    visit[y][x] = 1;
    for(int d = 0; d < 8; ++d)
        dfs(y+dy[d],x+dx[d]);
}
 
bool possible()
{
    int cnt = 0;
    
    for(int k = 0; k < (int)K.size(); ++k)
        if(visit[K[k].first][K[k].second])
            ++cnt;
    
    return cnt == (int)K.size();
}

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        char t[51]; cin>>t;
        for(int j = 0; j < N; ++j)
        {
            if(t[j]=='P')
                P = {i,j};
            else if(t[j]=='K')
                K.push_back({i,j});
        }
    }
}
 
int main()
{
    input();
    
    set<int> s;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            cin >> a[i][j];
            s.insert(a[i][j]);
        }
    }
    
    int result = 1e6;
    set<int>::iterator l = s.begin(),r = s.begin();
    
    while(r != s.end())
    {
        while(l != s.end())
        {
            memset((int *)visit,0,sizeof(visit));
            lo=*l;hi=*r;
            dfs(P.first,P.second);
            
            if(!possible())
                break;
            
            result = min(result,*r-*l);
            ++l;
        }
        ++r;
    }
    
    cout << result << endl;
}
