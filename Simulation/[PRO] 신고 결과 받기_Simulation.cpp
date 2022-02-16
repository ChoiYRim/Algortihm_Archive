#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<string> split(const string& report)
{
    size_t idx = 0,pos = 0;
    vector<string> ret;
    
    while((pos = report.find(' ',idx)) != string::npos)
    {
        if(idx == pos)
        {
            idx++;
            continue;
        }
        ret.push_back(report.substr(idx,pos-idx));
        idx = pos+1;
    }
    if(idx != pos)
        ret.push_back(report.substr(idx,pos-idx));
    
    return ret;
}

vector<int> solve(const vector<string>& id_list,const vector<string>& reports,const int k)
{
    int report_size = static_cast<int>(reports.size());
    
    vector<int> result;
    map<string,int> warns;
    map<string,set<string>> froms;
    
    // 초기화
    for(const auto& id : id_list)
    {
        warns.insert({id,0});
        froms.insert({id,{}});
    }
    
    // report 종합
    for(int i = 0; i < report_size; i++)
    {
        auto from_to = split(reports[i]);
        string from = from_to[0];
        string   to = from_to[1];
        
        // froms[from].insert(to);
        if(froms[from].find(to) != froms[from].end())
            continue;
        
        froms[from].insert(to);
        warns[to]++;
    }
    
    // 결과값 도출
    for(const auto& id : id_list)
    {
        int cnt = 0;
        set<string> report = froms[id];
        for(auto it = report.begin(); it != report.end(); it++)
        {
            if(warns[*it] >= k)
                cnt++;
        }
        result.push_back(cnt);
    }
    
    return result;
}

vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
    vector<int> answer = solve(id_list,report,k);
    
    return answer;
}
