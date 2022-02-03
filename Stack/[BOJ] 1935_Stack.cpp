#include <iostream>
#include <string>
#include <stack>

using namespace std;

int N;
double nums[26];
string in;
stack<double> s;

inline bool isAlpha(char c) { return (c >= 'A' && c <= 'Z'); }

inline bool isOperator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }

void input()
{
    cout << fixed;
    cout.precision(2);
        
    cin >> N;
    cin >> in;
    for(int i = 0; i < N; i++)
        cin >> nums[i];
    
}

double calculate(double a,double b,char op)
{
    switch(op)
    {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
    }
    
    return 0;
}

double solve()
{
    size_t len = in.length();
    for(size_t i = 0; i < len; i++)
    {
        if(isOperator(in[i]))
        {
            double B = s.top();
            s.pop();
            double A = s.top();
            s.pop();
            double output = calculate(A,B,in[i]);
            s.push(output);
        }
        else
        {
            s.push(nums[in[i]-'A']);
        }
    }
    
    return s.top();
}

int main()
{
    input();
    
    cout << solve() << endl;
    return 0;
}
