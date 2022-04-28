#include <stack>
#include <string>
#include <iostream>

using namespace std;

const char OPEN = '(';
const char CLOSE = ')';

string s;
stack<char> st;

int solve()
{
    int cnt = 0;
    size_t len = s.length();
    
    for(auto i = 0; i < len; i++)
    {
        if(s[i] == CLOSE && i < 1) return 0;
        
        if(s[i] == OPEN)
        {
            st.push(OPEN);
        }
        else if(s[i] == CLOSE && s[i-1] == OPEN) // laser
        {
            st.pop();
            cnt += st.size();
        }
        else // iron stick
        {
            cnt++;
            st.pop();
        }
    }
    
    return cnt;
}

int main(int argc, char* argv[])
{
    cin >> s;
    cout << solve() << endl;
    return 0;
}
