#include <stack>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const char Left = '(';
const char Right = ')';

pair<string,string> split(const string& p)
{
    string u = ""; // 더 이상 분리가 불가해야 함
    string v = ""; // u를 만들고 남은 문자열
    int len = static_cast<int>(p.length());
    int left_cnt = 0,right_cnt = 0,i = 1;
    
    if(p[0] != Left)
    {
        u.push_back(Right);
        right_cnt++;
    }
    else
    {
        u.push_back(Left);
        left_cnt++;
    }
    
    for(;i < len && left_cnt != right_cnt; i++)
    {
        char ele = p[i];
        
        if(ele != Left)
        {
            u.push_back(Right);
            right_cnt++;
        }
        else
        {
            u.push_back(Left);
            left_cnt++;
        }
    }
    
    v = p.substr(i);
        
    return {u,v};
}

bool is_correct(const string& p)
{
    stack<char> st;
    int len = static_cast<int>(p.length());
    
    if(len <= 0)
        return true;
    if(p[0] != Left) // 괄호의 시작은 (로 시작해야한다.
        return false;
    
    st.push(p[0]);
    for(int i = 1; i < len; i++)
    {
        if(p[i] == Right)
        {
            if(st.empty())
                return false;
            st.pop();
            continue;
        }
        st.push(p[i]);
    }
    
    return (st.empty() ? true : false);
}

string solve(const string& p)
{
    int len = static_cast<int>(p.length());
    
    // step 1
    if(len <= 0)
        return "";
    
    // step 2
    auto uv = split(p);
    //printf("%s %s\n", uv.first.c_str(), uv.second.c_str());
    string u = uv.first;
    string v = uv.second;
    
    if(is_correct(u))
        return u+solve(v);
    
    string str = "("+solve(v);
    str.push_back(')');
    
    u = u.substr(1);
    u.pop_back();
    for(auto& ele : u)
    {
        if(ele != Left)
            ele = Left;
        else
            ele = Right;
    }
    
    return str+u;
}

string solution(string p)
{
    return solve(p);
}

int main()
{
    cout << solve("()))((()") << endl;
    return 0;
}
