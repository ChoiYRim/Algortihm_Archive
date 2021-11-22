#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int N,K,ans;

void DFS(int cur,string str)
{
    if(cur == N)
    {
        ans++;
        if(ans == K)
        {
            for(int i = 0; i < (int)str.length(); i++)
            {
                if(i < str.length()-1)
                    cout << str[i] << '+';
                else
                    cout << str[i] << '\n';
            }
            exit(0);
        }
        return;
    }
    if(cur > N)
        return;
    
    for(int i = 1; i <= 3; i++)
    {
        cur += i;
        str.push_back(i+'0');
        DFS(cur,str);
        str.pop_back();
        cur -= i;
    }
}

int main()
{
    ans = 0;
    cin >> N >> K;
    DFS(0,"");
    cout << -1 << '\n';
    return 0;
}
