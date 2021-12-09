#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

const int MAX = 16;
int N;
string s; // [i, j] 범위 내 연산 최댓값, 최솟값
int maxCache[MAX][MAX];
int minCache[MAX][MAX];

void initialize(void)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            maxCache[i][j] = INT_MIN;
            minCache[i][j] = INT_MAX;
        }
    }
    
}

int calculate(int a, int b, char op)
{
    switch (op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
    }
    
    return 0;
}

int main(void)
{
    cin >> N;
    cin >> s;
    
    initialize();
    
    int numberCnt = N / 2 + 1; // 한 자리 수 값만 존재하기 때문에 전체 수의 개수는 N/2 + 1
    
    for (int i = 0; i < numberCnt; i++)
        maxCache[i][i] = minCache[i][i] = s[i * 2] - '0'; // i번째 ~ i번째 연산 최대값은 그냥 i번째 값
    
    for (int cnt = 1; cnt < numberCnt; cnt++)
    {
        for (int idx = 0; idx < numberCnt - cnt; idx++)
        {
            for (int i = 1, j = cnt; i <= cnt; i++, j--)
            {
                int opIdx = (idx + cnt - j) * 2 + 1;
                char op = s[opIdx];
                int candidates[4] =
                {
                    calculate(maxCache[idx][idx + cnt - j], maxCache[idx + i][idx + cnt], op),
                    calculate(maxCache[idx][idx + cnt - j], minCache[idx + i][idx + cnt], op),
                    calculate(minCache[idx][idx + cnt - j], maxCache[idx + i][idx + cnt], op),
                    calculate(minCache[idx][idx + cnt - j], minCache[idx + i][idx + cnt], op)
                };
                
                sort(candidates, candidates + 4);
                
                maxCache[idx][idx + cnt] = max(maxCache[idx][idx + cnt], candidates[3]);
                minCache[idx][idx + cnt] = min(minCache[idx][idx + cnt], candidates[0]);
                
            }
        }
    }
    
    cout << maxCache[0][numberCnt - 1] << "\n";
    return 0;
}
