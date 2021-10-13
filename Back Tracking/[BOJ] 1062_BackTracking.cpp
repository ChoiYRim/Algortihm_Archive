#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int N,K,ans = 0;
std::vector<std::string> v;
bool alpha[26] = {0,};

int getIdx(char a) { return (a-'a' > 0 ? a-'a' : 0); }

void solve(int depth,int cur)
{
    if(depth == K)
    {
        int cnt = 0;
        
        for(int i = 0; i < (int)v.size(); i++)
        {
            bool check = true;

            for(int j = 0; j < (int)v[i].length(); j++)
            {
                int idx = getIdx(v[i][j]);
                
                if(!alpha[idx])
                {
                    check = false;
                    break;
                }
            }
            if(check)
                cnt++;
        }
        
        ans = std::max(ans,cnt);
        return;
    }
    
    for(int alphabet = cur; alphabet < 26; alphabet++) // 익힐 수 있는 알파벳을 기준으로 봐야함
    {
        if(!alpha[alphabet])
        {
            alpha[alphabet] = true;
            solve(depth+1,alphabet);
            alpha[alphabet] = false;
        }
    }
}

int main(int argc,char* argv[])
{
    alpha[getIdx('a')] = true;
    alpha[getIdx('c')] = true;
    alpha[getIdx('i')] = true;
    alpha[getIdx('n')] = true;
    alpha[getIdx('t')] = true;
    
    std::cin >> N >> K;
    for(int i = 0; i < N; i++)
    {
        std::string str = "",input = "";
        std::cin >> str;
        
        str.erase(str.begin(), str.begin()+4);
        str.erase(str.end()-4,str.end());
        v.push_back(str);
    }
    
    if(K < 5) // 최소한 a,c,i,n,t는 배울 수 있어야함
    {
        std::cout << 0 << '\n';
        return 0;
    }
    if(K >= 26) // 배울 수 있는 글자 수가 26이상이면 모든 알파벳을 배울 수 있으므로 답은 N
    {
        std::cout << N << '\n';
        return 0;
    }
    
    K -= 5;
    solve(0,0);
    std::cout << ans << '\n';
    return 0;
}
