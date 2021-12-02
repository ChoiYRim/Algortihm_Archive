#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

bool solution(string s,string t)
{
    while(1)
    {
        if(s.length() == t.length())
        {
            if(s == t)
                return true;
            break;
        }
        
        char last = t.back();
        t.pop_back();
        
        if(last != 'A')
            reverse(t.begin(),t.end());
    }
    
    return false;
}

int main()
{
    string s,t;
    
    cin >> s;
    cin >> t;
    
    cout << solution(s,t) << '\n';
    return 0;
}
