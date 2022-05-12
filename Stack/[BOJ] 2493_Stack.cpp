#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<int> result;
vector<pair<int, int>> v;

int main(int argc, char* argv[])
{
    cin >> N;
    result = vector<int>(N,0);
    for(int i = 0; i < N; i++)
    {
        int value; cin >> value;
        int index = 0;
        
        while(!v.empty())
        {
            if(value < v.back().first)
            {
                index = v.back().second;
                break;
            }
            
            v.pop_back();
        }
        
        result[i] = index;
        v.push_back({value, i+1});
    }
    
    for(int i = 0; i < N; i++) cout << result[i] << " ";
    return 0;
}
