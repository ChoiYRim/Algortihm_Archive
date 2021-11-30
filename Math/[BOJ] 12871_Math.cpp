#include <iostream>
#include <string>

using namespace std;

string s = "",t = "";

int gcd(int a,int b)
{
    if(b != 0)
        return gcd(b,a%b);
    return a;
}

int lcm(int a,int b)
{
    return (a * b / gcd(a,b));
}

bool solution()
{
    int sl = (int)s.length(),tl = (int)t.length();
    int LCM = lcm(sl,tl);
    string fs = "",ft = "";
    
    for(int i = 0; i < LCM/sl; i++)
        fs += s;
    for(int i = 0; i < LCM/tl; i++)
        ft += t;
    
    if(fs == ft)
        return true;
    return false;
}

int main()
{
    cin >> s;
    cin >> t;
    
    cout << solution() << '\n';
    return 0;
}
