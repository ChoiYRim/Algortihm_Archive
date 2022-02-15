#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> sheeps;
vector<bool> visit;

void bs(const vector<int>& info,
        const vector<vector<int>>& edges,
        int cur,
        int sheep,
        int wolf,
        int& answer)
{
    if(wolf >= sheep) // 늑대 수가 양보다 같거나 많으면 컷
        return;
    
    answer = max(answer,sheep);
    
    for(const auto& edge : edges)
    {
        int parent = edge[0];
        int child  = edge[1];
        int next,save;
        
        if(cur != parent && cur != child) // 현재 노드와 관련없는 엣지 컷
            continue;
        
        if(cur != child) // 현재 노드가 부모
        {
            next = child;
            save = sheeps[next];
            
            if(info[next] != 1) // 다음 노드에 양
            {
                if(!visit[next]) // 방문한적이 없음
                {
                    visit[next] = true;
                    sheeps[next] = sheep+1;
                    bs(info,edges,next,sheep+1,wolf,answer);
                    sheeps[next] = save;
                    visit[next] = false;
                }
                else if(sheeps[next] < sheep) // 방문했었지만 현재 내가 데리고 있는 양의 수가 더 많음
                {
                    sheeps[next] = sheep;
                    bs(info,edges,next,sheep,wolf,answer);
                    sheeps[next] = save;
                }
            }
            else // 다음 노드에 늑대
            {
                if(!visit[next]) // 방문한적이 없음
                {
                    visit[next] = true;
                    sheeps[next] = sheep;
                    bs(info,edges,next,sheep,wolf+1,answer);
                    sheeps[next] = save;
                    visit[next] = false;
                }
                else if(sheeps[next] < sheep) // 방문했었지만 현재 내가 데리고 있는 양의 수가 더 많음
                    {
                    sheeps[next] = sheep;
                    bs(info,edges,next,sheep,wolf,answer);
                    sheeps[next] = save;
                }
            }
        }
        else // 현재 노드가 자식
        {
            next = parent;
            save = sheeps[next];
            
            if(info[next] != 1) // 다음 노드에 양
            {
                if(sheeps[next] < sheep) // 방문했었지만 현재 내가 데리고 있는 양의 수가 더 많음
                {
                    sheeps[next] = sheep;
                    bs(info,edges,next,sheep,wolf,answer);
                    sheeps[next] = save;
                }
            }
            else // 다음 노드에 늑대
            {
                if(sheeps[next] < sheep) // 방문했었지만 현재 내가 데리고 있는 양의 수가 더 많음
                {
                    sheeps[next] = sheep;
                    bs(info,edges,next,sheep,wolf,answer);
                    sheeps[next] = save;
                }
            }
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges)
{
    int answer = 0;
    
    // info : 0 -> sheep , 1 -> wolf
    // 노드의 개수 : info.size()
    // sheeps : idx번 노드에 방문했을 때 모은 양의 개수
    sheeps = vector<int>(info.size(),0);
    visit = vector<bool>(info.size(),0);
    
    sheeps[0] = 1;
    visit[0] = 1;
    bs(info,edges,0,1,0,answer);
    
    return answer;
}

int main(int argc,char* argv[])
{
    vector<int> info = {}; // node informations
    vector<vector<int>> edges = {}; // edge informations
    
    cout << solution(info,edges) << endl;
    return 0;
}
