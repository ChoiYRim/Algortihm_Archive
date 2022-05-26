#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<string> v, result;
bool alpha[26] = {0,};

void input()
{
    string str;
    
    cin >> N; getchar();
    for(int i = 0; i < N; i++)
    {
        getline(cin, str);
        v.push_back(str);
    }
}

void solve()
{
    for(int i = 0; i < N; i++)
    {
        string str = v[i];
        string tmp = "", ans = "";
        stringstream ss(str);
        bool check = false;
        
        // 맨 앞자리 먼저
        while(ss >> tmp)
        {
            if(tmp.length() <= 0) continue;
            if(check) { ans += tmp+" "; continue; }
            
            char ch = tmp[0];
            
            if(ch >= 'A' && ch <= 'Z')
            {
                if(!alpha[ch-'A'])
                {
                    alpha[ch-'A'] = true;
                    string tmp2(3, ' '); tmp2[0] = '['; tmp2[1] = ch; tmp2[2] = ']';
                    tmp2 += tmp.substr(1, tmp.length());
                    ans += tmp2+" ";
                    check = true;
                    continue;
                }
            }
            if(ch >= 'a' && ch <= 'z')
            {
                if(!alpha[ch-'a'])
                {
                    alpha[ch-'a'] = true;
                    string tmp2(3, ' '); tmp2[0] = '['; tmp2[1] = ch; tmp2[2] = ']';
                    tmp2 += tmp.substr(1, tmp.length());
                    ans += tmp2+" ";
                    check = true;
                    continue;
                }
            }
            
            ans += tmp+" ";
        }
        if(check)
        {
            if(ans.length() > 0 && ans.back() == ' ') ans.pop_back();
            result.push_back(ans);
            continue;
        }
        
        for(int j = 0; j < str.length(); j++)
        {
            if(str[j] == ' ') continue;
            
            if(str[j] >= 'A' && str[j] <= 'Z')
            {
                if(!alpha[str[j]-'A'])
                {
                    alpha[str[j]-'A'] = true;
                    ans = str.substr(0, j);
                    string tmp2(3, ' '); tmp2[0] = '['; tmp2[1] = str[j]; tmp2[2] = ']';
                    ans += tmp2; ans += str.substr(j+1, str.length());
                    check = true;
                    result.push_back(ans);
                    break;
                }
            }
            if(str[j] >= 'a' && str[j] <= 'z')
            {
                if(!alpha[str[j]-'a'])
                {
                    alpha[str[j]-'a'] = true;
                    ans = str.substr(0, j);
                    string tmp2(3, ' '); tmp2[0] = '['; tmp2[1] = str[j]; tmp2[2] = ']';
                    ans += tmp2; ans += str.substr(j+1, str.length());
                    check = true;
                    result.push_back(ans);
                    break;
                }
            }
        }
        if(!check)
            result.push_back(str);
    }
}

void output()
{
    for(const auto& ele : result)
        cout << ele << endl;
}

int main(int argc, char* argv[])
{
    input();
    solve();
    output();
    return 0;
}

