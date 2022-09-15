#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
string str;

void input()
{
    cin >> N;
    cin >> M;
    cin >> str;
}

int solve()
{
    int cnt = 0;
    
    for(int i = 0; i < M; i++)
    {
        if(str[i] != 'I') continue;
        
        int k = 0;
        while(i+2 < M && str[i+1] == 'O' && str[i+2] == 'I')
        {
            k++;
            
            if(k == N)
            {
                k--;
                cnt++;
            }
            
            i += 2;
        }
    }
    
    return cnt;
}

int main(int argc, char* argv[])
{
    input();
    cout << solve() << endl;
    return 0;
}
