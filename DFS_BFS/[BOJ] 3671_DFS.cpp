#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using uset = unordered_set<int>;

int tc;
uset s;
vector<bool> selected;

bool is_prime(int num)
{
    if(num < 2) return false;
    
    for(int i = 2; i <= sqrt(num); i++) if(num % i == 0) return false;
    
    return true;
}

void dfs(int depth, int num, int& answer, const vector<int>& v)
{
    if(depth == v.size())
    {
        //cout << "num : " << num << endl;
        if(s.find(num) != s.end()) return;
        s.insert(num);
        if(is_prime(num)) answer++;
        return;
    }
    
    // 안고름
    dfs(depth+1, num, answer, v);
    
    // 고름
    for(int i = 0; i < v.size(); i++)
    {
        int ele = v[i];

        if(selected[i]) continue;

        selected[i] = true;
        num = num*10+ele;
        dfs(depth+1, num, answer, v);
        num /= 10;
        selected[i] = false;
    }
}

int main(int argc, char* argv[])
{
    cin >> tc;
    while(tc--)
    {
        s.clear();
        
        int answer = 0;
        vector<int> v;
        
        string tmp; cin >> tmp;
        for(const auto& ele : tmp)
        {
            int num = ele-'0';
            
            v.push_back(num);
        }
        
        selected = vector<bool>(10, 0);
        dfs(0, 0, answer, v);
        cout << answer << endl;
    }
    
    return 0;
}
