#include <iostream>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

struct Node
{
    int pos;
    int cnt;
};

int total,start,target,U,D;
int btn[2];
bool visit[1000001];

inline bool range(int pos) { return (pos >= 1 && pos <= total); }

void input()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> total >> start >> target >> U >> D;
    btn[0] = U;
    btn[1] = -D;
}

string solve()
{
    queue<Node> q;
    visit[start] = 1;
    q.push({start,0});
    while(!q.empty())
    {
        int pos = q.front().pos;
        int cnt = q.front().cnt;
        q.pop();
        
        if(pos == target)
            return to_string(cnt);
        
        for(int i = 0; i < 2; i++)
        {
            int next = pos+btn[i];
            
            if(!range(next))
                continue;
            if(visit[next])
                continue;
            
            visit[next] = 1;
            q.push({next,cnt+1});
        }
    }
    
    return "use the stairs";
}

int main(int argc,char* argv[])
{
    input();
    
    cout << solve() << endl;
    return 0;
}
