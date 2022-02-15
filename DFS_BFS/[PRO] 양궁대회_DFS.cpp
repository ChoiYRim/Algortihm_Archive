#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 최대 점수 차 승리 : 55점
vector<vector<int>> win_cases[56];
vector<int> lion(11,0);
queue<pair<int,int>> apeach;

bool comp(const vector<int>& v1,const vector<int>& v2)
{
    for(size_t i = 10; i >= 0; i--)
    {
        if(v1[i] == v2[i])
            continue;
        
        if(v1[i] > v2[i])
            return true;
        else
            return false;
    }
    
    return false;
}

// 10점부터 0점까지 : 11개 점수
void dfs(int idx,
         int cnt,
         const int& n,
         const vector<int>& info)
{
    if(cnt <= 0) // 라이언이 쏠 수 있는 화살이 더 없음
    {
        auto q = apeach;
        auto l = lion;
        
        int lscore = 0,ascore = 0;
        while(!q.empty())
        {
            int idx = q.front().first;
            int num = q.front().second;
            q.pop();
            
            if(l[idx] > num)
                lscore += (10-idx);
            else
                ascore += (10-idx);
            l[idx] = 0;
        }
        for(int i = 0; i <= 10; i++)
            if(l[i])
                lscore += (10-i);
        
        if(lscore > ascore)
            win_cases[lscore-ascore].push_back(lion);
        return;
    }
    if(idx > 10)
        return;
    
    for(int i = 0; i <= cnt; i++)
    {
        lion[idx] = i;
        dfs(idx+1,cnt-i,n,info);
        lion[idx] = 0;
    }
}

bool check(vector<int>& best_case)
{
    for(int i = 55; i > 0; i--)
    {
        if(!win_cases[i].size())
            continue;
        
        sort(win_cases[i].begin(),win_cases[i].end(),comp);
        best_case = win_cases[i][0];
        return true;
    }
    
    return false;
}

vector<int> solve(const int& n,const vector<int>& info)
{
    bool win = false;
    vector<int> best_case;
    
    for(int i = 0; i <= 10; i++)
    {
        int num = info[i];
        int idx = i;
        
        if(num)
            apeach.push({idx,num});
    }
    
    // 최대 n개만 쏠 수 있음.
    dfs(0,n,n,info);
    
    win = check(best_case);
    
    if(!win)
        best_case = vector<int>(1,-1);
    
    return best_case;
}

vector<int> solution(int n, vector<int> info)
{
    vector<int> answer = solve(n,info);
    
    return answer;
}

int main()
{
    for(auto a : solution(5,{2,1,1,1,0,0,0,0,0,0,0}))
    {
        cout << a << ' ';
    }
    cout << endl;
    return 0;
}
