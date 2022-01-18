#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

const int kMax = 987654321;

int T,N;
vector<pair<int,vector<int>>> test;

void input()
{
    cin >> T;
    
    while(T--)
    {
        cin >> N;
        std::vector<int> input(N+1);

        for(int i = 0; i < N; i++)
        {
            int tmp; cin >> tmp;
            input[i+1] = tmp;
        }
        
        test.push_back({N,input});
    }
}

void print(int n,int arr[501][501])
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(arr[i][j] == kMax)
                printf("%-3d ", 0);
            else
                printf("%-3d ", arr[i][j]);
        }
        printf("\n");
    }
}

vector<int> solve()
{
    vector<int> result;
    
    for(size_t i = 0; i < test.size(); i++)
    {
        int sum[501] = {0,},dp[501][501] = {0,};
        N = test[i].first;
        vector<int> files = test[i].second;
                
        for(size_t j = 1; j <= N; j++)
        {
            sum[j] = sum[j-1]+files[j]; // sum = [0,40,70,100,150]
        }
        
        for(size_t count = 1; count < N; count++) // 개수
        {
            for(size_t start = 1; start+count <= N; start++) // 시작 인덱스
            {
                size_t end = start+count;
                dp[start][end] = kMax;
                for(size_t mid = start; mid < end; mid++)
                {
                    dp[start][end] = min(dp[start][end],dp[start][mid]+dp[mid+1][end]+sum[end]-sum[start-1]);
                }
            }
        }
        
        result.emplace_back(dp[1][N]);
    }
    
    return result;
}

void output(const vector<int>& result)
{
    for(auto i : result)
        cout << i << '\n';
}

int main()
{
    input();
    vector<int> result = solve();
    output(result);
    return 0;
}
