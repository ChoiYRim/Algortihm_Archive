#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<string> v;

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        v.push_back(move(tmp));
    }
}

int solve()
{
    int cnt = 0;
    
    for(auto& str : v)
    {
        char prev = '0';
        bool flag = true, alpha[26] = {0, };
        
        for(int i = 0; i < str.length(); i++)
        {
            if(alpha[str[i]-'a'] && prev != str[i])
            {
                flag = false;
                break;
            }
            
            prev = str[i];
            alpha[str[i]-'a'] = true;
        }
        if(flag) cnt++;
    }
    
    return cnt;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
