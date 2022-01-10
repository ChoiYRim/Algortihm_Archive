#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
 
int N;
int a[128][128];
int Min,Max,visit[128][128];
int di[4] = {-1,0,1,0};
int dj[4] = {0,1,0,-1};

inline bool range(int r,int c) { return ((r >= 0 && r < N) && (c >= 0 && c < N)); }
 
bool dfs(int i,int j)
{
    if(i == N-1 && j == N-1)
        return true;
    
    visit[i][j] = 1;
    for(int d = 0; d < 4; d++)
    {
        int row = i+di[d];
        int col = j+dj[d];
        
        if(!range(row,col))
            continue;
        if(visit[row][col] || a[row][col] < Min || a[row][col] > Max)
            continue;
        if(dfs(row,col))
            return true;
    }
    
    return false;
}

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    Min = 0;
    Max = 200;
    
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> a[i][j];
            Min = min(Min,a[i][j]);
            Max = max(Max,a[i][j]);
        }
    }
}
 
int main()
{
    input();
    
    int result = Max-Min;
    int until = Max;
    
    Max = a[0][0];
    
    while(Min <= a[0][0] && Max <= until)
    {
        memset((int *)visit,0,sizeof(visit));
        
        if(dfs(0,0))
        {
            result = min(result,Max-Min);
            Min++;
        }
        else
            Max++;
    }
    
    cout << result << endl;
    return 0;
}
