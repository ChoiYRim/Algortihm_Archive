#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// 초당 최대 처리량 (1초 : 1000밀리초)
// 9월 15일 하루 동안 1초에 최대 몇 개의 로그를 처리?
// 하루 : 60 * 60 * 24 = 3600 * 24 = 86400초

vector<pair<int,int>> seconds;

bool comp(const pair<int,int>& p1,const pair<int,int>& p2)
{
    if(p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first < p2.first;
}

vector<string> split(string& cur)
{
    vector<string> ret;
    char* c_str = new char[cur.length()],*ptr;
    
    strcpy(c_str,cur.c_str());
    ptr = strtok(c_str," ");
    while(ptr != NULL)
    {
        ret.push_back(string(ptr));
        ptr = strtok(NULL," ");
    }
    
    delete[] c_str;
    return ret;
}

void print_vector(const vector<string>& v)
{
    for(const auto& ele : v)
        printf("%s\n", ele.c_str());
}

void print_time()
{
    for(int i = 0; i < seconds.size(); i++)
    {
        printf("-----------------\n");
        printf("start : %d\n", seconds[i].first);
        printf("end   : %d\n", seconds[i].second);
    }
}

inline int get_start_time(int s,int l)
{
    return s-l+1;
}

void calculate(const vector<string>& v)
{
    int start_time,end_time,sec = 0,mili = 0;
    string End = v[1];
    string Len = v[2];
    string tmp = "";
    bool is_exist = false;
    
    //printf("v[2] : %s\n", v[2].c_str());
    
    string h = End.substr(0,2); // 시
    string m = End.substr(3,2); // 분
    string s = End.substr(6); // 초
    
    s.erase(s.find('.'),1); // . 제거
    Len.pop_back(); // s 제거 //
    for(int i = 0; i < Len.length(); i++)
    {
        if(Len[i] == '.')
        {
            is_exist = true;
            sec = stoi(tmp);
            sec *= 1000;
            tmp = "";
            continue;
        }
        
        tmp.push_back(Len[i]);
    }
    if(is_exist)
        mili = stoi(tmp);
    else
    {
        sec = stoi(tmp);
        sec *= 1000;
    }
        
    int eh = stoi(h);
    int em = stoi(m);
    int es = stoi(s);
    int l  = sec+mili;
    
    end_time = eh*60*60*1000+em*60000+es;
    start_time = get_start_time(end_time,l);
    if(start_time < 0)
        start_time = 0;
    
    seconds.push_back({start_time,end_time});
}

bool range(int left,int right,int s,int e)
{
    if(e < left || s > right)
        return false;
    return true;
}

int solution(vector<string> lines)
{
    int answer = 0;
    for(int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        auto v = split(line);
        
        calculate(v);
    }
    
    //sort(seconds.begin(),seconds.end(),comp);
    
    //print_time();
    
    for(int i = 0; i < seconds.size(); i++)
    {
        int num = 1;
        int si = seconds[i].first;
        int ei = seconds[i].second;
        
        for(int j = 0; j < seconds.size(); j++)
        {
            if(i == j) continue;
            
            int sj = seconds[j].first;
            int ej = seconds[j].second;
            
            if(range(ei,ei+999,sj,ej))
                num++;
        }
        
        answer = max(answer,num);
    }
    
    return answer;
}

int main()
{
    cout << solution({"2016-09-15 01:00:04.001 2.0s", "2016-09-15 01:00:07.000 2s"}) << endl;
    return 0;
}
