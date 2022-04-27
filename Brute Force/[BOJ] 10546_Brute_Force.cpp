#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int N;
unordered_map<string, int> m;

void input()
{
    scanf("%d", &N);
    for(int i = 0; i < N*2-1; i++)
    {
        string tmp = ""; cin >> tmp;
        if(m.find(tmp) != m.end())
            m[tmp]++;
        else
            m.insert({tmp, 1});
    }
}

void output()
{
    for(const auto& ele : m)
    {
        if(ele.second % 2 != 0)
        {
            cout << ele.first << endl;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    input();
    output();
    return 0;
}
