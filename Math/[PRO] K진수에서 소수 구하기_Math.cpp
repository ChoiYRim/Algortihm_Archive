#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using ull = unsigned long long;

// 10진수 n을 k진법 수로 바꾼 후
// (P는 10진수 기준)
// 0P0
// P0
// 0P
// P
// 를 만족하는 소수 P의 개수를 구해야 한다.
// 2진수가 가장 수가 길게 나오는데, 10^6 = 2^20

string convert_k(int n,int k)
{
    string ret = "";
    
    while(n > 0)
    {
        ret += to_string(n%k);
        n /= k;
    }
    
    reverse(ret.begin(),ret.end());
    return ret;
}

int check(string str)
{
    ull number = stoull(str);
    
    if(number <= 1)
        return 0;
    if(number % 2 == 0)
        return number == 2 ? 1 : 0;
    
    for(int i = 3; i <= sqrt(number); i += 2)
    {
        if(number % i == 0)
            return 0;
    }
    return 1;
}

int solve(string& converted)
{
    size_t idx = 0;
    int count = 0;
    string str = converted;
    string tmp = "";
    
    while(idx < str.size())
    {
        if(str[idx] != '0')
            tmp += str[idx];
        else
        {
            if(tmp.size())
                count += check(tmp);
            tmp.clear();
        }
        idx++;
    }
    if(tmp.size())
        count += check(tmp);
    
    return count;
}

int solution(int n, int k)
{
    int answer = -1;
    string converted = convert_k(n,k);
        
    return answer = solve(converted);
}

int main()
{
    cout << solution(1000000,3) << endl;
    return 0;
}
