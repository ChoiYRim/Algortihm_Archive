#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const char OPEN = '(';
const char CLOSE = ')';

int cnt = 0;
string str = "";
vector<int> visit;
set<string> result;
vector<pair<int, int>> con;

void init()
{
    vector<int> idx;
    int len = static_cast<int>(str.length());
    
    for(int i = 0; i < len; i++)
    {
        if(str[i] == OPEN)
        {
            cnt++;
            idx.push_back(i);
        }
        else if(str[i] == CLOSE)
        {
            if(idx.size())
            {
                con.push_back({idx.back(), i});
                idx.pop_back();
            }
        }
    }
}

void dfs(int depth, int idx, int total)
{
    if(depth == total)
    {
        result.insert(str);
        return;
    }
    else if(idx >= con.size())
        return;
    
    // X
    dfs(depth, idx+1, total);
    
    // O
    int from = con[idx].first;
    int to   = con[idx].second;
    string save_str = str;
    auto save_con = con;
    
    str = str.substr(0, from)+str.substr(from+1, to-from-1)+str.substr(to+1);
    
    for(int i = 0; i < con.size(); i++)
    {
        if(i == idx) continue;
        
        int& s = con[i].first;
        int& e = con[i].second;
        
        if(s > from && s < to)
            s--;
        else if(s > to)
            s-=2;
        
        if(e > from && e < to)
            e--;
        else if(e > to)
            e-=2;
    }
    
    dfs(depth+1, idx+1, total);
    
    str = save_str;
    con = save_con;
}

int main(int argc, char* argv[])
{
    cin >> str;
    
    init();
    for(int i = 1; i <= cnt; i++)
    {
        visit = vector<int>(con.size(), 0);
        dfs(0, 0, i);
    }
    //sort(result.begin(), result.end());
    
    for(const auto& ele : result) cout << ele << endl;
    return 0;
}
