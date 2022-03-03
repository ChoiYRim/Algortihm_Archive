#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int cnt = 0;
unordered_map<string,int> gem;
unordered_map<string,int> idx;
vector<int> v;

void init(const vector<string>& gems)
{
    unordered_set<string> s;
    
    for(int i = 0; i < gems.size(); i++)
    {
        if(s.find(gems[i]) != s.end())
            continue;
        
        s.insert(gems[i]);
        idx.insert({gems[i],cnt});
        cnt++;
    }
    
    v = vector<int>(cnt,0);
}

vector<int> solution(vector<string> gems)
{
    int len = static_cast<int>(gems.size()-1);
    int left = len,right = 1;
    vector<int> answer = {1,len+1};
    
    init(gems);
    
    for(int i = 0; i < gems.size(); i++)
    {
        if(gem.find(gems[i]) != gem.end())
        {
            gem[gems[i]] = i+1;
            v[idx[gems[i]]] = i+1;
            if(gem.size() == cnt)
            {
                left = *min_element(v.begin(), v.end());
                right = *max_element(v.begin(), v.end());
                if(len > right-left)
                {
                    len = right-left;
                    answer = {left,right};
                }
                else if(len == right-left)
                {
                    if(answer[0] > left)
                        answer = {left,right};
                }
            }
            continue;
        }
        
        gem[gems[i]] = i+1;
        v[idx[gems[i]]] = i+1;
        if(gem.size() == cnt)
        {
            left = *min_element(v.begin(), v.end());
            right = *max_element(v.begin(), v.end());
            if(len > right-left)
            {
                len = right-left;
                answer = {left,right};
            }
            else if(len == right-left)
            {
                if(answer[0] > left)
                    answer = {left,right};
            }
        }
    }
    
    return answer;
}


int main(int argc,char* argv[])
{
    auto v = solution({"A","B","C","D","D","E","C","B","A"});
    cout << "[" << v[0] << "," << v[1] << "]" << endl;
    return 0;
}
