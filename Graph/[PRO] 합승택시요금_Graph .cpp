#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    A : 택시비 절약 고민, B와 비슷한 방향으로 종종 택시 탑승

    [ 택시비 합 : X + Y + Z ]
        
    1. X : A와 B가 동승할 때의 비용
    2. Y : A와 B가 동승이 끝나는 지점부터 A집까지 비용
    3. Z : " B집까지 비용
    
    Floyd-Warshall : 모든 서로 다른 두 점 A,B의 최소 거리를 설정해줌
*/

void debugging(int n,vector<vector<int>>& dp,const int& kMax)
{
    printf("동적계획법 배열\n");
    for(int i = 1; i <= n; i++)
    {
        printf("정점 %d : ", i);
        for(int j = 1; j <= n; j++)
        {
            if(i == j) continue;
            if(dp[i][j] >= kMax) continue;
            
            printf("[%d:%d] ", j, dp[i][j]);
        }
        printf("\n");
    }
}

void make_graph(int n,vector<vector<int>>& dp,const vector<vector<int>>& fares)
{
    for(int i = 1; i <= n; i++)
        dp[i][i] = 0;
    
    for(const auto& fare : fares)
    {
        int from = fare[0];
        int to   = fare[1];
        int cost = fare[2];
        
        dp[from][to] = cost;
        dp[to][from] = cost;
    }
}

int solve(int n,int s,int a,int b,vector<vector<int>>& fares)
{
    const int kMax = 0x7fffffff;
    vector<vector<int>> dp(n+1,vector<int>(n+1,kMax));
    
    // 그래프 만들기
    make_graph(n,dp,fares);
        
    // Floyd Warshall
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++) // from i
        {
            for(int j = 1; j <= n; j++) // to j
            {
                if(i == j || i == k || j == k) continue;

                if(dp[i][k] != kMax && dp[k][j] != kMax)
                    dp[i][j] = min(dp[i][j],dp[i][k]+dp[k][j]);
            }
        }
    }
    
    //debugging(n,dp,kMax);
    
    /*
        S에서 A,B까지 도달하는데 존재할 수 있는 경우의 수 (둘이 나뉘는 지점을 X라 하자)
        
        1. S -> X + X -> A + X ->B // X까지 같이 가고 X에서 각자 A,B로 직행
        
        2. S -> A + A -> B
        
        3. S -> B + B -> A
        
        4. S -> A + S -> B
    
    */
    
    int mini = dp[s][a]+dp[s][b];
    for(int i = 1; i <= n; i++) // 둘이 나뉘는 지점 i
    {
        if(dp[s][i] != kMax && dp[i][a] != kMax && dp[i][b] != kMax)
            mini = min(mini,dp[s][i]+dp[i][a]+dp[i][b]);
    }
    
    return mini;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares)
{
    return solve(n,s,a,b,fares);
}

int main(int argc,char* argv[])
{
    cout << solution(6,4,6,2,{{4,1,10},{3,5,24},{5,6,2},{3,1,41},{5,1,24},{4,6,50},{2,4,66},{2,3,22},{1,6,25}}) << endl;
    return 0;
}
