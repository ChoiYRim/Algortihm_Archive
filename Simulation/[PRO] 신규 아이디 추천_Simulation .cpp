#include <string>
#include <vector>
#include <iostream>

using namespace std;

inline bool is_number(char c) { return (c >= '0' && c <= '9'); }

inline bool is_lower_case(char c) { return (c >= 'a' && c <= 'z'); }

inline bool is_upper_case(char c) { return (c >= 'A' && c <= 'Z'); }

inline bool is_special(char c) { return (c == '-' || c == '_' || c == '.'); }

bool check_id(const string& new_id)
{
    int len = static_cast<int>(new_id.size());
    
    if(len < 3 || len > 15)
        return false;
    if(new_id[0] == '.' || new_id[len-1] == '.')
        return false;
    
    int dot = 0;
    for(int i = 0; i < len; i++)
    {
        if(is_lower_case(new_id[i])) // 소문자
        {
            dot = 0;
            continue;
        }
        else // 소문자가 아님
        {
            if(!is_special(new_id[i])) // 특수 문자도 아님
                return false;
            if(new_id[i] == '.')
            {
                dot++;
                
                if(dot > 1)
                    return false;
            }
            else
                dot = 0;
        }
    }
    
    return true;
}

/*
1단계 new_id의 모든 대문자를 대응되는 소문자로 치환합니다.
2단계 new_id에서 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
3단계 new_id에서 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환합니다.
4단계 new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거합니다.
5단계 new_id가 빈 문자열이라면, new_id에 "a"를 대입합니다.
6단계 new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거합니다.
     만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거합니다.
7단계 new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.
*/

string convert_user_id(string new_id)
{
    int len = static_cast<int>(new_id.length()),dot = 0;
    string converted = "";
    char alpha[26] = {0,};
    
    for(int i = 0; i < 26; i++)
        alpha[i] = 'a'+i;
    
    for(int i = 0; i < len; i++)
    {
        char c = new_id[i];
        
        if(is_lower_case(c) || is_number(c))
        {
            dot = 0;
            converted.push_back(c);
            continue;
        }
        
        if(is_upper_case(c))
        {
            dot = 0;
            converted.push_back(alpha[c-'A']);
        }
        else if(is_special(c))
        {
            if(c == '.')
            {
                dot++;
                if(dot > 1)
                    continue;
                converted.push_back(c);
            }
            else
            {
                dot = 0;
                converted.push_back(c);
            }
        }
    }
    if(converted.length() > 0 && converted[0] == '.')
        converted = converted.substr(1);
    if(converted.length() > 0 && converted.back() == '.')
        converted.pop_back();
    if(converted.length() < 1)
        converted.push_back('a');
    if(converted.length() > 15)
    {
        converted = converted.substr(0,15);
        while(converted.back() == '.')
            converted.pop_back();
    }
    while(converted.length() < 3)
    {
        char c = converted.back();
        converted.push_back(c);
    }
    
    return converted;
}

string solve(const string& new_id)
{
    if(check_id(new_id))
        return new_id;
    return convert_user_id(new_id);
}

string solution(string new_id)
{
    return solve(new_id);
}

int main()
{
    cout << solution("") << endl;
    return 0;
}
