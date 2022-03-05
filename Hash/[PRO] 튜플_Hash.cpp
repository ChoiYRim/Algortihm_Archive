#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int,int> map;
unordered_set<int> nums;

void print_tuples(const vector<vector<int>>& tuples)
{
    printf("{");
    for(int i = 0; i < tuples.size(); i++)
    {
        printf("{");
        for(int j = 0; j < tuples[i].size(); j++)
            printf("%3d ", tuples[i][j]);
        printf("}");
    }
    printf("}\n");
}

vector<vector<int>> split(const string& s)
{
    string tmp = "";
    vector<int> v;
    vector<vector<int>> ret;
    int len = static_cast<int>(s.length());
    
    for(int i = 1; i < len-1; i++)
    {
        if(s[i] == '{')
        {
            if(v.size() > 0)
            {
                ret.push_back(v);
                v.clear();
            }
            continue;
        }
        if(s[i] == '}' || s[i] == ',')
        {
            v.push_back(stoi(tmp));
            nums.insert(v.back());
            tmp.clear();
            if(s[i] == '}')
                i++;
            continue;
        }
        
        tmp.push_back(s[i]);
    }
    ret.push_back(v);
    
    return ret;
}

vector<int> solution(string s)
{
    vector<int> answer;
    vector<vector<int>> tuples = split(s);
    
    //print_tuples(tuples);
    //printf("nums length : %d\n", nums.size());
    for(int len = 1; len <= nums.size(); len++)
    {
        auto tuple = *find_if(tuples.begin(),tuples.end(),[&](vector<int> ele){return ele.size() == len;});
        
        for(int i = 0; i < tuple.size(); i++)
        {
            int ele = tuple[i];
            if(map[ele] != 0)
                continue;
            
            map[ele] = len;
            answer.push_back(ele);
        }
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    auto v = solution("{{2},{2,1},{2,1,3},{2,1,3,4}}");
    for(const auto& ele : v)
        printf("%-3d\n", ele);
    return 0;
}
