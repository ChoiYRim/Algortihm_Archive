#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int result = 0x7fffffff;
vector<bool> visit;
vector<int> pick;

void debug_pick(const vector<int>& pick)
{
    for(const auto& ele : pick)
        printf("%2d ", ele);
    printf("\n");
}

bool is_needed_one(int n,vector<int>& weak,const vector<int>& dist)
{
    vector<int> tmp = weak;
    
    for(auto i = 0; i < weak.size(); i++)
    {
        int start = weak[i];
        for(auto& ele : tmp)
            if(ele < start)
                ele += n;
        
        sort(tmp.begin(),tmp.end());
        int weak_diff = tmp.back()-tmp.front();
        if(weak_diff <= dist.front())
            return true;
        tmp = weak;
    }
    
    return false;
}

void solve(int n,int cnt,vector<int> weak,const vector<int>& dist)
{
    if(cnt == dist.size())
    {
        //debug_pick(pick);
        
        for(int i = 0; i < weak.size() - 1; i++)
        {
            int weak_idx = 0,k;
            bool check = false;

            for(int j = 0; j < pick.size() && j + 1 < result && !check; j++)
            {
                int last = weak[weak_idx] + pick[j]; // 현재 친구가 갈 수 있는 최종 정점
                while(last >= weak[weak_idx])
                {
                    weak_idx++;
                    if(weak_idx == weak.size()) // 끝 도달
                    {
                        k = j + 1;
                        check = true;
                        break;
                    }
                }
            }
            
            if(check == true)
                result = min(result,k);

            int start = weak[0];
            for (int j = 1; j < weak.size(); j++) // 한칸씩 당기기
                weak[j - 1] = weak[j];
            weak[weak.size() - 1] = start + n; // 원래 시작점이었던 정점을 끝으로 옮기고 + n
        }
    }
    
    for(auto i = 0; i < dist.size(); i++)
    {
        if(visit[i])
            continue;
        
        visit[i] = true;
        pick.push_back(dist[i]);
        solve(n,cnt+1,weak,dist);
        pick.pop_back();
        visit[i] = false;
    }
}

int solution(int n, vector<int> weak, vector<int> dist)
{
    visit = vector<bool>(dist.size(),0);
    sort(dist.begin(),dist.end(),greater<int>());
    
    if(is_needed_one(n,weak,dist))
        return 1;
    
    solve(n,0,weak,dist);
    
    return (result == 0x7fffffff ? -1 : result);
}

int main()
{
    printf("%d\n", solution(12, {1,5,6,10}, {1,2,3,4}));
    return 0;
}
