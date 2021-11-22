#include <vector>
#include <iostream>
#include <algorithm>

#define ABS(x) (x >= 0 ? x : -x)

using namespace std;

int N,result = 0;
vector<int> column; // {y,x}

void DFS(int y,int x,int cnt)
{
    if(cnt == N)
    {
        result++;
        return;
    }
    
    for(int i = 0; i < N; i++) // 열 번호
    {
        bool check = true;

        for(int j = 0; j < (int)column.size(); j++) // j : 행 번호 , column[j] : 열 번호
        {
            if(j == y || i == column[j] || (ABS((j-y)) == ABS((i-column[j]))))
            {
                check = false;
                break;
            }
        }
        if(check)
        {
            column.push_back(i);
            DFS(y+1,i,cnt+1);
            column.pop_back();
        }
    }
}

int main(int argc, const char * argv[])
{
    cin >> N;
    
    DFS(0,0,0);
    
    cout << result << '\n';
    return 0;
}
