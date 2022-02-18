#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solve(const string& s)
{
    int len = static_cast<int>(s.length());
    int ret = len;
    
    // 문자열을 i개 단위로 잘랐을 때
    for(int i = 1; i <= len; i++)
    {
        string result = "";
        string cur = s.substr(0,i);
        
        if(len <= i)
            continue;
        
        string next = s.substr(i);
        int cnt = 1,pos = i,next_len = static_cast<int>(next.length());
        
        //printf("cur : %s\n", cur.c_str());
        //printf("next : %s\n", next.c_str());
        
        while(next_len > 0)
        {
            string tmp = next.substr(0,i);
            
            if(tmp != cur)
            {
                if(cnt < 2)
                    result += cur;
                else
                    result = result + to_string(cnt) + cur;
                
                cnt = 1;
                cur = tmp;
            }
            else
                cnt++;
            
            if(len <= pos+i)
            {
                string remain = s.substr(pos);
                
                if(remain != cur)
                    result += remain;
                else
                {
                    if(cnt < 2)
                        result = result + cur;
                    else
                        result = result + to_string(cnt) + cur;
                }
                break;
            }
            
            next = s.substr(pos+i);
            pos += i;
            next_len -= i;
        }
        
        int local_len = static_cast<int>(result.length());
        //printf("local len : %d\n", local_len);
        ret = min(ret,local_len);
        //printf("result : %s\n", result.c_str());
    }
    
    return ret;
}

int solution(string s)
{
    return solve(s);
}

int main()
{
    cout << solution("aabbaccc") << endl;
    return 0;
}
