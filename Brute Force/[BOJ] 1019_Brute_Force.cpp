#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N;
vector<ll> v(10,0);

/*
 
 1~9 : 1부터 9까지 1번씩
 10~19 : 1은 10개 + 0~9까지 1개씩
 20~29 : 2는 10개 + 0~9까지 1개씩 -> 2자리수 : 1~9까지 10개씩 + 0~9까지 9개씩
 ...
 100~109 : 1은 10개 + 0은 10개 + 0~9까지 1개씩
 110~119 : 1은 10개 + 1은 10개 + 0~9까지 1개씩
 ...
 190~199 : 1은 10개 + 9는 10개 + 0~9까지 1개씩
 ...
 990~999 : 9는 10개 + 9는 10개 + 0~9까지 1개씩 -> 3자리수 : 1~9까지 100개씩 + 0~9까지 90개씩 + 0~9까지 90개씩
 ...                                         4자리수 : 1~9까지 1000개씩 + 0~9까지 900개씩 + 900개 + 900개
 
*/

void output()
{
    for(int i = 0; i < 10; i++)
        cout << v[i] << " ";
    cout << endl;
}

void solve()
{
    vector<int> idx;
    string num = to_string(N);
    int len = static_cast<int>(num.length());
    
    if(len == 1)
    {
        for(int i = 1; i < N; i++)
            v[i]++;
        return;
    }
    
    for(int i = 1; i < 10; i++)
        v[i]++;
    
    int front = 10,rear = 9;
    for(int i = 2; i < len; i++)
    {
        for(int j = 1; j < 10; j++)
            v[j] += front;
        for(int j = 0; j < 10; j++)
            v[j] += rear*(i-1);
        
        front *= 10;
        rear  *= 10;
    }
    
    int cur = num[0]-'0';
    for(int i = 1; i < cur; i++)
        v[i] += front;
    idx.push_back(num[0]-'0');
    
    for(int i = 1; i < len; i++)
    {
        cur = num[i]-'0';
        
    }
}

int main(int argc,char* argv[])
{
    cin >> N;
    solve();
    output();
    return 0;
}
