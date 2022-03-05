#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

map<set<string>,bool> m;
vector<vector<string>> candidates;
vector<string> users[16];

inline bool comp(const string& s1,const string& s2) { return s1.length() < s2.length(); }

void search(const vector<string>& banned_id)
{
    for(int i = 0; i < banned_id.size(); i++)
    {
        string ban = banned_id[i];
        vector<string> v;
        vector<string> user = users[ban.length()];
        for(int j = 0; j < user.size(); j++)
        {
            bool check = true;
            for(int k = 0; k < user[j].length(); k++)
            {
                if(ban[k] == user[j][k])
                    continue;
                if(ban[k] == '*')
                    continue;
                check = false;
                break;
            }
            if(check)
                v.push_back(user[j]);
        }
        candidates.push_back(v);
    }
}

void classify(const vector<string>& user_id, vector<string>& banned_id)
{
    // 길이에 따른 분류
    sort(banned_id.begin(),banned_id.end(),comp);
    for(int i = 0; i < user_id.size(); i++)
    {
        string id = user_id[i];
        users[id.length()].push_back(id);
    }
}

void dfs(int depth,set<string> s)
{
    if(depth == candidates.size())
    {
        // printf("---------------\n");
        // for(auto it = s.begin(); it != s.end(); it++)
        //     printf("%s ", it->c_str());
        // printf("\n");
        if(m.find(s) != m.end())
            return;
        m[s] = true;
        return;
    }
    
    for(int i = 0; i < candidates[depth].size(); i++)
    {
        if(s.find(candidates[depth][i]) != s.end())
            continue;
        
        s.insert(candidates[depth][i]);
        dfs(depth+1,s);
        s.erase(candidates[depth][i]);
    }
}

int solution(vector<string> user_id, vector<string> banned_id)
{
    classify(user_id,banned_id);
    search(banned_id);
    dfs(0,{});
    return static_cast<int>(m.size());
}

int main(int argc,char* argv[])
{
    cout << solution({"frodo", "fradi", "crodo", "abc123", "frodoc"},{"fr*d*", "abc1**"}) << endl;
    return 0;
}
