#include <iostream>

using namespace std;
using ll = long long;

int N;
ll result = 0;

int main(int argc, char* argv[])
{
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        result += (N/i)*i;
    }
    
    cout << result << endl;
    return 0;
}

