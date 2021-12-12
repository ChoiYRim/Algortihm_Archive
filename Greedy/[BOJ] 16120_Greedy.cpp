#include <iostream>
#include <string>

using namespace std;

string PPAP = "";

int main()
{
    int cnt = 0;
    cin >> PPAP;
    
    for(int i = 0; i < (int)PPAP.length(); i++)
    {
        char cur = PPAP[i];
        
        if(cur == 'P')
        {
            cnt++;
            continue;
        }
        if(cnt >= 2 && i+1 < (int)PPAP.length() && PPAP[i+1] == 'P')
        {
            cnt--;
            i++;
        }
        else
        {
            cout << "NP" << '\n';
            return 0;
        }
    }
    
    if(cnt != 1)
        cout << "NP" << '\n';
    else
        cout << "PPAP" << '\n';
    return 0;
}
