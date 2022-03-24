#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int from,to;
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

void count(int num,int power)
{
    while(num)
    {
        v[num%10] += power;
        num /= 10;
    }
}

void solve()
{
    int power = 1;
    
    from = 1;
    while(from <= to)
    {
        while(from%10 != 0 && from <= to)
        {
            count(from,power);
            from++;
        }
        
        if(to < from)
            return;
        
        while(to%10 != 9 && from <= to)
        {
            count(to,power);
            to--;
        }
        
        from /= 10;
        to /= 10;
        
        for(int i = 0; i < 10; i++)
            v[i] += (to-from+1)*power;
        power *= 10;
    }
}

int main(int argc,char* argv[])
{
    cin >> to;
    solve();
    output();
    return 0;
}
