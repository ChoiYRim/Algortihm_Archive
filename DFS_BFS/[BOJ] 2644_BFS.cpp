#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Node
{
    int person;
    int cnt;
};

int N,M;
vector<int> relation[128];
bool visit[128] = {0,};
int start,last;
queue<Node> q;

int main()
{
    cin >> N;
    cin >> start >> last;
    cin >> M;
    for(int i = 0; i < M; i++)
    {
        int a,b; cin >> a >> b;
        relation[a].push_back(b);
        relation[b].push_back(a);
    }
    
    visit[start] = true;
    q.push({start,0});
    while(!q.empty())
    {
        Node cur = q.front();
        q.pop();
        
        if(cur.person == last)
        {
            cout << cur.cnt << '\n';
            return 0;
        }
        
        for(int i = 0; i < (int)relation[cur.person].size(); i++)
        {
            int connect = relation[cur.person][i];
            
            if(!visit[connect])
            {
                visit[connect] = true;
                q.push({connect,cur.cnt+1});
            }
        }
    }
    
    cout << -1 << '\n';
    return 0;
}
