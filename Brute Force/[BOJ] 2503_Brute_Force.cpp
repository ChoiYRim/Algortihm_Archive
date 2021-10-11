#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Step
{
    int str;
    int strike;
    int ball;
};

int N,cnt = 0;
vector<Step> v;

bool isPossible(string num)
{
    bool number[10] = {0,};
    
    for(int i = 0; i < (int)num.length(); i++)
    {
        if(!number[num[i]-'0'])
            number[num[i]-'0'] = true;
        else
            return false;
    }
    return true;
}

int main(int argc,char* argv[])
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int str,s,b;
        cin >> str >> s >> b;
        v.push_back({str,s,b});
    }
    
    for(int i = 100; i < 1000; i++)
    {
        bool check = true;
        string num = to_string(i);
        
        if(num.find("0") != -1)
            continue;
        if(!isPossible(num))
            continue;
        
        for(int j = 0; j < N; j++)
        {
            string str = to_string(v[j].str);
            int s = v[j].strike,b = v[j].ball;
            int sc = 0,bc = 0;
            
            for(int k = 0; k < 3; k++)
            {
                if(num[k] == str[k])
                    sc++;
                else
                {
                    for(int l = 0; l < 3; l++)
                    {
                        if(num[k] == str[l])
                            bc++;
                    }
                }
            }
            
            if(sc != s || bc != b)
            {
                check = false;
                break;
            }
        }
        
        if(check)
            cnt++;
    }
    
    cout << cnt << '\n';
    return 0;
}
