#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

string exp = "";
string ops = "";
bool selected[4];

int priority(char op,const string& cur)
{
    for(int i = cur.length()-1; i >= 0; i--)
    {
        if(op == cur[i])
            return i;
    }
    
    return -1;
}

ll calculate(int op_num,vector<string>& result)
{
    int i = 0;
    
    while(op_num > 0)
    {
        string cur = result[i];
        
        if(cur[0] >= '0' && cur[0] <= '9')
        {
            i++;
            continue;
        }
        if(cur.length() > 1 && cur[0] == '-')
        {
            i++;
            continue;
        }
        
        ll output = 0;
        char c = cur[0];
        ll num1 = stoll(result[i-2]);
        ll num2 = stoll(result[i-1]);
        
        op_num--;
        
        if(c == '+')
            output = num1+num2;
        else if(c == '-')
            output = num1-num2;
        else
            output = num1*num2;
        
        result[i-2] = to_string(output);
        result.erase(result.begin()+i-1);
        result.erase(result.begin()+i-1);
        i = i-2;
    }
    
    return stoll(result[0]);
}

void dfs(int depth,string cur,ll& answer)
{
    if(depth == ops.length())
    {
        //printf("%s\n", cur.c_str());
        string tmp = "";
        stack<char> st;
        vector<string> numbers;
        int operator_num = 0;
        
        for(int i = 0; i < exp.length(); i++)
        {
            if(exp[i] >= '0' && exp[i] <= '9')
                tmp.push_back(exp[i]);
            else
            {
                operator_num++;
                numbers.push_back(tmp);
                tmp.clear();
                
                if(st.empty())
                    st.push(exp[i]);
                else
                {
                    if(priority(st.top(),cur) >= priority(exp[i],cur))
                    {
                        while(!st.empty())
                        {
                            if(priority(st.top(),cur) < priority(exp[i],cur))
                                break;
                            
                            tmp.clear();
                            tmp.push_back(st.top());
                            numbers.push_back(tmp);
                            st.pop();
                        }
                        
                        st.push(exp[i]);
                    }
                    else
                    {
                        st.push(exp[i]);
                    }
                }
                
                tmp.clear();
            }
        }
        
        numbers.push_back(tmp);
        while(!st.empty())
        {
            tmp.clear();
            tmp.push_back(st.top());
            numbers.push_back(tmp);
            st.pop();
        }
        
        // printf("--------------\n");
        // printf("operator : %s\n", cur.c_str());
        // for(auto ele : numbers)
        //     printf("[%s]\n", ele.c_str());
        // ll output = abs(calculate(operator_num,numbers));
        // printf("output : %lld\n", output);
        // printf("--------------\n");
           
        ll output = abs(calculate(operator_num,numbers));
        answer = max(answer,output);
        return;
    }
    
    for(int i = 0; i < ops.length(); i++)
    {
        if(selected[i]) continue;
        
        selected[i] = true;
        cur.push_back(ops[i]);
        dfs(depth+1,cur,answer);
        cur.pop_back();
        selected[i] = false;
    }
}

ll solution(string expression)
{
    ll answer = 0;
    bool check[3] = {0,};
    
    exp = expression;
    for(int i = 0; i < exp.length(); i++)
    {
        if(exp[i] >= '0' && exp[i] <= '9')
            continue;
        
        if(exp[i] == '+')
        {
            if(check[0])
                continue;
            
            check[0] = true;
            ops.push_back(exp[i]);
        }
        else if(exp[i] == '-')
        {
            if(check[1])
                continue;
            
            check[1] = true;
            ops.push_back(exp[i]);
        }
        else if(exp[i] == '*')
        {
            if(check[2])
                continue;
            
            check[2] = true;
            ops.push_back(exp[i]);
        }
    }
    
    //printf("ops : %s\n", ops.c_str());
    dfs(0,"",answer);
    
    return answer;
}

int main(int argc,char* argv[])
{
    cout << solution("100-200*300-500+20") << endl;
    return 0;
}
