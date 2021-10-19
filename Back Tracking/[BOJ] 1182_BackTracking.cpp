#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

ll S;
int N,ans = 0;
vector<int> v;
bool visit[32] = {0,};

void DFS(ll cur,int cnt,int depth)
{
    if(cnt <= 0)
    {
        if(cur != S)
            return;
        ans++;
        return;
    }
    
    for(int i = depth; i < N; i++)
    {
        if(!visit[i])
        {
            visit[i] = true;
            DFS(cur+v[i],cnt-1,i);
            visit[i] = false;
        }
    }
}

int main(int argc,char* argv[])
{
    cin >> N >> S;
    for(int i = 0; i < N; i++)
    {
        int tmp; cin >> tmp;
        v.push_back(tmp);
    }
    
    for(int i = 1; i <= N; i++)
    {
        DFS(0,i,0);
    }
    
    cout << ans << '\n';
    return 0;
}
