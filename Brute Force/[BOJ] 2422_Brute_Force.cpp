#include <vector>
#include <iostream>

using namespace std;

int N,M,ans = 0;
bool v[201][201] = {0,};

int main(int argc,char* argv[])
{
    cin >> N >> M;
    for(int i = 0; i < M; i++)
    {
        int a,b; cin >> a >> b;
        if(a > b)
            swap(a,b);
        v[a][b] = true;
    }
    
    for(int i = 1; i <= N-2; i++)
    {
        for(int j = i+1; j <= N-1; j++)
        {
            if(v[i][j])
                continue;
            
            for(int k = j+1; k <= N; k++)
            {
                if(v[i][k] || v[j][k])
                    continue;
                ans++;
            }
        }
    }
    
    cout << ans << '\n';
    return 0;
}
