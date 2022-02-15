#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

vector<vector<string>> split(const vector<string>& records)
{
    vector<vector<string>> ret;
    
    for(auto record : records)
    {
        size_t pos = 0,idx = 0;
        vector<string> parts;
        
        while(record.back() == ' ')
            record.pop_back();
        while((pos = record.find(' ',idx)) != string::npos)
        {
            if(idx == pos)
            {
                idx++;
                continue;
            }
            parts.push_back(record.substr(idx,pos-idx));
            idx = pos+1;
        }
        parts.push_back(record.substr(idx,pos-idx));
        ret.push_back(parts);
    }
    
    return ret;
}

bool tcomp(const vector<string>& v1,const vector<string>& v2)
{
    string v1_in = v1[0];
    string v2_in = v2[0];
    
    int v1_hour = stoi(v1_in.substr(0,2));
    int v2_hour = stoi(v2_in.substr(0,2));
    
    int v1_min = stoi(v1_in.substr(3,2));
    int v2_min = stoi(v2_in.substr(3,2));
    
    if(v1_hour == v2_hour)
        return v1_min < v2_min;
    return v1_hour < v2_hour;
}

bool ncomp(const vector<string>& v1,const vector<string>& v2)
{
    if(v1[1] < v2[1])
        return true;
    return false;
}

int get_time(const string& in,const string& out)
{
    int total = 0;
    
    int in_hour = stoi(in.substr(0,2));
    int out_hour = stoi(out.substr(0,2));
    
    int in_min = stoi(in.substr(3,2));
    int out_min = stoi(out.substr(3,2));
    
    int hour = out_hour-in_hour;
    int minute = out_min-in_min;
    
    if(minute < 0)
    {
        minute += 60;
        hour--;
    }
    
    total = (hour*60)+minute;
    
    return total;
}

int get_cost(const vector<int>& fees,double total)
{
    int std_time = fees[0];
    int std_cost = fees[1];
    int unit_time = fees[2];
    int unit_cost = fees[3];
    //int total = get_time(in,out);
    
    if(total <= std_time)
        return std_cost;
    
    int cost = std_cost;
    
    total -= std_time;
    cost += ceil(total/unit_time)*unit_cost;
    
    return cost;
}

vector<int> solve(const vector<int>& fees,const vector<string>& records)
{
    vector<vector<string>> in,out;
    map<string,int> m;
    vector<int> cost;
    
    auto new_records = split(records);
    sort(new_records.begin(),new_records.end(),ncomp);
    for(auto& record : new_records)
    {
        string io_time = record[0];
        string car_num = record[1];
        string io      = record[2];
        
        if(io != "OUT") // IN
        {
            in.push_back(record);
        }
        else // OUT
        {
            out.push_back(record);
        }
    }
    
    sort(in.begin(),in.end(),tcomp);
    sort(out.begin(),out.end(),tcomp);
    
    for(size_t i = 0; i < in.size(); i++)
    {
        string car_num = in[i][1];
        string in_time = in[i][0];
        string out_time = "23:59";
        map<string,int>::iterator it;
        
        for(auto it = out.begin(); it != out.end(); it++)
        {
            auto v = *it;
            string target_num = v[1];
            
            if(target_num == car_num)
            {
                out_time = v[0];
                out.erase(it);
                break;
            }
        }
        
        if((it = m.find(car_num)) != m.end())
            it->second += get_time(in_time,out_time);
        else
            m.insert({car_num,get_time(in_time,out_time)});
    }
    
    for(auto it = m.begin(); it != m.end(); it++)
        cost.push_back(get_cost(fees,static_cast<double>(it->second)));
    
    return cost;
}

vector<int> solution(vector<int> fees, vector<string> records)
{
    vector<int> answer = solve(fees,records);
    
    return answer;
}

int main()
{
    auto v = solution({180,5000,10,600},
                   {"05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT",
                    "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN",
                    "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT"});
    
    // .. 출력 결과 확인 ..
    
    return 0;
}
