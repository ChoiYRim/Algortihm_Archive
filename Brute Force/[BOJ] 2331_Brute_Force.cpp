#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int A, P;
unordered_map<int, int> m;

int main(int argc, char* argv[])
{
    int idx = 0, output = 0;
    
    cin >> A >> P;
    
    m[A] = idx++;
    while(1)
    {
        int sum = 0, result;
        
        while(A > 0)
        {
            int num = A%10;
            
            if(num == 0)
            {
                A /= 10;
                continue;
            }
            
            result = 1;
            
            for(int i = 0; i < P; i++)
                result *= num;
            
            sum += result;
            A /= 10;
        }
        
        if(m.find(sum) != m.end())
        {
            output = m[sum];
            break;
        }
        
        A = sum;
        m[sum] = idx++;
    }
    
    cout << output << endl;
    return 0;
}
