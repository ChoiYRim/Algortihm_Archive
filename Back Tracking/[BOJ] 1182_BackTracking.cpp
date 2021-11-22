#include <iostream>

using namespace std;

int N,S,ans = 0;
int num[32] = {0,};
int visit[32] = {0,};

void DFS(int idx,int sum,int cnt)
{
    if(!cnt)
    {
        if(sum == S)
            ans++;
        return;
    }
    
    for(int i = idx; i < N; i++)
    {
        if(!visit[i])
        {
            visit[i] = 1;
            sum += num[i];
            DFS(i+1,sum,cnt-1);
            sum -= num[i];
            visit[i] = 0;
        }
    }
}

int main()
{
    cin >> N >> S;
    for(int i = 0; i < N; i++)
        cin >> num[i];
    
    for(int cnt = 1; cnt <= N; cnt++)
        DFS(0,0,cnt);
    
    cout << ans << '\n';
    return 0;
}
