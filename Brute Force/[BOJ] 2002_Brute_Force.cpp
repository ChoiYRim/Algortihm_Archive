#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int N;
vector<int> v;
map<string, int> m;

int solve()
{
    int cnt = 0, idx = 0;
    
    cin >> N;
    v = vector<int>(N, 0);
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        m.insert({tmp, i});
    }
    
    for(int i = 0; i < N; i++)
    {
        string tmp; cin >> tmp;
        int tmp_idx = m.find(tmp)->second;
        
        if(tmp_idx != idx)
        {
            cnt++;
            v[tmp_idx] = 1;
            continue;
        }
        
        idx++;
        while(idx < N && v[idx]) idx++;
    }
    
    return cnt;
}

int main(int argc, char* argv[])
{
    cout << solve() << endl;
    return 0;
}
