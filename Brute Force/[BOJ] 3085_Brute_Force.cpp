#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int ans,n;
vector<string> a;

void check();

int main(int argc,char* argv[])
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string str = ""; cin >> str;
        a.push_back(str);
    }
    for (int i = 0; i < n; i++)
    { // 행 바꾸기
        for (int j = 0; j < n - 1; j++)
        {
            swap(a[i][j],a[i][j + 1]);
            check();
            swap(a[i][j],a[i][j + 1]);
        }
    }
    
    for (int j = 0; j < n; j++)
    { // 열 바꾸기
        for (int i = 0; i < n - 1; i++)
        {
            swap(a[i][j], a[i + 1][j]);
            check();
            swap(a[i][j], a[i + 1][j]);
        }
    }
    
    cout << ans << '\n';
}

void check(void)
{
    char c;
    
    for (int i = 0; i < n; i++)
    { // 행 계산
        int count = 1; // 1개부터 시작
        c = a[i][0];
        
        for (int j = 1; j < n; j++)
        {
            if ((a[i][j] == c))
                count += 1;
            else
                count = 1;
            
            c = a[i][j];
            
            if (count > ans)
                ans = count;
        }
    }

    for (int j = 0; j < n; j++)
    { // 열 계산
        int count = 1;
        c = a[0][j];
        for (int i = 1; i < n; i++)
        {
            if ((a[i][j] == c))
                count += 1;
            else
                count = 1;
            
            c = a[i][j];
            
            if (count > ans)
                ans = count;
        }
    }
}
