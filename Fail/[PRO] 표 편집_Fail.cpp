#include <set>
#include <stack>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

stack<int> st;
set<int> table;
set<int>::iterator cur;

string solution(int n, int k, vector<string> cmds)
{
    for(int i = 0; i < n; i++)
        table.insert(i);
    
    cur = table.find(k);
    string result(n,'X');
    
    for(const auto& cmd : cmds)
    {
        if(cmd[0] == 'U' || cmd[0] == 'D')
        {
            string str = cmd.substr(2);
            int cnt = stoi(str);
            
            if(cmd[0] == 'U')
                while(cnt--)
                    cur = prev(cur);
            else
                while(cnt--)
                    cur = next(cur);
            continue;
        }
        if(cmd[0] == 'C')
        {
            st.push(*cur);
            cur = table.erase(cur);
            if(cur == table.end())
                cur = prev(cur);
            continue;
        }
        table.insert(st.top());
        st.pop();
    }
    
    for(auto& ele : table)
        result[ele] = 'O';
    
    return result;
}
int main(int argc,char* argv[])
{
    cout << solution(8, 2, {"D 2","C","U 3","C","D 4","C","U 2","Z","Z"}) << endl;
    return 0;
}
