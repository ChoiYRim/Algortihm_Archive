#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int T;

bool solve(int left, int right, const string& input)
{
    if(left == right)
        return true;
    
    int mid = (left+right)/2; // middle position
    int len = mid-left;
    
    for(int i = 0; i < len; i++)
    {
        if(input[left+i] == input[mid+len-i])
            return false;
    }
    
    return (solve(left, mid-1, input) & solve(mid+1, right, input));
}

int main(int argc, char* argv[])
{
    cin >> T;
    while(T--)
    {
        string input = "";
        
        cin >> input;
        cout << (solve(0, static_cast<int>(input.length())-1, input) == true ? "YES" : "NO") << endl;
    }
    
    return 0;
}
