#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

#define NUM 100001

using namespace std;

int T,N;
vector<int> v,result;
vector<bool> visit;

void input()
{
    v.clear();
    cin >> N;
    v = vector<int>(N+1,0);
    for(int i = 1; i <= N; i++)
    {
        int student; cin >> student;
        v[i] = student;
    }
    visit = vector<bool>(N+1,false);
}

int main(void)
{
    cin >> T;
    while(T--)
    {
        int sum = 0;
        
        input();
        
        for(int start = 1; start <= N; start++)
        {
            if(visit[start])
                continue;
            
            int cnt = 0;
            bool check = false;
            queue<int> q;
            vector<int> node;
            vector<bool> local(N+1,false);
            
            q.push(start);
            while(!q.empty())
            {
                int cur = q.front();
                int next = v[cur];
                q.pop();
                
                cnt++;
                if(local[cur])
                    break;
                
                visit[cur] = true;
                local[cur] = true;
                node.push_back(cur);

                if(next != start)
                {
                    q.push(next);
                    continue;
                }
                
                check = true;
                break;
            }
            
            if(check)
                sum += cnt;
            else
            {
                for(int i = 0; i < (int)node.size(); i++)
                {
                    visit[node[i]] = false;
                }
            }
        }
        
        result.push_back(N-sum);
    }
    
    for(int i = 0; i < (int)result.size(); i++)
        cout << result[i] << '\n';
    return 0;
}
