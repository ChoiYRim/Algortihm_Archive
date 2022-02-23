#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 2개 이상 주문한 메뉴들 중에서 '묶음' 단위로 가장 많이 주문된 것을 찾고
// 그런 것들이 여러개면 다 넣으면 된다.

inline bool comp(const pair<string,int>& p1,const pair<string,int>& p2)
{
    return p1.second > p2.second;
}

void order_count(vector<int>& ordered,const vector<string>& orders)
{
    for(int i = 0; i < orders.size(); i++)
    {
        const char* order = orders[i].c_str();
        while(*order != '\0')
        {
            int idx = *order-'A';
            ordered[idx]++;
            order++;
        }
    }
}

string get_menus(vector<int>& ordered,vector<string>& orders)
{
    string result = "";
    
    order_count(ordered,orders);
    
    for(int i = 0; i < 26; i++)
    {
        if(ordered[i] < 2) continue;
        
        result.push_back(i+'A');
    }
    
    return result;
}

void comb(int idx,int num,string str,vector<string>& v,const string& menus)
{
    if(str.length() == num)
    {
        v.push_back(str);
        return;
    }
    else if(idx == menus.length())
        return;
    
    str.push_back(menus[idx]);
    comb(idx+1,num,str,v,menus);
    str.pop_back();
    
    comb(idx+1,num,str,v,menus);
}

int count(const string& target,const vector<string>& orders)
{
    int result = 0;
    
    for(int i = 0; i < orders.size(); i++)
    {
        string order = orders[i];
        bool is_exist = true;
        
        for(int j = 0; j < target.length(); j++)
        {
            if(order.find(target[j]) == string::npos)
            {
                is_exist = false;
                break;
            }
        }
        if(is_exist)
            result++;
    }
    
    return result;
}

vector<string> solve(vector<string>& orders,vector<int>& course)
{
    vector<string> result;
    vector<int> ordered(26,0); // 메뉴들 주문 횟수 세기
    string menus = get_menus(ordered,orders); // 2번 이상 주문된 메뉴들
    
    for(int i = 0; i < course.size(); i++)
    {
        vector<string> set_menu;
        vector<pair<string,int>> v; // 묶을 메뉴,호출된 횟수
        int call = course[i]; // 메뉴들을 몇 개 단위로 묶을건지
        int cnt;
        
        comb(0,call,"",set_menu,menus);
        
        for(int j = 0; j < set_menu.size(); j++)
        {
            cnt = count(set_menu[j],orders);
            if(cnt > 1)
                v.push_back({set_menu[j],cnt});
        }
        
        sort(v.begin(),v.end(),comp);
        
        if(v.size() <= 0 || v.front().first == "")
            continue;
        
        cnt = v.front().second;
        for(int j = 0; j < v.size() && v[j].second == cnt; j++)
            result.push_back(v[j].first);
        
        // printf("------------------\n");
        // for(auto ele : set_menu)
        //     printf("%s ", ele.c_str());
        // printf("\n------------------\n");
    }
    
    sort(result.begin(),result.end());
    return result;
}

vector<string> solution(vector<string> orders, vector<int> course)
{
    return solve(orders,course);
}

int main()
{
    auto v = solution({"ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH"},{2,3,4});
    return 0;
}
