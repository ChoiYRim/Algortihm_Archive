#include <iostream>

using namespace std;

int N,M;
int arr[1026][1026],dp[1026][1026];

int sum(int x1,int y1,int x2,int y2)
{
    if(x1 == 0 && y1 == 0)
        return dp[x2][y2];
    else if(x1 == 0 && y1 != 0)
        return dp[x2][y2]-dp[x2][y1-1];
    else if(x1 != 0 && y1 == 0)
        return dp[x2][y2]-dp[x1-1][y2];
    return dp[x2][y2]-dp[x1-1][y2]-dp[x2][y1-1]+dp[x1-1][y1-1];
}

void print_dp()
{
    cout << "\nDP" << endl;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < N; x++)
        {
            printf("%2d ", dp[y][x]);
        }
        printf("\n");
    }
}

int main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        int num = 0;
        for(int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
            arr[i][j] = arr[i][j]+num;
            num = arr[i][j];
            
            if(i == 0)
                dp[i][j] = arr[i][j];
            else
                dp[i][j] = dp[i-1][j]+arr[i][j];
        }
    }
    
    //print_dp();
    
    for(int i = 0; i < M; i++)
    {
        int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        printf("%d\n", sum(x1-1,y1-1,x2-1,y2-1));
    }
    //print_dp();
    
    return 0;
}
