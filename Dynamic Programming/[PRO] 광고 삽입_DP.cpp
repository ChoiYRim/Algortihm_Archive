#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int total[360000];

vector<string> split(string& str,const char delimiter)
{
    size_t pos = 0,idx = 0;
    vector<string> ret;
    
    while((pos = str.find(delimiter,idx)) != string::npos)
    {
        if(idx+1 == pos)
        {
            idx++;
            continue;
        }
        
        ret.push_back(str.substr(idx,pos-idx));
        idx = pos+1;
    }
    
    ret.push_back(str.substr(idx,pos-idx));
    return ret;
}

string get_result(int total)
{
    string hours = to_string(total/3600);
    string minutes = to_string((total-stoi(hours)*60*60)/60);
    string seconds = to_string(total-stoi(hours)*60*60-stoi(minutes)*60);
    
    if(hours.length() < 2)
        hours = "0"+hours;
    if(minutes.length() < 2)
        minutes = "0"+minutes;
    if(seconds.length() < 2)
        seconds = "0"+seconds;
    
    return hours+":"+minutes+":"+seconds;
}

int convert_time(const string& hours,const string& minutes,const string& seconds)
{
    int h = stoi(hours);
    int m = stoi(minutes);
    int s = stoi(seconds);
    
    return (h*60*60+m*60+s);
}

int check_time(int play,int adv)
{
    int result = 0;
    ll sum = 0,tmp;
    
    for(int i = 0; i < adv; i++) // 처음 0초부터 광고시간만큼 확인
        sum += total[i];
    tmp = sum;
    
    for(int i = adv; i < play; i++)
    {
        tmp += total[i]-total[i-adv];
        if(tmp > sum)
        {
            sum = tmp;
            result = i-adv+1;
        }
    }
    
    return result;
}

string solve(string& play,string& adv,vector<string>& logs)
{
    vector<pair<int,int>> result;
    vector<string> p_str = split(play,':');
    vector<string> a_str = split(adv,':');
    
    int play_time = convert_time(p_str[0],p_str[1],p_str[2]);
    int adv_time  = convert_time(a_str[0],a_str[1],a_str[2]);
    
    if(play_time == adv_time) // 동영상 재생시간과 공익광고 재생시간이 동일함
        return "00:00:00";
    
    for(int i = 0; i < logs.size(); i++)
    {
        vector<string> tmp1 = split(logs[i],'-'); // {시작시간,종료시간}
        vector<vector<string>> tmp2;
        
        for(int j = 0; j < tmp1.size(); j++)
            tmp2.push_back(split(tmp1[j],':'));
        
        int start_time = convert_time(tmp2[0][0],tmp2[0][1],tmp2[0][2]);
        int end_time = convert_time(tmp2[1][0],tmp2[1][1],tmp2[1][2]);
        
        for(int j = start_time; j < end_time; j++)
            total[j]++;
    }
    
    return get_result(check_time(play_time,adv_time));
}

string solution(string play_time, string adv_time, vector<string> logs)
{
    return solve(play_time,adv_time,logs);
}

int main(int argc,char* argv[])
{
    cout << solution("02:03:55","00:14:15",
                     {"01:20:15-01:45:14", "00:40:31-01:00:00",
                      "00:25:50-00:48:29", "01:30:59-01:53:29",
                      "01:37:44-02:02:30"}) << endl;
    return 0;
}
