#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string,vector<int>> m;

vector<string> split(const string& info)
{
    size_t pos = 0,idx = 0;
    vector<string> ret;
    
    while((pos = info.find(' ',idx)) != string::npos)
    {
        if(idx+1 == pos)
        {
            idx++;
            continue;
        }
        
        string tmp = info.substr(idx,pos-idx);
        if(tmp == "and")
        {
            idx = pos+1;
            continue;
        }
        
        ret.push_back(info.substr(idx,pos-idx));
        idx = pos+1;
    }
    
    ret.push_back(info.substr(idx,pos-idx));
    return ret;
}

void insert_score(int idx,string str,const vector<string>& info,int& score)
{
    if(idx == 4)
    {
        m[str].push_back(score);
        return;
    }
    
    string tmp = str;
    
    tmp += info[idx];
    insert_score(idx+1,tmp,info,score);
    
    str.push_back('-');
    insert_score(idx+1,str,info,score);
}

vector<int> solution(vector<string> info, vector<string> query)
{
    vector<int> answer;
        
    // 정보 입력
    for(int i = 0; i < info.size(); i++)
    {
        auto v = split(info[i]);
        int score = stoi(v.back());
        v.pop_back();
        
        insert_score(0,"",v,score);
    }
    
    // unordered_map 오름차순 정렬
    for(auto it = m.begin(); it != m.end(); it++)
    {
        sort(it->second.begin(),it->second.end());
        
        // printf("[%s] : ", it->first.c_str());
        // for(int i = 0; i < it->second.size(); i++)
        //     printf("%3d ", it->second[i]);
        // printf("\n");
    }
    
    // 쿼리 수행
    for(int i = 0; i < query.size(); i++)
    {
        auto v = split(query[i]);
        string score = "";
        string question = "";
        for(int j = 0; j < v.size(); j++)
        {
            if(j == v.size()-1)
            {
                score = v[j];
                continue;
            }
            
            string cur = v[j];
            if(cur.length() <= 0)
                question += "-";
            else
                question += cur;
        }
        
        // printf("query : %s\n", question.c_str());
        // printf("score : %s\n", score.c_str());
        auto it = m.find(question);
        if(it != m.end())
        {
            auto low = lower_bound(it->second.begin(),it->second.end(),stoi(score));
            int cnt = static_cast<int>(it->second.end()-low);
            answer.push_back(cnt);
        }
        else
            answer.push_back(0);
    }
    
    return answer;
}

int main(int argc,char* argv[])
{
    auto v = solution({"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"}, {"java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"});
    
    for(const auto& ele : v)
        printf("%3d ", ele);
    printf("\n");
    return 0;
}
