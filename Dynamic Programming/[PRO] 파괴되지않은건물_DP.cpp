#include <string>
#include <vector>
#include <iostream>

using namespace std;

int n,m;
int dp[1024][1024];

void print_dp()
{
    printf("DP\n");
    for(int y = 0; y < n+2; y++)
    {
        for(int x = 0; x < m+2; x++)
        {
            printf("%3d ", dp[y][x]);
        }
        printf("\n");
    }
}

void get_delta(const vector<vector<int>>& skill)
{
    for(const auto& ele : skill)
    {
        int type = ele[0];
        int r1 = ele[1],c1 = ele[2];
        int r2 = ele[3],c2 = ele[4];
        int degree = ele[5];
        
        if(type == 1)
            degree = -degree;
        
        dp[r1][c1] += degree;
        dp[r1][c2+1] -= degree;
        dp[r2+1][c1] -= degree;
        dp[r2+1][c2+1] += degree;
    }
}

void get_sum()
{
    // 위에서 아래로 누적합
    for(int x = 0; x < m; x++)
    {
        int cur = dp[0][x];
        for(int y = 1; y < n; y++)
        {
            dp[y][x] += cur;
            cur = dp[y][x];
        }
    }
    
    // 왼쪽에서 오른쪽으로 누적합
    for(int y = 0; y < n; y++)
    {
        int cur = dp[y][0];
        for(int x = 1; x < m; x++)
        {
            dp[y][x] += cur;
            cur = dp[y][x];
        }
    }
}

int get_result(vector<vector<int>>& board)
{
    int result = 0;
    
    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < m; x++)
        {
            board[y][x] += dp[y][x];
            if(board[y][x] > 0)
                result++;
        }
    }
    
    return result;
}

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    n = static_cast<int>(board.size());
    m = static_cast<int>(board[0].size());
    
    get_delta(skill); // 변화량 구하기
    
    get_sum();
        
    return get_result(board);
}

int main(int argc,char* argv[])
{
    cout << solution({{1,2,3},{4,5,6},{7,8,9}},{{1,1,1,2,2,4},{1,0,0,1,1,2},{2,2,0,2,0,100}}) << endl;
    return 0;
}
