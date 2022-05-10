#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int TC;
int alpha[26] = {0,};

void init()
{
    for(int i = 0; i < 26; i++)
    {
        alpha[i] = min(i-0, 26-i); // 각 문자에서 A까지의 최단 거리
    }
}

int solve(string& str)
{
    if(str.length() <= 0) return 0;

    int cnt = 0, j;
    int len = static_cast<int>(str.length());
    int Move = len-1;

    for(int i = 0; i < len; i++)
    {
        cnt += alpha[str[i]-'A'];

        j = i+1;
        while(j < len && str[j] == 'A') j++;
        Move = min(Move, i+len-j+min(i, len-j));
    }

    return cnt+Move;
}

int main(int argc, char* argv[])
{
    cin >> TC;

    init();
    while(TC--)
    {
        string input = ""; cin >> input;
        cout << solve(input) << endl;
    }

    return 0;
}
