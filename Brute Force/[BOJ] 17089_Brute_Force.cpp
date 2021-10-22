#include <iostream>

#define INF 987654321

using namespace std;

int N,M;
bool friends[4001][4001] = {0,};
int cnt[4001] = {0,};

int main(void)
{
    int sum = INF;
    
    cin >> N >> M;
    for(int i = 0; i < M; i++)
    {
        int a,b; cin >> a >> b;
        friends[a][b] = true;
        friends[b][a] = true;
        cnt[a]++; cnt[b]++;
    }
    if(M < 3)
    {
        cout << -1 << '\n';
        return 0;
    }
    
    for(int i = 1; i <= N-2; i++)
    {
        for(int j = i+1; j <= N-1; j++)
        {
            if(!friends[i][j] || !friends[j][i])
                continue;
            
            for(int k = j+1; k <= N; k++)
            {
                if((!friends[i][k] || !friends[k][i]) || (!friends[j][k] || !friends[k][j]))
                    continue;
                
                int A = cnt[i]-2,B = cnt[j]-2,C = cnt[k]-2;
                
                if(sum > A+B+C)
                    sum = A+B+C;
            }
        }
    }
    
    cout << (sum != INF ? sum : -1) << '\n';
    return 0;
}
