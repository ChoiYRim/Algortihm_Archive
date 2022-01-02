#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

string n = "",ans = "";

string add(string a,string b)
{
    string ret = "";

    int prev = 0;
    int al = (int)a.length();
    int bl = (int)b.length();
    int ml = (al > bl ? al : bl);

    while((int)a.length() < ml)
        a = "0"+a;
    while((int)b.length() < ml)
        b = "0"+b;

    for(int i = ml-1; i >= 0; i--)
    {
        int A = a[i]-'0';
        int B = b[i]-'0';
        int num = (A+B+prev)%10;

        ret.push_back(num+'0');
        prev = (A+B+prev)/10;
    }
    if(prev)
        ret.push_back(prev+'0');

    while(ret.back() == '0')
        ret.pop_back();

    reverse(ret.begin(),ret.end());
    if(!ret.length())
        return "0";
    return ret;
}

string sub(string a,string b) // a가 b보다 큰게 보장되어야함
{
    string ret = "";

    while(b.length() < a.length())
        b = "0"+b;

    for(int i = (int)a.length()-1; i >= 0; i--)
    {
        int A = a[i]-'0';
        int B = b[i]-'0';

        if(A < B)
        {
            for(int j = i-1; j >= 0; j--)
            {
                if(a[j]-'0' > 0)
                {
                    a[j]--;
                    for(int k = j+1; k < i; k++)
                        a[k] = '9';
                    A += 10;
                    break;
                }
            }
        }

        ret.push_back((A-B)+'0');
    }

    while(ret.back() == '0')
        ret.pop_back();

    reverse(ret.begin(),ret.end());
    if(!ret.length())
        return "0";
    return ret;
}

string mul(string a,string b)
{
    string ret = "";

    int cnt = 0;
    int al = (int)a.length();
    int bl = (int)b.length();
    int ml = (al > bl ? al : bl);

    while((int)a.length() < ml)
        a = "0"+a;
    while((int)b.length() < ml)
        b = "0"+b;

    for(int i = ml-1; i >= 0; i--)
    {
        int prev = 0;
        string tmp = "";

        for(int j = 0; j < cnt; j++)
            tmp.push_back('0');
        for(int j = ml-1; j >= 0; j--)
        {
            int A = a[i]-'0';
            int B = b[j]-'0';
            int num = (A*B+prev)%10;

            tmp.push_back(num+'0');
            prev = (A*B+prev)/10;
        }
        if(prev)
            tmp.push_back(prev+'0');

        reverse(tmp.begin(),tmp.end());

        ret = add(ret,tmp);
        cnt++;
    }

    if(!ret.length())
        return "0";
    return ret;
}

string mid(string a,string b)
{
    int prev = 0;
    string ret = "",sum = add(a,b);

    for(int i = 0; i < (int)sum.length(); i++)
    {
        int num,front = prev*10+(sum[i]-'0');

        if(front < 2)
        {
            if(i+1 >= (int)sum.length())
            {
                ret.push_back('0');
                break;
            }

            front *= 10;
            front += sum[i+1]-'0';
            i++;
        }

        num = front/2;
        prev = front%2;
        ret.push_back(num+'0');
    }

    return ret;
}

bool comp(string a,string b)
{
    int la = (int)a.length();
    int lb = (int)b.length();

    if(la > lb)
        return false;
    if(la < lb)
        return true;

    for(int i = 0; i < la; i++)
    {
        if(a[i] > b[i])
            return false;
        if(a[i] < b[i])
            return true;
    }

    return true;
}

string bs(string left,string right)
{
    if(comp(left,right))
    {
        string m = mid(left,right);
        string p = mul(m,m);

        if(p == n)
            return m;
        else if(p > n)
            return bs(left,sub(m,"1"));
        else
            return bs(add(m,"1"),right);
    }

    return "";
}

int main()
{
    chrono::system_clock::time_point begin,end;
    
    for(int i = 0; i < 800; i++)
        n.push_back('9');
    
    string left = "1";
    string right = "10";

    for(int i = 0; i < ceil(n.length()/2)-1; i++)
    {
        left = left+'0';
        right = right+'0';
    }
    
    begin = chrono::system_clock::now();
    cout << bs(left,right) << '\n';
    end = chrono::system_clock::now();
    auto result_us = chrono::duration_cast<std::chrono::microseconds>(end-begin);
    
    cout << "executing time : " << result_us.count() << '\n';
    return 0;
}
