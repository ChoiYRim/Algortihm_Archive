#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int N, K, M;
string num, result;

int main(int argc, char* argv[])
{
    cin >> N >> K;
    cin >> num;
    
    M = N-K;
    result.push_back(num[0]);
    for(auto i = 1; i < num.length(); i++)
    {
        while(K && result.length() > 0 && result.back() < num[i])
        {
            result.pop_back();
            K--;
        }
        
        result.push_back(num[i]);
    }
    
    for(auto i = 0; i < M; i++)
        cout << result[i];
    cout << endl;
    return 0;
}
