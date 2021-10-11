#include <string>
#include <iostream>

using namespace std;

int N;

int main(int argc,char* argv[])
{
    cin >> N;
    
    int cnt = 0;
    int cur = 665;
    
    while(cnt < N)
    {
        cur++;
        
        string num = to_string(cur);
        
        if(num.find("666") != -1)
            cnt++;
    }
    
    cout << cur << '\n';
    return 0;
}
