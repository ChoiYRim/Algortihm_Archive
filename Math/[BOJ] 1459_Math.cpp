#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

ll Y, X, S, W;

int main(int argc, char* argv[])
{
    ll result = 0, diff;
    
    cin >> X >> Y >> W >> S;
    
    if(2*W <= S)
        result = W*Y+W*X;
    else if(2*W > S)
    {
        if(Y < X)
        {
            result = Y*S;
            diff = X-Y;
        }
        else
        {
            result = X*S;
            diff = Y-X;
        }
        if(diff % 2 != 0) result += min(diff*W, W+(diff-1)*S);
        else result += min(diff*W, min(diff*S, diff/2*S+diff/2*W));
    }
    
    cout << result << endl;
    return 0;
}
