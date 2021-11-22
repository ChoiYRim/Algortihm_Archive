#include <iostream>

using namespace std;

int T,N,ans;

void DFS(int cur)
{
    if(cur == N)
    {
        ans++;
        return;
    }
    if(cur > N)
        return;
    
    for(int i = 1; i <= 3; i++)
    {
        cur += i;
        DFS(cur);
        cur -= i;
    }
}

int main()
{
    cin >> T;
    while(T--)
    {
        ans = 0;
        cin >> N;
        DFS(0);
        cout << ans << '\n';
    }
    
    return 0;
}
