#include <string>
#include <vector>
#include <iostream>

using namespace std;

int gcd(int a,int b)
{
    if(b == 0)
        return a;
    return gcd(b,a%b);
}

int lcm(int a,int b)
{
    int GCD = gcd(a,b);
    int A = a/GCD;
    
    return b*A;
}

int solution(vector<int> arr)
{
    int answer = arr[0];
    
    for(int i = 1; i < arr.size(); i++)
    {
        answer = lcm(answer,arr[i]);
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    return 0;
}
