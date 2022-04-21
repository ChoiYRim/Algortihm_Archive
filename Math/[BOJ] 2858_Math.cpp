#include <iostream>

using namespace std;

int R,B,L,W;

int main(int argc, char* argv[])
{
    cin >> R >> B;
    
    int extent = R+B;

    for(L = 1; L <= extent; L++)
    {
        if(extent % L != 0) continue;
        if(extent / L > L)  continue;
        
        W = extent / L;
        
        if(W*2 + (L-2)*2 != R) continue;
        
        break;
    }
    
    cout << L << " " << W << endl;
    return 0;
}
