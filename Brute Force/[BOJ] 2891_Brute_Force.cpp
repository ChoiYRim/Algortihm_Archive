#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, S, R;
vector<int> team;

void input()
{
    cin >> N >> S >> R;
    
    team = vector<int>(N+1, 1);
    for(int i = 0; i < S; i++)
    {
        int idx; cin >> idx;
        team[idx]--;
    }
    for(int i = 0; i < R; i++)
    {
        int idx; cin >> idx;
        team[idx]++;
    }
}

int solve()
{
    int cnt = 0;
    
    for(int i = 1; i <= N; i++)
    {
        if(team[i] == 0)
        {
            cnt++;
            if(i-1 > 0 && team[i-1] > 1) { team[i-1]--; cnt--; continue; }
            if(i+1 <= N && team[i+1] > 1) { team[i+1]--; cnt--; continue; }
        }
    }
    
    return cnt;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
