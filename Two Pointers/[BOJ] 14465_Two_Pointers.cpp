#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N, K, B;
vector<bool> v;

int main(int argc, char* argv[])
{
    int cnt = 0;
    
    cin >> N >> K >> B;
    v = vector<bool>(100001);
    for(int i = 0; i < B; i++) { int tmp; cin >> tmp; v[tmp] = 1; }
    
    cnt = B;
    for(int i = 1; i <= N-K+1; i++)
    {
        int tmp = 0;
        for(int j = i; j < i+K; j++)
        {
            if(v[j]) tmp++;
        }
        cnt = min(cnt, tmp);
    }
    
    cout << cnt << endl;
    return 0;
}
